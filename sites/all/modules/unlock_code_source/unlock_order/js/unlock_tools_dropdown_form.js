Drupal.behaviors.unlock_tools_dropdown_form = function() {
	$('.tool-dropdown-selection').change(function() {
		window.location.replace(Drupal.settings.basePath+"unlock-order/"+$(this).val());
	});
}