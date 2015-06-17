Drupal.behaviors.fblike = function() {
	$('.fblike-container').append('<iframe src="'+Drupal.settings.basePath+'fblike-button?fburl='+encodeURIComponent(document.URL)+'" scrolling="no" frameborder="0"></iframe>');
}