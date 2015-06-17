<?php
/*Begin implementation for unlock tool order page*/
function unlock_order_tool($tool_id) {
	$response = unlock_api_get_unlocktools($tool_id);
	$tool = $response['unlock_tools']['tool'];
	$content = '';

	if($tool) {
		//Render unlock details box
		$content .= theme('unlock_details', $tool['tool_name'], filter_xss(stripslashes($tool['description']), array('a', 'em', 'strong', 'cite', 'code', 'ul', 'ol', 'li', 'dl', 'dt', 'dd', 'br', 'p')), $tool['process_time'], unlock_order_markup_price($tool_id, $tool['price']), $tool['supported']['PhoneMakeID']);
		//Render Order Form
		$content .= drupal_get_form('unlock_order_form', unlock_order_phone_make_options($tool['supported']['PhoneMakeID']), $tool_id, $tool['ExtraParams'], unlock_order_markup_price($tool_id, $tool['price']), $tool['price']);
		return $content;
	} else {
		drupal_not_found();
	}
}

function unlock_order_form(&$form_state = array(), $phone_make_options, $tool_id, $extra_params, $price, $cost) {
	drupal_add_js(drupal_get_path('module', 'unlock_order').'/js/imei_length_validate.js');

	$form = array();
	$form['tool_id'] = array('#type' => 'value', '#value' => $tool_id);
	$form['price'] = array('#type' => 'value', '#value' => $price);
	$form['cost'] = array('#type' => 'value', '#value' => $cost);
	$form['phone_makes'] = array('#type' => 'value', '#value' => $phone_make_options);
	
	if($extra_params == 'Y') {
		$extra_param_options = unlock_order_extra_param_options($tool_id);

		$form['extra-params'] = array(
			'#type' => 'fieldset',
			'#title' => t($extra_param_options['title']),
			'#collapsible' => FALSE
		);

		$form['extra-params']['option'] = array(
			'#type' => 'select',
			'#options' => $extra_param_options['options'],
			'#attributes' => array('class' => 'unlock-service'),
			'#required' => TRUE
		);
	}
	
	$form['order'] = array(
		'#type' => 'fieldset',
		'#title' => t('Order Details'),
		'#collapsible' => FALSE,
	);
	$form['order']['make_options'] = array(
		'#type' => 'select',
		'#title' => 'Device make',
		'#options' => $phone_make_options,
		'#required' => TRUE
	);
	$form['order']['model'] = array(
		'#type' => 'textfield',
		'#title' => 'Device model',
		'#required' => FALSE,
		'#size' => 20,
		'#maxlength' => 128
	);
	$form['order']['imei'] = array(
		'#type' => 'textfield',
		'#title' => 'IMEI Number',
		'#required' => TRUE,
		'#size' => 20,
		/*
		'#rows' => 5,
		'#cols' => 5,
		'#description' => 'Please insert one IMEI per line.'
		*/
		'#description' => 'IMEI number of the phone to be unlocked.'
	);

	$form['order']['customer'] = array(
		'#type' => 'textfield',
		'#title' => 'Customer E-mail',
		'#description' => 'We can optionally e-mail the code result to your customer\'s email address.',
		'#required' => FALSE,
		'#size' => 40,
		'#maxlength' => 255
	);
	
	$form['order']['notes'] = array(
		'#type' => 'textarea',
		'#title' => 'Additional Notes',
		'#required' => FALSE
	);
	
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => 'Submit Order'
	);

	return $form;
}

function unlock_order_form_validate($form, &$form_values) {
	global $user;
	
	$email_tools = array(109, 2);
	$dhru_tools = array(233, 183, 195, 194, 213, 164, 109);
	
	if(in_array($form_values['values']['tool_id'], $email_tools)) {
		
		$body = "A new E-Mail order has been placed on unlockbazaar.com.\nBelow are all of the details pertaining to the new order.\n\n";
		foreach($form_values['values'] as $key => $val) {
			if($key == 'make_options')  {
				$body .= $key.': '.$form_values['values']['phone_makes'][((int)($val))]."\n";
			} elseif($key == 'phone_makes') {
			} else {
				$body .= $key.': '.$val."\n";
			}
		}
		
		drupal_mail_send(array(
			'id' => 'unlock_order_request',
			'to' => 'Faraz Ahmed <info@unlockbazaar.com>, Asad Hasan <asadpakistani@gmail.com>',
			'subject' => 'New Unlock Order Request',
			'body' => drupal_wrap_mail($body),
			'headers' => array('From' => 'info@unlockbazaar.com'),
		));

		drupal_set_message('Your order was successfully submitted. You will recieve an email with your unlock code shortly.');

		//da_user_credits_charge($price*count($imeis), $user_id);
	
	//} elseif(in_array($form_values['values']['tool_id'], $dhru_tools)) {

	} else {
	
		if(in_array($form_values['values']['tool_id'], array(63, 83, 84, 173, 16, 82, 20))) {
			$imeis = unlock_order_parse_meids($form_values['values']['imei']);
		} else {
			$imeis = unlock_order_parse_imeis($form_values['values']['imei']);
		}
	
		$valid_imeis = count($imeis);
		$pieces = array_map('trim', explode("\n", $form_values['values']['imei']));
		//Make sure user has sufficient credits to make the order
		if((float)$form_values['values']['price']*$valid_imeis > (float)da_user_credits_fetch($user->uid)) {
			form_set_error('imei', 'You do not have sufficient credits to make this order. Please '.l('add more credit', 'user/'.$user->uid.'/add-credit').' to your account.');
			drupal_add_js('Drupal.behaviors.incomplete_imeis = function() {(function($) {$("#edit-imei").val("'.$form_values['values']['imei'].'");})(jQuery);}', 'inline');
			return;
		}
		
		if($valid_imeis == 0) {
			form_set_error('imei', 'All of the IMEI numbers submitted by you were invalid. Please use numbers only (no dashes or spaces), and enter one valid IMEI number per line.');
			drupal_add_js('Drupal.behaviors.incomplete_imeis = function() {(function($) {$("#edit-imei").val("'.$form_values['values']['imei'].'");})(jQuery);}', 'inline');
			return;
		}
	
		if($valid_imeis != count($pieces)) {
			form_set_error('imei', 'Some of the IMEI numbers provided by you were invalid. (Invalid IMEI Numbers: '.implode(', ', array_diff($pieces, $imeis)).')');
			drupal_add_js('Drupal.behaviors.incomplete_imeis = function() {(function($) {$("#edit-imei").val("'.$form_values['values']['imei'].'");})(jQuery);}', 'inline');
			return;
		}
		
		//Attempt Submitting an order
		if(isset($form_values['values']['option'])) {
			$params = $form_values['values']['option'];
		} else {
			$params = '';
		}
		
		$imeis = unlock_order_recycle_imeis($imeis, $user->uid, time(), $form_values['values']['tool_id'], $form_values['values']['price'], $form_values['values']['cost'], $form_values['values']['customer'], $form_values['values']['notes'], $form_values['values']['make_options'], $form_values['values']['model']);
		if(count($imeis) == 0) {
			return;
		}
		
		//Use String or Array
		if(count($imeis) == 1) {
			$imei = $imeis[0];	
		} else {
			$imei = $imeis;	
		}
	
		//Submit imei's remotely
		$response = unlock_api_submit_order($imei, $form_values['values']['make_options'], $form_values['values']['tool_id'], $params, 	$form_values['values']['notes'], $form_values['values']['model']);
		
		if($response['status'] == 'OK') {	
			unlock_order_process_new_order($user->uid, time(), $form_values['values']['tool_id'], UNLOCK_PENDING, $imeis, $form_values['values']['cost'], $form_values['values']['price'], $form_values['values']['make_options'], $form_values['values']['model'], $form_values['values']['customer'], $form_values['values']['notes'], $response['orderID']);
			drupal_set_message('Your order was successfully submitted. You can proceed to the order page to check your order status.');
		} elseif(!isset($response['orderID'])) {
			//When server does not return any OrderID...it is charging us in these cases...wierd api
			form_set_error('imei', 'Your request could not be processed. Either your inputs are invalid or the service is currently down for maintenance. Please do not retry, contact the site administrator for assistance immediately.'.$response['message']);
			drupal_add_js('Drupal.behaviors.incomplete_imeis = function() {(function($) {$("#edit-imei").val("'.implode("\n", $imeis).'");})(jQuery);}', 'inline');
		} else {
			$new_order = unlock_api_get_order_id($response['orderID']);
			$completed_imeis = unlock_order_filter_submitted_imeis($imeis, $new_order);
			drupal_add_js('Drupal.behaviors.incomplete_imeis = function() {(function($) {$("#edit-imei").val("'.implode("\n", $imeis).'");})(jQuery);}', 'inline');
			//Only inserter completed IMEIs to DB
			unlock_order_process_new_order($user->uid, time(), $form_values['values']['tool_id'], UNLOCK_PENDING, $completed_imeis, $form_values['values']['cost'], $form_values['values']['price'], $form_values['values']['make_options'], $form_values['values']['model'], $form_values['values']['customer'], $form_values['values']['notes'], $response['orderID']);
			if(count($imeis) == 0) {
				drupal_set_message('Your order was successfully submitted. You can proceed to the order page to check your order status. Some duplicate IMEI numbers may have been removed automatically.');
			} else {
				form_set_error('imei', 'There was an error with some IMEI numbers. Successfully submitted IMEI numbers were removed from the list below. Please fix the remaining IMEI numbers and continue. (Invalid IMEI Numbers: '.implode(", ", $imeis).')'.$response['message']);
				drupal_add_js('Drupal.behaviors.incomplete_imeis = function() {(function($) {$("#edit-imei").val("'.implode("\n", $imeis).'");})(jQuery);}', 'inline');
			}
		}
	}
}

function unlock_order_recycle_imeis($imeis, $uid, $timestamp, $tool_id, $price, $cost, $customer, $notes, $make, $model) {
	global $language;

	$fresh_imeis = array();
	foreach($imeis as $imei) {
		if(unlock_order_is_imei_present($imei)) {
			$old_order = unlock_order_imei_order_object($imei);
			if(user_access('administer user credits system')) {
				$price = 0.00;	
			}
			unlock_order_update_completion(unlock_order_process_new_order($uid, $timestamp, $tool_id, UNLOCK_FOUND, array($imei), 0.00, $price, $make, $model, $customer, $notes, 'RECYCLED', $old_order->code));
			$params['account'] = user_load($uid);
			$params['order'] = $old_order;
			$params['order']->imei = $imei;
			$params['code'] = $old_order->code;
			if($customer) {
				drupal_mail('unlock_order', 'customeremail', $customer, $language, $params, $params['account']->mail);
			}
			drupal_mail('unlock_order', 'useremail', $params['account']->mail, $language, $params, variable_get('site_mail', ''));
		} else {
			$fresh_imeis[] = $imei;
		}
	}

	return $fresh_imeis;
}

function unlock_order_is_imei_present($imei) {
	return (bool)db_result(db_query("SELECT COUNT(*) FROM {unlock_orders} uo WHERE uo.imei LIKE '%%%s%%' AND uo.status = %d", $imei, UNLOCK_FOUND));
}

function unlock_order_imei_order_object($imei) {
	return db_fetch_object(db_query("SELECT uo.code FROM {unlock_orders} uo WHERE uo.imei LIKE '%%%s%%' AND uo.status = %d", $imei, UNLOCK_FOUND));
}

function is_IMEI_valid($imei){    
    if(!ctype_digit($imei)) return false;
    $len = strlen($imei);
    if(!in_array($len, range(15,18))) return false;

    for($ii=1, $sum=0 ; $ii < $len ; $ii++){
        if($ii % 2 == 0) $prod = 2;
        else $prod = 1;
        $num = $prod * $imei[$ii-1];
        if($num > 9){
          $numstr = strval($num);
          $sum += $numstr[0] + $numstr[1]; 
        }else $sum += $num;
    }

    $sumlast = intval(10*(($sum/10)-floor($sum/10))); //The last digit of $sum
    $dif = (10-$sumlast);
    $diflast = intval(10*(($dif/10)-floor($dif/10))); //The last digit of $dif
    $CD = intval($imei[$len-1]); //check digit

    if($diflast == $CD) return true;

    $odd = !strlen($imei)%2;
	$sum = 0;
	for($i=0;$i<strlen($imei);++$i) {
			$n=0+$imei[$i];
			$odd=!$odd;
		if($odd) {
			$sum+=$n;
		} else {
			$x=2*$n;
			$sum+=$x>9?$x-9:$x;
		}
	}

	return(($sum%10)==0);
}

function unlock_order_filter_submitted_imeis(&$imeis, $new_order) {
	$completed_imeis = array();

	if(isset($new_order['imei_orders']['imei'])) {
		$completed_imeis[] = $new_order['imei_orders']['imei'];
		unlock_order_remove_imeis($new_order['imei_orders']['imei'], $imeis);
	} else {
		foreach($new_order['imei_orders'] as $imei_order) {
			$completed_imeis[] = $imei_order['imei'];
			unlock_order_remove_imeis($imei_order['imei'], $imeis);
		}
	}

	return $completed_imeis;
}

function unlock_order_remove_imeis($completed_imei, &$imeis) {
	foreach($imeis as $key => $imei) {
		if(strpos($imei, $completed_imei) !== FALSE) {
			unset($imeis[$key]);
		}
	}
}

function unlock_order_parse_imeis($imeis) {
	$cleaned_imeis = array();
	$pieces = array_map('trim', explode("\n", $imeis));
	foreach($pieces as $imei) {
		if(is_IMEI_valid($imei)) {
			array_push($cleaned_imeis, $imei);
		}
	}
	
	return $cleaned_imeis;
}

function unlock_order_parse_meids($imeis) {
	$cleaned_imeis = array();
	$pieces = array_map('trim', explode("\n", $imeis));
	foreach($pieces as $imei) {
		if($imei) {
			array_push($cleaned_imeis, $imei);
		}
	}
	
	return $cleaned_imeis;
}

function unlock_order_form_submit($form, $form_values) {
	drupal_goto('user');
}

function unlock_order_process_new_order($user_id, $timestamp, $tool_id, $status, $imeis, $cost, $price, $make, $model, $cust_email, $notes, $remote_order_id, $code = '') {
	//Add order to database if it was successfully submitted to the API, and charge the customer.
	da_user_credits_charge($price*count($imeis), $user_id);
		
	foreach($imeis as $imei) {
		$unlock_order = (object)array(
			'user_id' => $user_id,
			'timestamp' => $timestamp,
			'tool_id' => $tool_id,
			'status' => $status,
			'imei' => $imei,
			'cost' => $cost,
			'price' => $price,
			'make' => $make,
			'model' => $model,
			'cust_email' => $cust_email,
			'notes' => $notes,
			'remote_order_id' => $remote_order_id,
			'code' => $code
		);
	
		drupal_write_record('unlock_orders', $unlock_order);
		return $unlock_order->order_id;
	}
}

function unlock_order_phone_make_options($make_ids) {
	//Parse phone make id array in to a drupal form options array.
	$phone_make_options = array();
	if(isset($make_ids['phonemake_id'])) {
		$phone_make_options[$make_ids['phonemake_id']] = $make_ids['phone_make'];
	} else {
		foreach($make_ids as $make_id) {
			$phone_make_options[$make_id['phonemake_id']] = $make_id['phone_make'];
		}
	}

	return $phone_make_options;
}

function unlock_order_extra_param_options($tool_id) {
	//Render different extra param options array based on the tool id.
	$extra_params = unlock_api_get_required_params($tool_id);
	$options = array('none' => 'Please Select a Service');

	if($tool_id == '83') {
		foreach($extra_params['MODELS'] as $model) {
			$options[$model['id']] = $model['name'];
		}
	} elseif($tool_id == '18' || $tool_id == '19' || $tool_id == '68' || $tool_id == '22' || $tool_id == '23' || $tool_id == '31' || $tool_id == '12') {
		foreach($extra_params['service'] as $service) {
			$options[$service['country']][$service['data'].'__'.$service['country'].' - '.urlencode($service['network'])] = html_entity_decode($service['network']);
		}
	} elseif($tool_id == '46') {
		foreach($extra_params['MEP_LIST'] as $mep) {
			$options[$mep] = $mep;
		}
	} elseif($tool_id == 78 || $tool_id == 81) {
		foreach($extra_params['MODELS'] as $model) {
			$options[$model] = $model;
		}
	} else {
		//General Catching cuz api example got bugs, there are ids with extra params that dun get caught
		foreach($extra_params as $param) {
			if(is_array($param)) {
				foreach($param as $key => $val) {
					$options[$key] = $val;
				}
			}
		}
	}

	return array('title' => $extra_params['PARAM_TYPE'], 'options' => $options);
}
/*End implementation for unlock tool order page*/

//List unlock tools
function unlock_tools() {
	drupal_add_js(drupal_get_path('module', 'unlock_order').'/js/unlock_order_collapser.js');

	//Make sure user is signed in with a wholesale account, or else don't provide links to tools.
	$tools = unlock_api_get_unlocktools();
	$data = array();
	if($tools) {
		if(user_access('place unlocking orders')) {
			$header = array('Tool', '', 'Cost', 'Turn-Around');
			foreach($tools['unlock_tools']['tool'] as $tool) {
				$data[] = array(l($tool['tool_name'], 'unlock-order/'.$tool['tool_id'], array('html' => TRUE)), unlock_order_collapsible(filter_xss(stripslashes($tool['description']), array('a', 'em', 'strong', 'cite', 'code', 'ul', 'ol', 'li', 'dl', 'dt', 'dd', 'br', 'p'))), '<span class="credit-amount">'.unlock_order_markup_price($tool['tool_id'], $tool['price']).'</span>', '<strong>'.$tool['process_time'].'</strong>');
			}
		} else {
			$header = array('Tool', '');
			foreach($tools['unlock_tools']['tool'] as $tool) {
				$data[] = array($tool['tool_name'], filter_xss(stripslashes($tool['description']), array('a', 'em', 'strong', 'cite', 'code', 'ul', 'ol', 'li', 'dl', 'dt', 'dd', 'br', 'p')));
			}
		}
		
		return theme('table', $header, $data);	
	} else {
		return 'Service is temporarily down. Please try again later.';	
	}
}

function unlock_order_collapsible($text) {
	return '<div class="collapsible-widget"><div class="collapsible-text">'.$text.'</div><div class="collapse-toogle-link"><a href="#">More ...</a></div></div>';
}

function unlock_order_retail() {
	return drupal_get_form('unlock_order_retail_form');
}

function unlock_order_retail_form($form_state) {
	drupal_add_js(drupal_get_path('module', 'unlock_order').'/js/unlock_order_retail.js');
	drupal_add_css(drupal_get_path('module', 'unlock_order').'/css/unlock_order_button.css');
	
	$form = array();
	$tool_ids = array();
	$form['single-order'] = array(
		'#type' => 'fieldset',
		'#title' => t('Order Details'),
		'#collapsible' => FALSE,
	);
	
	$form['single-order']['email'] = array(
		'#type' => 'textfield',
		'#title' => 'Your E-mail',
		'#description' => 'Enter a valid e-mail address to send code and instructions.',
		'#required' => TRUE,
		'#size' => 40,
		'#maxlength' => 255
	);

	$form['single-order']['imei'] = array(
		'#type' => 'textfield',
		'#title' => 'IMEI Number',
		'#description' => 'Enter the 15 digit IMEI number of your device',
		'#required' => TRUE,
		'#size' => 20,
		'#maxlength' => 255
	);
	
	$form['single-order']['make'] = array(
		'#type' => 'select',
		'#title' => 'Device Make',
		'#description' => 'What is the make of your phone?',
		'#attributes' => array('class' => 'unlock_retail_makes'),
		'#options' => unlock_order_get_makes($tool_ids),
		'#required' => TRUE
	);
	
	$form['single-order']['network'] = array(
		'#type' => 'select',
		'#title' => 'Select a Network',
		'#attributes' => array('class' => 'unlock_retail_network'),
		'#options' => array('Please select a network'),
		'#required' => TRUE
	);
	
	$form['single-order']['paypal-button'] = array(
		'#type' => 'markup',
		'#value' => '<div class="retail-throbber"></div><div class="retail-order-now"></div>',
	);

	drupal_add_js(array('unlock_order_carriers' => unlock_order_get_carriers($tool_ids)), 'setting');
	return $form;
}

//Helper functions to build on top of the API Stack
function unlock_order_get_carriers($tool_ids) {
	$carriers = array();
	$tools = unlock_api_get_SortedMethodList();

	foreach($tool_ids as $phone_make => $phone_make_tools) {
		foreach($tools['CarrierTools'] as $tool) {
			if(in_array($tool['tool_id'], $phone_make_tools)) {
				$carriers[$phone_make][$tool['country']][$tool['tool_id']] = $tool['ToolName'];
			}
		}
		foreach($tools['ManufacturerTools'] as $tool) {
			if(in_array($tool['tool_id'], $phone_make_tools)) {
				$carriers[$phone_make]['Miscellaneous'][$tool['tool_id']] = $tool['ToolName'];
			}
		}
	}
	
	return $carriers;
}

function unlock_order_get_makes(&$tool_ids) {
	/*
	@Params: None
	@Return: Get a list of all phone make IDs.
	*/

	$tools = unlock_api_get_unlocktools();
	//Provide retail order experience

	$makes = array();
	foreach($tools['unlock_tools']['tool'] as $tool) {
		if(isset($tool['supported']['PhoneMakeID']['phone_make'])) {
			$makes[$tool['supported']['PhoneMakeID']['phone_make']] = $tool['supported']['PhoneMakeID']['phone_make'];
			$tool_ids[$tool['supported']['PhoneMakeID']['phone_make']][] = $tool['tool_id'];
		} else {
			if(isset($tool['supported']['PhoneMakeID'])) {
				foreach($tool['supported']['PhoneMakeID'] as $phone_make) {
					$makes[$phone_make['phone_make']] = $phone_make['phone_make'];
					$tool_ids[$phone_make['phone_make']][] = $tool['tool_id'];
				}
			}
		}
	}
	
	return $makes;
}

function unlock_order_get_makes_from_instructions($instructions) {
	//A less cpu intensive makes fetcher
	$makes = array('Select a Manufacturer');

	foreach($instructions as $instruction) {
		$makes[$instruction['make_id']] = $instruction['make_name'];
	}
	return $makes;
}

function unlock_retail_button($tool_id) {
	module_load_include('inc', 'da_user_credits', 'add_credits');
	
	$response = unlock_api_get_unlocktools($tool_id);
	$tool = $response['unlock_tools']['tool'];
	$content = '';
	
	if($tool) {
		$price = unlock_order_markup_price($tool_id, $tool['price']);
		print '<div class="retail-price"><strong>Price:</strong> <span>'.$price.'</span></div>';
		print da_user_credits_paypal_button($price, base_path().drupal_get_path('module', 'unlock_order').'/images/retailorder.png', 'Single Unlock');
	} else {
		print 'Please select another network.';	
	}
}
/*Unlock Instructions Page*/
function unlock_order_instructions($instruction_id) {
	if($instruction_id) {
		$response = unlock_api_get_instructions($instruction_id);
		print '<div class="instruction-name"><h2>'.$response['make_name'].' Unlocking Instructions</h2></div>'.$response['instructions'];
	} else {
		$response = unlock_api_get_instructions();
		$content = drupal_get_form('unlock_order_instructions_form', unlock_order_get_makes_from_instructions($response['instructions']));
		return $content;
	}
}

function unlock_order_instructions_form($form_state, $makes) {
	drupal_add_js(drupal_get_path('module', 'unlock_order').'/js/unlock_order_instructions.js');
	drupal_add_css(drupal_get_path('module', 'unlock_order').'/css/unlock_order_button.css');
	
	$form['container'] = array('#type' => 'fieldset');
	
	$form['container']['option'] = array(
		'#type' => 'select',
		'#title' => 'View Unlocking Instruction',
		'#options' => $makes,
		'#attributes' => array('class' => 'instructions-select'),
	);
	
	$form['container']['loader'] = array(
		'#type' => 'markup',
		'#value' => '<div class="retail-throbber"></div><div class="instruction-container"></div>'
	);
	
	return $form;
}