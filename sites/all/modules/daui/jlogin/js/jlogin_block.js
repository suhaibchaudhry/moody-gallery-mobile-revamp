Drupal.behaviors.jlogin_block = function() {
	var jloginBlock = $('.jlogin-block');
	var jlink = $('.jlogin-link a');

	//Prevent fadeout by clicking jloginBlock
	jloginBlock.click(function(event) {
		event.stopPropagation();	
	});

	//initially hide if there is no error
	if(jloginBlock.find('.error').length == 0) {
		jloginBlock.css('display', 'none');
	} else {
		$(document).bind('click.jcartBodyClicks', function() {
			jloginBlock.fadeOut('slow');
			$(this).unbind('click.jcartBodyClicks');	
		});	
	}

	jlink.bind('click.jloginClicks', function(event) {
		event.preventDefault();
		jloginBlock.fadeIn('slow', function() {
			$(document).bind('click.jcartBodyClicks', function() {
				jloginBlock.fadeOut('slow');
				$(this).unbind('click.jcartBodyClicks');	
			});
		});
	});
}