Drupal.behaviors.widescreen_slider = function() {
	$(window).load(function() {
		$('#widescreen-slideshow').cycle({fx: 'scrollLeft', pause: 1, pauseOnPagerHover: 1, easing: Drupal.settings.widescreen_slider.animation, speed: Drupal.settings.widescreen_slider.speed, timeout: Drupal.settings.widescreen_slider.delay, pager: '.pager_container'});	
	});
}