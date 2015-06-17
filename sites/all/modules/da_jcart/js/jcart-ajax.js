$(document).ready(function() {
	//css class .btpane is WG theme specifig, please change later.
	$("#browsepane").load(Drupal.settings.basePath+'jcart', function() {
		$(".clickitey").click(function () {
			if($("#mdpane:animated").length == 0) {
   				$("#mdpane").slideToggle("fast"); 
				$(".jcrtarrow").toggleClass("arrow-open");
			}
		});
	}).hide().fadeIn('200');
});