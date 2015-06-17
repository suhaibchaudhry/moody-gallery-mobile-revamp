Drupal.behaviors.unlock_order_insturctions = function() {
	$('.instructions-select').change(function() {
		if($(this).val() != 0) {
			$('.retail-throbber').css('display', 'block');
			$('.instruction-container').empty();
			$('.instruction-container').load(Drupal.settings.basePath+'unlock-instructions/'+$(this).val(), function() {
				$('.retail-throbber').css('display', 'none');
			});
		}
	});
}