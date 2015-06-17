Drupal.behaviors.da_user_credits_table = function() {
	 var refreshTotal = function(element) {
		var amount = Math.round(parseFloat($(element).val().replace('$', '').match(/[0-9]*\.?[0-9]*/)[0]));
		if(isNaN(amount)) {
			amount = 0;
		}
		//Update chart total price
		$('.regular-pay .total-price').text(amount.toFixed(2));
		
		//Apply service fee if needed
		var threshold = parseFloat(Drupal.settings.da_user_credits.threshold);
		var fee = parseFloat(Drupal.settings.da_user_credits.fee)/100;
		if(amount <= threshold) {
			$('.regular-pay .service-fee').text((amount*fee).toFixed(2));
			$('.regular-pay input[name="custom"]').val((amount*fee).toFixed(2));
			amount *= 1+fee;
		} else {
			$('.regular-pay .service-fee').text((0).toFixed(2));
			$('.regular-pay input[name="custom"]').val((0).toFixed(2));
		}

		$('.regular-pay .total-fee').text(amount.toFixed(2));

		//update paypal button amount
		$('.regular-pay input[name="amount"]').val(amount.toFixed(2));
	}
	
	refreshTotal($('#edit-payment-amount'));
	$('#edit-payment-amount').bind('keyup', function(event) {
		refreshTotal(this);
	});
	
	$('input.submit-paypal').click(function(event) {
		event.preventDefault();
		event.stopPropagation();
		
		if(parseInt($('td.total-price').text()) < 25) {
			alert("Only transactions more than $25.00 are allowed at the moment.");
		} else {
			$('div.paypal-button form').submit();
		}
	});

}