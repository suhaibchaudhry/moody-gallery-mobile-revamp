<?php
function theme_unlock_details($tool_name, $description, $process_time, $price, $supported) {
	$content = '';
	$content .= '<div class="unlock-details">';
	$content .= '<h3>'.$tool_name.' Remote IMEI Unlocks</h3>';
	$content .= '<div class="unlock-description">';
	$content .= '<p><strong>Processing Time: </strong>'.$process_time.'</p>';
	$content .= '<p><strong>Price: </strong><span class="credit-amount">'.$price.'</span></p>';
	$content .= '<span>Unlock Description</span>';
	$content .= $description;
	$content .= '</div>';
	$content .= '<div class="unlock-supported">';
	$content .= '<span>Supported Devices for this Unlock Tool</span>';
	$content .= '<ul class="supported-phones">';
	if(isset($supported['phone_make'])) {
		$content .= '<li>'.$supported['phone_make'].'</li>';
	} else {
		foreach($supported as $phone) {
			$content .= '<li>'.$phone['phone_make'].'</li>';
		}
	}
	$content .= '</ul>';
	$content .= '</div>';
	$content .= '</div>';
	
	return $content;
}