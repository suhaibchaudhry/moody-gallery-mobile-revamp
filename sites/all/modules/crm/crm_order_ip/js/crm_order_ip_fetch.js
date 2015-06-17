Drupal.behaviors.crm_order_ip = function () {
	$(".crm_order_ip_geo").one("click", function() {
		var div = $(this);
		div.empty().append('<div class="throbbler"></div>');
		$.getJSON(Drupal.settings.basePath+"crm_order_ip/json/"+Drupal.settings.crm_order_ip.customer_host+"/"+Drupal.settings.crm_order_ip.api_key, function(json) {
			div.empty().hide().append('<strong>Country:</strong> '+json.countryName+'<img src="http://www.ipinfodb.com/img/flags/'+json.countryCode.toLowerCase()+'.gif" alt="'+json.countryCode+'">'+'<br />'+'<strong>State:</strong> '+json.regionName+'<br />'+'<strong>City:</strong> '+json.cityName+'<br />'+'<strong>ISP Zip Code:</strong> '+json.zipCode+'<br />').fadeIn('slow');
		});
	});
};