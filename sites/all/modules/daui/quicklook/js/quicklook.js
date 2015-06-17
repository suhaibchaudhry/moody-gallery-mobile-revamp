jQuery.fn.centerDialog = function () {
    this.css("top", (($(window).height() - this.outerHeight()) / 2) + "px");
    this.css("left", (($(window).width() - this.outerWidth()) / 2) + $(window).scrollLeft() + "px");
    return this;
}

Drupal.behaviors.quicklook = function() {
	$('body').append('<div class="quicklook-dialog"></div>');
	var field = $('.field-field-image-cache .field-item');
	
	field.height(field.find('.quicklook-img').height());
	
	field.hover(function() {
		$(this).find('.quicklook-btn-container').fadeIn('fast');
	}, function() {
		$(this).find('.quicklook-btn-container').fadeOut('fast');
	});
	
	$('a.quicklook-btn').click(function(e) {
		e.preventDefault();
		loadQuickLookDialog($(this).attr('href'));
	});
	
	function loadQuickLookDialog(url) {
		var dialog = $('.quicklook-dialog');
		dialog.fadeOut('slow', function() {
			dialog.load(url, function() {
				dialog.centerDialog();
				//Center dialog on resize
				$(window).resize(function() {
					dialog.centerDialog();
				});
				dialog.fadeIn('slow', function() {
					//apply all click behaviours to dialog
					$('.imagelist img').click(function() {
						$('.bigimage a').html('<img src="'+$(this).attr('rel')+'" />');
					});
					
					dialog.click(function(event) {
						event.stopPropagation();
					});
					
					$('.dialogtitle .closebtn').click(function() {
						dialog.fadeOut('slow');
					});
					
					$(document).click(function() {
						dialog.fadeOut('slow');
					});
				});
			});
		});
	}
}