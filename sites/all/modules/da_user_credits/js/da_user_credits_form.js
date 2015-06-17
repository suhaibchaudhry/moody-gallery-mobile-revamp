Drupal.behaviors.da_user_credits_form = function() {
	$('.purchase-credits form').submit(function() {
		return false;
	});
}