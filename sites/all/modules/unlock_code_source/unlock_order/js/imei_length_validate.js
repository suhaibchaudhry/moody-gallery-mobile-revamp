Drupal.behaviors.imei_length_validate = function() {
	var found = false;
	$('#unlock-order-form').submit(function(event) {
		$.each($('#edit-imei').val().split("\n"), function(key, value) {
			if((value.length > 0 && value.length < 15) || value.length > 18 || (value.length == 0 && key == 0)) {
				alert("All IMEIs must be between 15 to 18 characters long consisting of only digits. IMEI on Line #"+(key+1)+" is invalid.");
				found = false;
				return false;
			} else {
				found = true;
			}
		});

		if($('select.unlock-service').val() == 'none') {
			alert('Please Select a Service to continue');
			found = false;
		}

		if(found) {
			button = $("#unlock-order-form .form-submit");
			button.attr('disabled', 'disabled');
			button.val('Placing Order ...');
		}
		
		return found;
	});
}