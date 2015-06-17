(function($){
  Drupal.behaviors.cck_slider = function(context) {
  var settings = new Array();
  var iter = 0;
  var slider_settings = Drupal.settings.cck_slider;
  /* Cycle through each cck slider */
  $(".cck-slider-wrapper").each(function(){
    $(this).find(".ui-slider-handle").html("&nbsp;");
    /* Get the field name */
    var field_name = this.id;
    /* Get the field attributes */
    var field_settings = slider_settings[field_name];
    /* Hide the textfield */
    $(this).find(".cck-slider-field").hide();
    /* Add the min/max labels */
    $(this).find(".cck-slider-widget-min").html(parseInt(field_settings['min']));
    $(this).find(".cck-slider-widget-max").html(parseInt(field_settings['max']));
    /* Create the slider */
    $(this).find(".cck-slider-widget").slider({
      value: parseInt(field_settings['default']),
      min: parseInt(field_settings['min']),
      max: parseInt(field_settings['max']),
      step: parseInt(field_settings['increment_size']),
      slide: function( event, ui ) {
        /* Update the textfield with the new value */
	$(this).parent(".cck-slider-widget-wrapper").siblings(".form-item").children(".cck-slider-field").val(ui.value);
	/* Update the slider handle to show the new current value */
	$(this).find(".ui-slider-handle").html(ui.value);
      }
    });
    /* Set the text above the slider */
    $(this).find(".ui-slider-handle").text(parseInt(field_settings['default']));
  });
}
})(jQuery);
