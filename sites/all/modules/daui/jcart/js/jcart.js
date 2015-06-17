var run_once = true;
Drupal.behaviors.jcart = function() {
	if(run_once) {
		var jwindow = $('.jcart-window');
		var jlink = $('.jcart-link a');
		var jpreloader = $('.jcart-preloader');

		//Center the window under the link
		jwindow.css('left', jwindow.offset().left-(jwindow.width()/2));
	
		//Initially hide jwindow
		jwindow.css('display', 'none');
	
		//Append Number of items to link
		jQuery.get(Drupal.settings.basePath+'jcart-numberofitems', function(data) {
			jlink.append('<span>'+data+'</span>');
		});

		//Prevent fadeout by clicking jwindow
		jwindow.click(function(event) {
			event.stopPropagation();
		});

		jlink.click(function(event) {
			event.preventDefault();
			jwindow.fadeIn('slow', function() {
				$(this).load(jlink.attr('href'), function() {
					//Add handler to close link
					$('.jcart-close a').bind('click.jcartCloseClicks', function(event) {
						event.preventDefault();
						jwindow.fadeOut('slow');
						//Stop fadout on outside clicks
						$(document).unbind('click.jcartCloseClicks');
					});
				});

				//Add handler to on click to anywhere outside
				$(document).bind('click.jcartCloseClicks', function() {
					jwindow.fadeOut('slow');
					$(this).unbind('click.jcartCloseClicks');	
				});
			});
		});

		run_once = false;
	}
}