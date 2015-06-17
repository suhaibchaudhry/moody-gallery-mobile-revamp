<?php
function da_user_credits_ipn_handler() {
	if(variable_get('da_user_credits_transaction_mode', 0)) {
		$gateway = 'https://www.paypal.com/cgi-bin/webscr';
	} else {
		$gateway = 'https://sandbox.paypal.com/cgi-bin/webscr';
	}

	if(function_exists('get_magic_quotes_gpc')) {
		$get_magic_quotes_exists = true; 
	}
	
	$req = 'cmd=_notify-validate';
	foreach ($_POST as $key => $value)  {  
		if($get_magic_quotes_exists == true && get_magic_quotes_gpc() == 1){  
			$value = urlencode(stripslashes($value)); 
		} else { 
			$value = urlencode($value); 
		} 
		$req .= '&'.$key.'='.$value; 
	}
	
	$response = drupal_http_request($gateway, array(), 'POST', $req);
	if($response->code == '200' && strcmp($response->data, "VERIFIED") == 0) {
		//This is a valid API response
		if(da_user_credits_transaction_isprocessed($_POST['txn_id'])) {
			if(strcmp($_POST['payment_status'], 'Completed') == 0 && da_user_credits_status_ischanged($_POST['txn_id'], $_POST['payment_status'])) {
				//Update Status
				$ipn_response = da_user_credits_build_ipn_object(da_user_credits_get_transaction_id($paypal_transaction_id));
				drupal_write_record('da_ipn_responses', $ipn_response, 'transaction_id');
				//Credit User
				da_user_credits_add_credits(da_user_credits_calculate_credits((float)$_POST['mc_gross']), da_user_credits_parse_uid($_POST['item_number']));
			}
		} else {
			//Insert Into DB
			$ipn_response = da_user_credits_build_ipn_object();
			drupal_write_record('da_ipn_responses', $ipn_response);

			if(strcmp($_POST['payment_status'], 'Completed') == 0) {
				//Credit User
				da_user_credits_add_credits(da_user_credits_calculate_credits((float)$_POST['mc_gross']), da_user_credits_parse_uid($_POST['item_number']));
			}
		}
	} else {
		//Report admin of a hacker's attack attempt.
		watchdog('da_user_credits', 'An invalid IPN response was posted to the handler. IP: '.ip_address(), WATCHDOG_WARNING);
	}

	print 'PayPal IPN Handler';
}

function da_user_credits_transaction_isprocessed($paypal_transaction_id) {
	return db_result(db_query("SELECT COUNT(*) FROM {da_ipn_responses} WHERE paypal_txn_id = '%s'", $paypal_transaction_id));
}

function da_user_credits_get_transaction_id($paypal_transaction_id) {
	return db_result(db_query("SELECT transaction_id FROM {da_ipn_responses} WHERE paypal_txn_id = '%s'", $paypal_transaction_id));
}

function da_user_credits_status_ischanged($paypal_transaction_id, $new_status) {
	return (db_result(db_query("SELECT status FROM {da_ipn_responses} WHERE paypal_txn_id = '%s'", $paypal_transaction_id)) != $new_status);
}

function da_user_credits_build_ipn_object($transaction_id = '') {
	$da_ipn_response = array(
		'paypal_txn_id' => $_POST['txn_id'],
		'timestamp' => time(),
		'status' => $_POST['payment_status'],
		'customer_uid' => da_user_credits_parse_uid($_POST['item_number']),
		'payer_email' => urldecode($_POST['payer_email']),
		'first_name' => $_POST['first_name'],
		'last_name' => $_POST['last_name'],
		'total_payment' => $_POST['mc_gross'], //Total Payments Made
		'credits' => da_user_credits_calculate_credits((float)$_POST['mc_gross']), //Credits purchased
		'service_fee' => $_POST['custom'], //Service Fee Charged
		'paypal_fee' => $_POST['mc_fee'],
	);

	if(is_int($transaction_id)) {
		$da_ipn_response['transaction_id'] = $transaction_id;
	}

	return (object)$da_ipn_response;
}

function da_user_credits_parse_uid($item_number) {
	return str_replace('uid-', '', $item_number);
}

function da_user_credits_calculate_credits($payment) {
	$fee = (float)$_POST['custom'];
	if($fee > 0) {
		return $payment - $fee;
	} else {
		return $payment;	
	}
}