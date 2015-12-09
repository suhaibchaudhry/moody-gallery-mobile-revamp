Drupal.behaviors.mobile_menu = function(context) {
	var $primar_nav = $('.primary_nav', context);
	$primar_nav.prepend('<a class="mobile-menu-trigger" href="#">Menu</a>');
	$('a.mobile-menu-trigger', context).click(function(e) {
		e.preventDefault();
		e.stopPropagation();
		$primar_nav.find('ul').toggleClass('menuExpanded');
	});

	$('.field-field-artist-work', context).append('<a href="#" class="scrollBottom"></a>');

	$('a.scrollBottom', context).click(function(e) {
		e.preventDefault();
		$('html, body').animate({
        		scrollTop: $('.node-content .field:eq(1)').offset().top
   		}, 1000);
	});
}
