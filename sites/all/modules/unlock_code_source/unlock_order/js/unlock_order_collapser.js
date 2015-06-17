Drupal.behaviors.unlock_order_collapser = function() {
	var adjustheight = 40;
	
	$('.collapsible-text').css('height', adjustheight).css('overflow', 'hidden');
	$(".collapse-toogle-link a").toggle(function() {
		$(this).parent().parent().find('.collapsible-text').css('height', 'auto').css('overflow', 'visible');
		$(this).text("Less ...");
	}, function() {
		$(this).parent().parent().find('.collapsible-text').css('height', adjustheight).css('overflow', 'hidden');
		$(this).text("More ...");
	});
}