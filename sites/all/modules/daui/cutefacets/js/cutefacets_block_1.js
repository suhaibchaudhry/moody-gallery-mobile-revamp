Drupal.behaviors.cutefacetsChecks = function() {
	$('#block-cutefacets-1 a.facet-option').click(function(e) {
		e.preventDefault();
		e.stopPropagation();
		$(this).toggleClass('checked-option');	
	});	
	
	$('#block-cutefacets-1 a.browse-plans').click(function(e) {
		e.preventDefault();
		e.stopPropagation();
		
		var param = '';
		$i = 0;
		$('.cutefacets-vocabulary').each(function(index, element) {
			var $this = $(this);
			if($this.data('multiple')) {
				var $options = $this.find('.checked-option');
				$options.each(function(index, element) {
					if($i > 0) {
						param += '&';
					}
					param += $this.data('filter')+'[]='+$(this).attr('rel');
					$i++;
				});
			} else {
				var $val = $this.find('select').val();
				//console.log($val);
				if($val != 0) {
					if($i > 0) {
						param += '&';
					}
					
					param += $this.data('filter')+'[]='+$val;
					$i++;
				}
			}

		});
		
		if(param) {
			param = '?'+param;
		}

		window.location = Drupal.settings.basePath+Drupal.settings.cutefacets_settings.views_path+param;
	});
}