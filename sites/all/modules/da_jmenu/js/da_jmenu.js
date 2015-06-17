$(document).ready(function() {
	$(".collapser").click(function () {
		$(this).next().slideToggle('fast'); 
	});
});