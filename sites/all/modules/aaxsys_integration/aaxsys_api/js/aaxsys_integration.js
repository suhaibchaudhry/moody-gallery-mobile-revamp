Drupal.behaviors.aaxsys_integration = function() {
	var $dialog = $("#dialog").dialog({
		autoOpen: false,
		show: "drop",
		hide: "drop",
		width: 926,
		height: 750,
		modal: true
	});
	
	function dialogNew(url, $dialog, postURL, dialog_title) {
		//$dialog.data("width.dialog", width);
		//$dialog.data("height.dialog", height);
		//$('#dialog').dialog("option", "width", width);
		//$('#dialog').dialog("option", "height", height);
		//$('.ui-widget-header .ui-icon').hide();
		$dialog.html('<div class="dialog-loader"></div>');
		$dialog.dialog("open");
		$dialog.dialog("option", 'title', dialog_title);
		$.post(url,{'InformationLink': postURL},function(html) {
			$dialog.html(html);
			Drupal.attachBehaviors();
			$('.ui-dialog-content').css('padding', 0);
			//$('.ui-widget-header .ui-icon').css({left: $('.ui-dialog-content').width()-20, position: 'absolute'});
			//$('.ui-widget-header .ui-icon').show();
		});
	}
	
	$('.property-info-link').click(function(event) {
		event.preventDefault();
		event.stopPropagation();
		dialogNew(Drupal.settings.basePath+'property-details', $dialog, $(this).attr('rel'), $(this).attr('title'));
	});
}

function external_integration_popup(url) {
	window.open(url, 'newWindow', 'status=0,height=720,width=680,resizable=1');
}