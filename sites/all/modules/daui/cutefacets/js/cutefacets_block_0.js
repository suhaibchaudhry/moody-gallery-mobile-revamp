function cuteFacet(filterIdentifier, operator, single, vid, context) {
	this.filterIdentifier = filterIdentifier;
	this.operator = operator;
	this.single = single;
	this.vid = vid;
	this.wtype = 0;
	//this.children = new Array();
	this.primary = false;
	this.context = context;
	this.facet;

	this.mapTaxonomyTree(vid, context);
}

cuteFacet.prototype.mapTaxonomyTree = function(vid, context) {
	var display_widgets = Drupal.settings.cutefacets_settings.display_widgets;
	for(var v in display_widgets) {
		var display_widget = display_widgets[v];
		if(vid == display_widget.vid) {
			this.wtype = display_widget.wtype;
			break;
		}
	}

	var term_trees = Drupal.settings.cutefacets_settings.term_trees;
	var filter_map = Drupal.settings.cutefacets_settings.filter_map;
	for(var p in term_trees) {
		var term_tree = term_trees[p];
		if(vid == term_tree.pvid) {
			for(var fm in filter_map) {
				if(term_tree.vid == filter_map[fm].vid) {
					term_tree.child_facet = new cuteFacet(filter_map[fm].filter, filter_map[fm].operator, filter_map[fm].single, term_tree.vid, context);
					break;
				}
			}
			//this.children.push(term_tree);
		}
	}

	var primary_vocab = Drupal.settings.cutefacets_settings.primary_vocabs;
	for(var pv in primary_vocab) {
		if(primary_vocab[pv] == vid) {
			this.primary = true;
			break;
		}
	}
	
	if(this.wtype == 0) {
		this.constructListFacet();
	} else {
		this.constructSliderFacet();
	}
}

Drupal.behaviors.cutefacets_priceRange = function(context) {
	if($('.views-widget-filter-sell_price', context).length > 0) {
		$('#facet-price-slider', context).data('submissionLock', false);
		var price_facet = $('<div class="facet facet-price-slider" id="facet-price-slider" />');
		//var i = 0;

		price_facet.append('<h3>Price</h3>');
		price_facet.append('<div class="price-slider-selections" />');
		price_facet.append('<div class="slider" />');
		var max_price = Math.ceil(Drupal.settings.cutefacets_price_settings.max_price);
		//var $selections = filter.find('select option');
		var slider = price_facet.find('.slider');
		var sliderOptions = {
			animate: "fast",
			range: true,
			min: 0,
			max: max_price,
			values: [0, max_price],
			change: function( event, ui ) {
				//var filter = $('.views-exposed-widgets .views-widget-filter-price-slider', context);
				$('.views-widget-filter-sell_price #edit-sell-price-min').val(ui.values[0]);
				$('.views-widget-filter-sell_price #edit-sell-price-max').val(ui.values[1]);
				price_facet.find('.price-slider-selections').text('$'+ui.values[0].toFixed(2)+' - $'+ui.values[1].toFixed(2));
				
				if(!$('#facet-price-slider', context).data('submissionLock')) {
					cuteFacet.startPreloader(context);
					$('.view-filters form', context).trigger('submit');
					//CuteFacetsSubmit.apply($('.view-filters form', context).get(0));
				}
			},
			slide: function(event, ui) {
				//var filter = $('.views-exposed-widgets .views-widget-filter-price-slider', context);
				price_facet.find('.price-slider-selections').text('$'+ui.values[0].toFixed(2)+' - $'+ui.values[1].toFixed(2));
			}
		};
		
		price_facet.find('.price-slider-selections').text('$0.00 - $'+max_price);
		slider.slider(sliderOptions);
		
		var $container = '#block-cutefacets-0 .cutefacets-primary-facets, #block-cutefacets-2 .cutefacets-primary-facets';
		$($container, context).append(price_facet);
	}
}

cuteFacet.prototype.constructSliderFacet = function() {
	$('#facet-'+this.filterIdentifier, this.context).data('submissionLock', false);
	if($('#facet-'+this.filterIdentifier, this.context).length > 0) {
		this.facet = $('#facet-'+this.filterIdentifier, this.context);
	} else {
		var $this = this;
		if($this.single) {
			var facet_class = ' facet-single';
		} else {
			var facet_class = ' facet-multiple';
		}
		var facet = $('<div class="facet facet-slider'+facet_class+'" id="facet-'+$this.filterIdentifier+'" />');
		var filter = $('.views-exposed-widgets .views-widget-filter-'+$this.filterIdentifier, $this.context);
		var i = 0;
	
		facet.append('<h3>'+filter.find('label').text()+'</h3>');
		facet.append('<div class="selections" />');
		facet.append('<div class="slider" />');
		
		$this.facet = facet;
		var $selections = filter.find('select option');
		var slider = $this.facet.find('.slider');
		
		
		var textOptions = [];
		$selections.each(function(index, el) {
			textOptions.push($(el).text());			
		});
		/*
		var textWidth = slider.width() / (textOptions.length - 1);
		*/
		if(this.single) {
			//Implement Later
			var sliderOptions = {};
		} else {
			var sliderOptions = {
				animate: "fast",
				range: true,
				min: 0,
				max: $selections.length-1,
				values: [0, $selections.length-1],
				change: function( event, ui ) {
					var filter = $('.views-exposed-widgets .views-widget-filter-'+$this.filterIdentifier, $this.context);
					var $selections = filter.find('select option');
					var i = ui.values[0];
					$selections.attr('selected', false);
					if($this.operator == 'and' || ui.values[0] != 0 || ui.values[1] != $selections.length-1) {
						while(i <= ui.values[1]) {
							$selections.eq(i).attr('selected', true);
							i++;
						}
					}
					
					$this.facet.find('.selections').text($selections.eq(ui.values[0]).text()+' - '+$selections.eq(ui.values[1]).text());
					
					if(!$('#facet-'+$this.filterIdentifier, $this.context).data('submissionLock')) {
						cuteFacet.startPreloader($this.context);
						$('.view-filters form', $this.context).trigger('submit');
					}
				},
				slide: function(event, ui) {
					var filter = $('.views-exposed-widgets .views-widget-filter-'+$this.filterIdentifier, $this.context);
					var $selections = filter.find('select option');
					$this.facet.find('.selections').text($selections.eq(ui.values[0]).text()+' - '+$selections.eq(ui.values[1]).text());
				}
			};
		}

		slider.slider(sliderOptions);
		//slider.after('<div class="ui-slider-legend"><p style="width:' + textWidth + 'px;">' + textOptions.join('</p><p style="width:' + textWidth + 'px;">') +'</p></div>')
		if(Drupal.settings.cutefacets_settings.label_sliders == "1") {
			var slider_legend = $('<div class="slider-legend"></div>');
			slider.after(slider_legend);
			
			var opt = slider.data('slider').options;
			// Get the number of possible values
			var vals = opt.max - opt.min;
	
			// Position the labels
			for (var i = 0; i < textOptions.length; i++) {
				// Create a new element and position it with percentages
				// Add the element inside #slider
				slider_legend.append('<div style="width: '+100/(textOptions.length)+'%;">'+textOptions[i]+'</div>');
			}
			
			slider.wrap('<div class="slider-padd"></div>');
		}

		if(!$this.single && $this.operator == 'and') {
			$(window).load(function() {
				$('.views-exposed-widgets .views-widget-filter-'+$this.filterIdentifier, $this.context).find('select option').attr('selected', true);
				cuteFacet.startPreloader($this.context);
				$('.view-filters form', $this.context).trigger('submit');
			});
		}


		$this.facet.find('.selections').text($selections.eq(0).text()+' - '+$selections.eq($selections.length-1).text());
		
		if($this.primary) {
			var $container = '#block-cutefacets-0 .cutefacets-primary-facets, #block-cutefacets-2 .cutefacets-primary-facets';
		} else {
			var $container = '#block-cutefacets-0 .cutefacets-secondary-facets, #block-cutefacets-2 .cutefacets-secondary-facets';
		}

		$($container, $this.context).append($this.facet);
	}
}

cuteFacet.prototype.constructListFacet = function() {
	if($('#facet-'+this.filterIdentifier, this.context).length > 0) {
		this.facet = $('#facet-'+this.filterIdentifier, this.context);
	} else {
		var $this = this;
		if($this.single) {
			var facet_class = ' facet-single';
		} else {
			var facet_class = ' facet-multiple';
		}
		var facet = $('<div class="facet facet-list'+facet_class+'" id="facet-'+$this.filterIdentifier+'" />');
		//facet.data('cuteFacet', this);
		var filter = $('.views-exposed-widgets .views-widget-filter-'+$this.filterIdentifier, $this.context);
		var i = 0;
	
		facet.append('<h3>'+filter.find('label').text()+'</h3>');
		
		filter.find('select option').each(function(index) {
			if($this.single == 1 && i == 0) {
				var text = 'All';
			} else {
				var text = $(this).text();
			}
			
			if($(this).is(':selected')) {
				var checked_class = ' checked-option';
				//console.log('RAM');
				$this.activateChildFacet(parseInt($(this).val()), false);
				//console.log(parseInt($(this).val()));
			} else {
				var checked_class = '';
			}
			
			if(index%2 == 0) {
				checked_class += ' even';
			}
			
			var term_id = $(this).val();
			var additional_icons = '';
			
			if(typeof Drupal.settings.cutefacets_settings.term_images == "object") {
				var term_images = Drupal.settings.cutefacets_settings.term_images;
				
				if(term_id in term_images) {
					additional_icons += '<span class="tximg" style="background-image: url('+term_images[term_id]+');"></span>';
				}
			}
			
			facet.append('<a href="#" class="facet-option'+checked_class+'" rel="'+$this.filterIdentifier+'" rev="'+term_id+'"><span class="checked"></span>'+additional_icons+'<span class="opt-title">'+text+'</span></a>');
			i++;
		});
	
		$this.facet = facet;
		
		if($this.primary) {
			var $container = '#block-cutefacets-0 .cutefacets-primary-facets, #block-cutefacets-2 .cutefacets-primary-facets';
		} else {
			var $container = '#block-cutefacets-0 .cutefacets-secondary-facets, #block-cutefacets-2 .cutefacets-secondary-facets';
		}
		
		$this.facet.find('a.facet-option').bind('click', function(e) {
			e.preventDefault();
			e.stopPropagation();
			var option = $('.views-exposed-widgets .views-widget-filter-'+$this.filterIdentifier, $this.context).find('option[value="'+$(this).attr('rev')+'"]');
			
			if($this.single) {
				var checked_option = $this.facet.find('.checked-option');
				checked_option.removeClass('checked-option');
				option.attr('selected', 'selected');
				$this.disableChildFacet(parseInt(checked_option.attr('rev')), false);
				$(this).addClass('checked-option');
				$this.activateChildFacet(parseInt($(this).attr('rev')), true);
			} else {
				if($(this).is('.checked-option')) {
					option.attr('selected', false);
					$(this).removeClass('checked-option');
					//if($this.primary) {
						$this.disableChildFacet(parseInt($(this).attr('rev')), true);
					//}
				} else {
					option.attr('selected', 'selected');
					$(this).addClass('checked-option');
					//if($this.primary) {
						$this.activateChildFacet(parseInt($(this).attr('rev')), true);
					//}
				}
			}
			cuteFacet.startPreloader($this.context);
			$('.view-filters form', $this.context).trigger('submit');
		});
		
		$($container, $this.context).append($this.facet);
	}
}

cuteFacet.prototype.activateChildFacet = function(tid, animation) {
	var term_trees = Drupal.settings.cutefacets_settings.term_trees;
	for(var i in term_trees) {
		if(term_trees[i].tid == tid) {
			var facet = $('#facet-'+term_trees[i].child_facet.filterIdentifier, this.context);
			//console.log(facet);
			if(animation) {
				facet.stop(true, true).fadeIn(500);
			} else {
				facet.css('display', 'block');
			}
		}
	}
}

cuteFacet.prototype.disableChildFacet = function(tid, animation) {
	var term_trees = Drupal.settings.cutefacets_settings.term_trees;
	for(var i in term_trees) {
		if(tid == term_trees[i].tid) {
			if(cuteFacet.disableVid(term_trees[i].child_facet.filterIdentifier, term_trees[i].vid, this.context, term_trees[i].child_facet)) {
				var child_facet = $('#facet-'+term_trees[i].child_facet.filterIdentifier, this.context);
				if(animation) {
					child_facet.stop(true, true).fadeOut(500);
				} else {
					child_facet.css('display', 'none');
				}
			}
		}
	}
}

cuteFacet.disableVid = function(childFilterIdentifier, vid, context, $this) {
	var term_trees = Drupal.settings.cutefacets_settings.term_trees;
	for(var i in term_trees) {
		if(term_trees[i].vid == vid) {
			if($('.views-exposed-widgets .views-exposed-widget option[value="'+term_trees[i].tid+'"]', context).attr('selected')) {
				return false;
			}
		}
	}

	cuteFacet.diactivateSelections(childFilterIdentifier, context, $this);
	return true;
}

cuteFacet.diactivateSelections = function(filterIdentifier, context, $this) {
	if($this.wtype == 0) {
		$('#facet-'+filterIdentifier+' a', context).removeClass('checked-option');
		$('.views-exposed-widgets .views-widget-filter-'+filterIdentifier, context).find('option').attr('selected', (!$this.single && $this.operator == 'and'));
	} else {
		//$this.slider.slider('option', 'min', 10);
		var slider = $('#facet-'+filterIdentifier+' .slider', context);
		if($this.single) {
			//Implement Later
		} else {
			$('#facet-'+filterIdentifier, context).data('submissionLock', true);
			slider.slider('values', 0, slider.slider('option', 'min'));
			slider.slider('values', 1, slider.slider('option', 'max'));
			$('#facet-'+filterIdentifier, context).data('submissionLock', false);
		}
	}
}

cuteFacet.startPreloader = function(context) {
	$('.view', context).each(function() {
		if($(this).find('.view-filters').size()) {
			$(this).find('.view-content').html('<div class="cutefacets-loader"></div>');
		}
	});
}

Drupal.behaviors.facetInitialization = function(context) {
	var filter_map = Drupal.settings.cutefacets_settings.filter_map;
	//$cuteFacets = new Array();
	//Construct all facets before mapping taxonomy tree routes
	for(var f in filter_map) {
		new cuteFacet(filter_map[f].filter, filter_map[f].operator, filter_map[f].single, filter_map[f].vid, context);
	}
	
	//for(var f in filter_map) {
	//	$cuteFacets[f].mapTaxonomyTree(filter_map[f].vid, context);
	//}
}