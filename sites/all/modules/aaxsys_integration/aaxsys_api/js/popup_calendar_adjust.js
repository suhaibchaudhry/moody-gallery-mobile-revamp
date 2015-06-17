Drupal.behaviors.aaxsys_popup_calendar_adjust = function() {
	var begin_field = $(".aaxsys_api_date_begin_picker");
	begin_field.change(function(event) {
		//console.log($(this).val());
		$this = $(this);
		var end_field = $(".aaxsys_api_date_end_picker");
		if($this.val().length > 0 && end_field.val().length == 0) {
			var end_date = Date.parseExact($this.val(), "MM/dd/yyyy");
			end_date.add(1).days();
			end_field.val(end_date.toString("MM/dd/yyyy"));
		}
	});
}