Drupal.behaviors.fancyradios = function() {
    $(".fancy-list li > a").live('click', function (event) {
        // First disable the normal link click
        event.preventDefault();

        // Remove all list and links active class.
        $('.fancy-list .active').removeClass("active");

        // Grab the link clicks ID
        var id = this.id;

        // The id will now be something like "link1"
        // Now we need to replace link with option (this is the ID's of the checkbox)
        var newselect = id.replace('fancy-option', 'edit-attributes');

        // Make newselect the option selected.
        $('#'+newselect).attr('checked', true);

        // Now add active state to the link and list item
        $(this).addClass("active").parent().addClass("active");
		
		//Stop bubbling
        return false;
    });	
}