Drupal.behaviors.zoomview = function() {
	var options = {  
		zoomType: 'reverse',  
		lens:true,  
		preloadImages: true,  
		alwaysOn:false,  
		zoomWidth: 415,  
		zoomHeight: 300,  
		xOffset:5,
		yOffset:0,  
		position:'right',
		showEffect: 'fadein',
		hideEffect: 'fadeout',
		imageOpacity: .5,
		title: false
	};
	$('.zoomview').jqzoom(options);
	
	$('.field-field-image-cache .field-item::first-child').addClass('bigthumb');
	$('.field-field-image-cache .field-item::last-child').addClass('lastthumb');
}