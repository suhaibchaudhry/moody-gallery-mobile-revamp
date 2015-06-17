Drupal.behaviors.da_measurements = function() {
	$('.collapsible-howto a').click(function(event) {
		event.preventDefault();
		$(this).parent().find('.hidden-markup').stop(true, true).slideToggle('slow');
	});
}