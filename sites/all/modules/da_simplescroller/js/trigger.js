(function($) {
	$(function() {
		$("ul.scroll").simplyScroll({
			autoMode: 'loop',
			horizontal: false,
			pauseOnHover: true,
			frameRate: 30,
			speed: 1
		});
	});
})(jQuery);