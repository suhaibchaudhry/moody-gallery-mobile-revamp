<?php
function & XML_unserialize(&$xml){
	$xml_parser = &new XML();
	$data = &$xml_parser->parse($xml);
	$xml_parser->destruct();
	return $data;
}

function & XML_serialize(&$data, $level = 0, $prior_key = NULL){
	if($level == 0){ ob_start();  }
	while(list($key, $value) = each($data))
		if(!strpos($key, ' attr'))
			if(is_array($value) and array_key_exists(0, $value)){
				XML_serialize($value, $level, $key);
			}else{
				$tag = $prior_key ? $prior_key : $key;
				echo str_repeat("\t", $level),'<',$tag;
				if(array_key_exists("$key attr", $data)){ 
					while(list($attr_name, $attr_value) = each($data["$key attr"]))
						echo ' ',$attr_name,'="',htmlspecialchars($attr_value),'"';
					reset($data["$key attr"]);
				}

				if(is_null($value)) echo " />\n";
				elseif(!is_array($value)) echo '>',htmlspecialchars($value),"</$tag>\n";
				else echo ">\n",XML_serialize($value, $level+1),str_repeat("\t", $level),"</$tag>\n";
			}
	reset($data);
	if($level == 0){ $str = ob_get_contents(); ob_end_clean(); return $str; }
}

class XML{
	var $parser;   
	var $document; 
	var $parent;   
	var $stack;    
	var $last_opened_tag; 

	function XML(){
 		$this->parser = xml_parser_create();
		xml_parser_set_option($this->parser, XML_OPTION_CASE_FOLDING, false);
		xml_set_object($this->parser, $this);
		xml_set_element_handler($this->parser, 'open', 'close');
		xml_set_character_data_handler($this->parser, 'data');
	}
	function destruct(){ xml_parser_free($this->parser); }
	function & parse(&$data){
		$this->document = array();
		$this->stack    = array();
		$this->parent   = &$this->document;
		return xml_parse($this->parser, $data, true) ? $this->document : NULL;
	}
	function open(&$parser, $tag, $attributes){
		$this->data = ''; 
		$this->last_opened_tag = $tag;
		if(is_array($this->parent) and array_key_exists($tag,$this->parent)){ 
			if(is_array($this->parent[$tag]) and array_key_exists(0,$this->parent[$tag])){ 
				
				$key = count_numeric_items($this->parent[$tag]);
			}else{
				
				if(array_key_exists("$tag attr",$this->parent)){
					$arr = array('0 attr'=>&$this->parent["$tag attr"], &$this->parent[$tag]);
					unset($this->parent["$tag attr"]);
				}else{
					$arr = array(&$this->parent[$tag]);
				}
				$this->parent[$tag] = &$arr;
				$key = 1;
			}
			$this->parent = &$this->parent[$tag];
		}else{
			$key = $tag;
		}
		if($attributes) $this->parent["$key attr"] = $attributes;
		$this->parent  = &$this->parent[$key];
		$this->stack[] = &$this->parent;
	}
	function data(&$parser, $data){
		if($this->last_opened_tag != NULL) 
			$this->data .= $data;
	}
	function close(&$parser, $tag){
		if($this->last_opened_tag == $tag){
			$this->parent = $this->data;
			$this->last_opened_tag = NULL;
		}
		array_pop($this->stack);
		if($this->stack) $this->parent = &$this->stack[count($this->stack)-1];
	}
}
function count_numeric_items(&$array){
	return is_array($array) ? count(array_filter(array_keys($array), 'is_numeric')) : 0;
}

//* UCS API v. 3.0 *//
//* http://www.unlockcodesource.com remote interface class
//* Copyright unlockcodesource.com 2011 *//
//* if you have any questions or would like to report a bug please contact techsupport@unlockcodesource.com *//

class UCS {
	var $username;
	var $pass;
	var $apikey;
	var $response;
	
	function action ($action, $params = array()) {

		$datarequest['API']['username'] = $this->username;
		$datarequest['API']['pass'] = $this->pass;
		$datarequest['API']['key']= $this->apikey;
		$datarequest['API']['action'] = $action;
		
		switch ($action) {
			case "get_accountinfo":
				$datarequest['API']['action'] = "get_accountinfo";
			break;
			
			case "get_unlocktools":
				(isset($params['method_id'])) ? $datarequest['API']['method_id'] = $params['method_id'] : $datarequest['API']['method_id'] = NULL;
				(isset($params['cust_id'])) ? $datarequest['API']['cust_id'] = $params['cust_id'] : $datarequest['API']['cust_id'] = NULL;
				$datarequest['API']['action'] = "get_unlocktools";		
			break;
			
			case "get_instructions":
				(isset($params['instruction_id'])) ? $datarequest['API']['instruction_id'] = $params['instruction_id'] : $datarequest['API']['instruction_id'] = NULL;
				$datarequest['API']['action'] = "get_instructions";			
			break;
			
			case "submit_order":
				(isset($params['imei'])) ? $datarequest['API']['imei'] = $params['imei'] : $datarequest['API']['imei'] = NULL;
				(isset($params['phonemake_id'])) ? $datarequest['API']['phonemake_id'] = $params['phonemake_id'] : $datarequest['API']['phonemake_id'] = NULL;																																
				(isset($params['model'])) ? $datarequest['API']['model'] = $params['model'] : $datarequest['API']['model'] = "";
				(isset($params['tool_id'])) ? $datarequest['API']['tool_id'] = $params['tool_id'] : $datarequest['API']['tool_id'] = 0;
				(isset($params['notes'])) ? $datarequest['API']['notes'] = $params['notes'] : $datarequest['API']['notes'] = "";
				(isset($params['cust_id'])) ? $datarequest['API']['cust_id'] = $params['cust_id'] : $params['cust_id'] = NULL;	
				(isset($params['params'])) ? $datarequest['API']['params'] = $params['params'] : $params['params'] = NULL;
			break;
			
			case "get_orderID":
				(isset($params['orderID'])) ? $datarequest['API']['orderID'] = $params['orderID'] : $datarequest['API']['orderID'] = NULL;
				$datarequest['API']['action'] = "get_orderID";
		
			break;
			
			case "get_imei":
				(isset($params['imei'])) ? $datarequest['API']['imei'] = $params['imei'] : $datarequest['API']['imei'] = NULL;
				$datarequest['API']['action'] = "get_imei";
			break;
		
			case "get_RequiredParams":
				(isset($params['tool_id'])) ? $datarequest['API']['tool_id'] = $params['tool_id'] : $datarequest['API']['tool_id'] = NULL;
			break;
			
			case "get_SortedMethodList":
				$datarequest['API']['action'] = "get_SortedMethodList";
				(isset($params['vip_id'])) ? $datarequest['API']['vip_id'] = $params['vip_id'] : $datarequest['API']['vip_id'] = NULL;
			break;
		}
		
		$this->response = $this->sendQuery($datarequest);

	}
	
	function sendQuery($data) {
		//*change array to xml *//
		//print_r($data);
		$xmlrequest = XML_serialize($data);
		$xmlrequest = 'data='.$xmlrequest;
		$timeout = 250;
		$url = "http://www.unlockcodesource.com/API_v2/ucs_apiv3.php"; //XML service API address
		//$url = "http://24.85.147.86/ucsv3/API_v2/ucs_apiv2.php";
		//$url = "http://www.unlockcodesource.com/API_v2/ucs_mobileapi.php";
		//$url = "http://24.85.147.86/ucsv3/API_v2/ucs_mobileapi.php";
		$ch = curl_init(); //initiate the curl session
		curl_setopt($ch, CURLOPT_URL, $url); //set to url to post to
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1); // tell curl to return data in a variable
		curl_setopt($ch, CURLOPT_HEADER, 0);
		curl_setopt($ch, CURLOPT_POST, 1);
		curl_setopt($ch, CURLOPT_POSTFIELDS, $xmlrequest); // post the xml
		curl_setopt($ch, CURLOPT_TIMEOUT, 10); // set timeout in seconds
		curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, FALSE);
		$result['xml'] = curl_exec($ch);
		curl_close ($ch);
		//* set the xml as array *//
		$result['data'] = XML_unserialize($result['xml']); 
		return $result;
	}
	
}
