var run_flag = true;
Drupal.behaviors.fading_nav = function(context) {
	if(run_flag) {
		//Elements
		var container = $('.primary_nav', context);
		var links = $('.primary_nav a', context);

		//set nav to take full width
		var parent_width = container.width();
		links.width(Math.floor(parent_width/links.size()) - parseInt(links.css('margin-right')));

		//setup the overlay and hover animation
		var copy = container.clone();
		var position = container.position();
		if(position) {
			copy.addClass('primary_nav_js_overlay').css('top', container.position().top).css('left', container.position().left).css('width', container.width()).insertAfter(container).find('a').hover(function() {
				$(this).stop().animate({opacity: 0}, 1000);
			}, function() {
				$(this).stop().animate({opacity: 1}, 1000);
			});

			//Fix overlap on resize
			$(window).resize(function() {
	  			copy.css('left', container.position().left);
			});

			//Repeatedly fix menu overlap
			setInterval(function() {
	      		copy.css('left', container.position().left);
			}, 100);
		}
		run_flag = false;
	}
}