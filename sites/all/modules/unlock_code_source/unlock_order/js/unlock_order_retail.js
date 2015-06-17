Drupal.behaviors.unlock_order_retails = function() {
	UnlockOrderRetailRefreshNetworks($('.unlock_retail_makes').val());
	
	$('.unlock_retail_makes').change(function() {
		UnlockOrderRetailRefreshNetworks($(this).val());
	});

	$('.unlock_retail_network').change(function() {
		UnlockOrderGetButton($('.unlock_retail_network').val());
	});
	
	$('#edit-email, #edit-imei').bind('keyup', function(event) {
		UnlockOrderUpdateProductName($('.unlock_retail_network').val());
	});
	
	function UnlockOrderRetailRefreshNetworks(make) {
		var networks = Drupal.settings.unlock_order_carriers[make];
		var content = '';
		$.each(networks, function(country, tools) {
			content = content + '<optgroup label="'+country+'">';
			$.each(tools, function(tool_id, tool_name) {
				content += '<option value="'+tool_id+'">'+tool_name+'</option>';
			});
			content = content + '</optgroup>';
		});
		
		$('.unlock_retail_network').html(content);
		UnlockOrderGetButton($('.unlock_retail_network').val());
	}
	
	function UnlockOrderGetButton(tool_id) {
		$('.retail-throbber').css('display', 'block');
		$('.retail-order-now').empty();
		$('.retail-order-now').load(Drupal.settings.basePath+'retail-order-button/'+tool_id, function() {
			$('.retail-throbber').css('display', 'none');
			UnlockOrderUpdateProductName($('.unlock_retail_network').val());
			
			$('.submit-paypal').click(function(event) {
				if($('#edit-email').val() == '' || $('#edit-imei').val() == '') {
					alert('E-mail and IMEI are required to continue');
					event.stopPropagation();
					event.preventDefault();
				}
			});
		});
	}
	
	function UnlockOrderUpdateProductName(tool_id) {
		$('.retail-order-now input[name="item_name"]').val('IMEI: '+$('#edit-imei').val()+' - '+$('#edit-email').val());
		$('.retail-order-now input[name="item_number"]').val('mid-'+tool_id);
	}
}