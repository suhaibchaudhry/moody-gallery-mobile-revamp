Drupal.behaviors.mobile_menu = function(context) {
	var $primar_nav = $('.primary_nav', context);
	$primar_nav.prepend('<a class="mobile-menu-trigger" href="#">Menu</a>');
	$('a.mobile-menu-trigger', context).click(function(e) {
		e.preventDefault();
		$primar_nav.find('ul').toggleClass('menuExpanded');
	});
}