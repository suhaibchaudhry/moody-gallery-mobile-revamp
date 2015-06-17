Drupal.behaviors.order_unlock_statistics = function() {
	$(".prev-month, .next-month").click(function(event) {
		event.preventDefault();
		date = $(this).attr('rel').split(',');
		stats = $('.order-stats');
		
		stats.height(stats.height());
		stats.empty().append('<div class="loading-stats"></div>');
		$('.order-statistics-block').load(Drupal.settings.basePath+"admin/unlock-stats/"+date[0]+"/"+date[1], function() {
			Drupal.behaviors.order_unlock_statistics();	
		});
	});
}