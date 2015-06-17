$(document).ready(function() {
	$(".clickitey").click(function () {
		if($("#mdpane:animated").length == 0) {
   			$("#mdpane").slideToggle("fast"); 
			$(".jcrtarrow").toggleClass("arrow-open");
		}
	});
});