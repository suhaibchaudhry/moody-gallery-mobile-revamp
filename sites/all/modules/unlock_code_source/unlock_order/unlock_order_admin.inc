<?php
function unlock_order_admin() {
	return drupal_get_form('unlock_order_pricing_form');
}

function unlock_order_pricing_form($form_state) {
	$form = array();
	$retail_roles = user_roles(FALSE, 'place retail orders');
	$wholesale_roles = user_roles(TRUE, 'place unlocking orders');
	$roles = $retail_roles + $wholesale_roles;
	$values = unserialize(variable_get('unlock_order_pricing', ''));

	$form['default_markup'] = array(
      '#type' => 'textfield', 
      '#title' => t('Default Markup'), 
      '#default_value' => isset($values['default_markup']) ? $values['default_markup'] : 0, 
      '#size' => 10, 
      '#description' => 'The default amount to markup on unlock tools. Will be used only when the markup defined for a user role is zero. USE NUMBERS ONLY.', 
      '#required' => TRUE,
    );
	
	$form['table_begin'] = array(
		'#type' => 'markup',
		'#value' => '<table class="unlock-pricing-chart">',
	);
	
	$form['table_headers'] = array(
		'#type' => 'markup',
		'#value' => unlock_order_pricing_chart_headers($roles),
	);
	
	$step = variable_get('unlock_order_pricing_increments', 0.5);
	$max_price = variable_get('unlock_order_pricing_limit', 18);
	$i = 0;
	$j = 0;

	while($j <= $max_price/$step) {
		if($j == 0) {
 			$form['row-start-markup-'.$j] = array(
				'#type' => 'markup',
				'#value' => '<tr>'
			);
		}
		
		foreach($roles as $rid => $role) {
			$form['r_m-'.$rid.'-'.$j] = array(
				'#type' => 'textfield', 
    		  	'#title' => t('$'.number_format($i, 2).' - $'.number_format($i+$step, 2)),
				'#prefix' => '<td>',
				'#suffix' => '</td>',
      			'#default_value' => isset($values[$rid][$j]) ? $values[$rid][$j] : 0, 
      			'#size' => 10, 
				'#required' => TRUE,
      			'#description' => 'Amount to markup for this price range on unlock tools for '.$role.'.'
			);
			
			if($j == $max_price/$step) {
				$form['r_m-'.$rid.'-'.$j]['#title'] = t('More than $'.number_format($i, 2));
			}
		}

		if($j == $max_price-1 || $j == 0) {
			$form['row-end-markup-'.$j] = array(
				'#type' => 'markup',
				'#value' => '</tr>'
			);
		} else {
			$form['row-end-markup-'.$j] = array(
				'#type' => 'markup',
				'#value' => '</tr><tr>'
			);
		}

		$j++;
		$i += $step;
	}

	$form['table_end'] = array(
		'#type' => 'markup',
		'#value' => '</table>',
	);
	
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => 'Update',
	);

	return $form;
}

function unlock_order_pricing_form_submit($form, $form_values) {
	drupal_set_message('Pricing chart updated.');

	$values = array();
	$matches = array();
	
	$values['default_markup'] = $form_values['values']['default_markup'];
	foreach($form_values['values'] as $key => $val) {
		if(strpos($key, 'r_m-') !== FALSE) {
			preg_match_all('/-[0-9]+/', $key, $matches);
			$rid = (int)substr($matches[0][0], 1);
			$bracket = (int)substr($matches[0][1], 1);
			$values[$rid][$bracket] = $val;
		}
	}

	variable_set('unlock_order_pricing', serialize($values));
}

function unlock_order_pricing_chart_headers($roles) {
	$content = '';
	$content .= '<tr>';
	foreach($roles as $rid => $role) {
		$content .= '<th>'.$role.'</th>';
	}
	$content .= '</tr>';
	
	return $content;
}

function unlock_order_pricing_settings_admin() {
	return drupal_get_form('unlock_order_pricing_settings_form');
}

function unlock_order_pricing_settings_form($form_state) {
	$form = array();
	
	$form['unlock_order_pricing_limit'] = array(
		'#type' => 'textfield',
		'#title' => t('Maximum price to adjust for'),
		'#default_value' => variable_get('unlock_order_pricing_limit', 18),
		'#size' => 10,
		'#description' => t("Prices above this number will have a fixed markup."),
		'#required' => TRUE,
	);
	
	$form['unlock_order_pricing_increments'] = array(
		'#type' => 'textfield',
		'#title' => t('Adjustment Increments'),
		'#default_value' => variable_get('unlock_order_pricing_increments', 0.5),
		'#size' => 10,
		'#description' => t("Markups can be adjusted between these increments."),
		'#required' => FALSE,
	);

	return system_settings_form($form);
}

//Email Form
function unlock_order_email_templates_admin() {
	return drupal_get_form('unlock_order_email_templates_form');
}

function unlock_order_email_templates_form($form_state) {
	$form = array();
	
	$form['customeremail'] = array(
		'#type' => 'textarea',
		'#title' => t("Emails to Reseller's Customers"),
		'#default_value' => variable_get('customeremail', ''),
		'#description' => t("These emails are sent to customers of resellers that use the websites when an unlock code is found."),
	);
	
	$form['useremail'] = array(
		'#type' => 'textarea',
		'#title' => t("Emails to Reseller"),
		'#default_value' => variable_get('useremail', ''),
		'#description' => t("This email is sent to a reseller when the status of an order changes."),
	);
	
	$form['manageremail'] = array(
		'#type' => 'textarea',
		'#title' => t("Emails to Admin"),
		'#default_value' => variable_get('manageremail', ''),
		'#description' => t("This email is sent to the admin when the credits on the main account are below the threshold value."),
	);

	return system_settings_form($form);
}