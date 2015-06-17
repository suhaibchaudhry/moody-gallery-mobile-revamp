<?php
function da_user_credits_add($user) {
	drupal_set_message('<strong>Important:</strong> We prefer paypal as our method of payment. Credit purchases less than $'.variable_get('da_user_credits_threshold_amount', 0).' will be subjected to a '.variable_get('da_user_credits_service_fee', 0).'% service charge when using the regular Paypal payment method. ($1 USD = 1 credit).');

	$content = '<div class="purchase-credits"><h3>Purchase Credits</h3>'.drupal_get_form('da_user_credits_purchase_form').'</div>';
	$content .= da_user_credits_regular_pay($user->uid);

	return $content;
}

function da_user_credits_regular_pay($uid) {
	$fee = variable_get('da_user_credits_service_fee', 0);
	$threshold = variable_get('da_user_credits_threshold_amount', 0);
	
	drupal_add_js(array('da_user_credits' => array('fee' => $fee, 'threshold' => $threshold)), 'setting');
	drupal_add_js(drupal_get_path('module', 'da_user_credits').'/js/da_user_credits_table.js');
	
	$content .= '<div class="regular-pay">';
	$content .= '<table class="creditchart">';
	$content .= '<tr><td>Credit Price</td><td>$1 USD</td></tr>';
	$content .= '<tr><td>Total Credits</td><td class="total-price">0.00</td></tr>';
	$content .= '<tr><td>Service Fee</td><td class="service-fee">0.00</td></tr>';
	$content .= '<tr><td><strong>Total Amount:</strong></td><td class="total-fee">0.00</td></tr>';
	$content .= '</table>';
	$content .= '<div class="paypal-button">'.da_user_credits_paypal_button(variable_get('da_user_credits_threshold_amount', 0), base_path().drupal_get_path('module', 'da_user_credits').'/images/checkout.png', 'Credit Purchase for Unlock Bazaar', TRUE).'</div>';
	$content .= '</div>';
	
	return $content;
}

function da_user_credits_purchase_form() {
	drupal_add_js(drupal_get_path('module', 'da_user_credits').'/js/da_user_credits_form.js');
	
	$form = array();
	
	$form['payment_method'] = array(
		'#type' => 'radios',
		'#title' => t('Select Payment Method'),
		'#options' => array('Paypal', 'Paypal Masspay'),
		'#default_value' => 0,
	);
	
	$form['payment_amount'] = array(
		'#type' => 'textfield',
		'#title' => t('Amount to Purchase'),
		'#size' => '10',
		'#default_value' => variable_get('da_user_credits_threshold_amount', 0),
		'#description' => 'Please enter a dollar amount of credits you wish to purchase'
	);

	return $form;
}

function da_user_credits_paypal_button($charge_amount, $button_image_path, $decsciption, $send_to_ipn = FALSE) {
	global $user;

	if(variable_get('da_user_credits_transaction_mode', 0)) {
		$gateway = 'https://www.paypal.com/cgi-bin/webscr';
	} else {
		$gateway = 'https://sandbox.paypal.com/cgi-bin/webscr';
	}
	$content = '<form action="'.$gateway.'" method="post" class="paypal-button-form">';
	$content .= '<input type="hidden" name="cmd" value="_xclick">';
	$content .= '<input type="hidden" name="business" value="'.variable_get('da_user_credits_username', '').'">';
	$content .= '<input type="hidden" name="lc" value="US">';
	$content .= '<input type="hidden" name="item_name" value="'.$decsciption.'">';
	$content .= '<input type="hidden" name="item_number" value="uid-'.$user->uid.'">';
	$content .= '<input type="hidden" name="amount" value="'.$charge_amount.'">';
	$content .= '<input type="hidden" name="currency_code" value="USD">';
	$content .= '<input type="hidden" name="button_subtype" value="services">';
	$content .= '<input type="hidden" name="no_note" value="0">';
	$content .= '<input type="hidden" name="cn" value="Add special instructions to the seller">';
	$content .= '<input type="hidden" name="no_shipping" value="1">';
	$content .= '<input type="hidden" name="rm" value="1">';
	$content .= '<input type="hidden" name="return" value="'.variable_get('da_user_credits_success', '').'">';
	$content .= '<input type="hidden" name="cancel_return" value="'.variable_get('da_user_credits_cancel', '').'">';
	$content .= '<input type="hidden" name="custom" value="0">'; //Let JS insert custom params, such as fee charged.
	$content .= '<input type="hidden" name="bn" value="PP-BuyNowBF:btn_buynowCC_LG.gif:NonHosted">';
	if($send_to_ipn) {
		$content .= '<input type="hidden" name="notify_url" value="'.url('ipn-handler', array('absolute' => TRUE)).'">';
	}
	$content .= '<input class="submit-paypal" type="image" src="'.$button_image_path.'" border="0" name="submit" alt="PayPal - The safer, easier way to pay online!">';
	$content .= '<img alt="" border="0" src="https://www.paypalobjects.com/en_US/i/scr/pixel.gif" width="1" height="1">';
	$content .= '</form>';
	
	return $content;
}