Drupal.behaviors.frontPageGrid = function() {
	var $rows = $('.view-front .views-row');
	if($rows.length > 1) {
		var covers = $rows.find('.views-field-field-cover-image-fid img');
		$rows.width(covers.width());

		var height = covers.eq(0).height();
		covers.each(function() {
			if($(this).height() < height) {
				height = $(this).height();
			}
		});	
		
		$rows.find('.views-field-field-cover-image-fid').height(height);
	} else if($rows.length == 1) {
		$('.view-front .views-row').css({width: '100%'});
	}
}