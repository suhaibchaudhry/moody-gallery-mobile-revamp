$(document).ready(function() {
	$("#edit-da-drop-51").change(function() {
		tid = $("#edit-da-drop-51 option:selected").val();
		window.location.replace("products/cellphones/"+tid);
	});
	
	$("#edit-da-drop-22").change(function() {
		tid = $("#edit-da-drop-22 option:selected").val();
		window.location.replace("products/cellphones/"+tid);
	});
});