if((typeof Drupal.Views !== "undefined") && (typeof Drupal.Views.Ajax !== "undefined") && (typeof Drupal.Views.Ajax.handleErrors == "undefined")) {
	Drupal.Views.Ajax.handleErrors = function(xhr, ajax_path) {}
}