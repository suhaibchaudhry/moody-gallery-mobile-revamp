$(document).ready(function() {
	$("#edit-search-theme-form-1").focus(function(srcc) {
        if ($(this).val() == $(this)[0].title) {
			$(this).removeClass("defaultTextActive");
			$(this).val("");
		}
	});

	$("#edit-search-theme-form-1").blur(function() {
		if ($(this).val() == "") {
			$(this).addClass("defaultTextActive");
			$(this).val($(this)[0].title);
		}
	});
	
	$("#edit-search-theme-form-1").blur();        
});