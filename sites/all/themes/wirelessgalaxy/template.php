<?php
function phptemplate_show_compatibility($parent_nodes) {
	if(isset($parent_nodes)) {
		$content = "<p><strong>Compatible with:</strong></p><ul class=\"compatible-products\">";
	
		foreach($parent_nodes as $node) {
			$content .= '<li>';
			$content .= '<p>'.l($node->title, 'node/'.$node->nid).'</p>';
			$content .= l(theme('imagecache', 'teaser_image', $node->field_image_cache[0]['filepath'], $node->field_image_cache[0]['data']['alt'], $node->field_image_cache[0]['data']['title']), 'node/'.$node->nid, array('html' => true));
			$content .= '</li>';
		}
		$content .= "</ul>";
	} else {
		$conent = '';
	}
		
		return $content;
}

function phptemplate_render_teaser_elements($nid, $image_field, $title, $node_url, $sale_price, $add_to_cart_form, $attributes, $top_terms) {
	static $gcount = 1;
	$class = (($gcount%4) == 0) ? ' prdt-tsr-last' : '';
	$add_to_cart_form = _str_replace_first('<option value="" selected="selected">Please select</option>', '', $add_to_cart_form);
	//$add_to_cart_form = empty($attributes) ? $add_to_cart_form : phptemplate_choose_attr_link($attributes, $node_url);
	
	$content = '<div id="product-'.$nid.'" class="product-teaser">';
	$content .= '<div class="prdt-information'.$class.'">';
	$content .= '<div class="full-node-link"><p><a href="'.$node_url.'">'.$title.'</a></p></div>';
	$content .= '<div class="teaser-image"><p><a href="'.$node_url.'">'. theme('imagecache', 'teaser_image', $image_field[0]['filepath'], $image_field[0]['data']['alt'], $image_field[0]['data']['title']) .'</a></p></div>';
	$content .= '<div class="price-buy"><p class="p-price">'.$sale_price.'</p>'.$add_to_cart_form.'</div>';
	$content .= '<div class="top-terms">'.$top_terms.'</div>';
	$content .= '</div>';
	$content .= '<div class="prdt-btm-padd"></div>';
	$content .= '</div>';
	
	$gcount++;
	
	return $content;
}

function phptemplate_setup_tooltips() {
	drupal_add_css(drupal_get_path('theme','wirelessgalaxy').'/tooltip/css/vtip.css', 'theme');
	drupal_add_js(drupal_get_path('theme','wirelessgalaxy').'/tooltip/js/vtip.js', 'theme');
	drupal_add_js(array('themePath' => drupal_get_path('theme','wirelessgalaxy')), 'setting');
}

function phptemplate_get_selected_term_for_node($label_text, $node, $vid) {
	$terms = taxonomy_node_get_terms_by_vocabulary($node, $vid);
	foreach($terms as $term) {
		if(empty($term->description)) {
			$tooltip = '';
		} else {
			$tooltip = phptemplate_get_theme_image('mark.png', array('alt' => '', 'class' => 'vtip', 'title' => $term->description));
		}
		return $label_text.':<span class="available">'.$term->name.'</span>'.$tooltip;
	}
}

function phptemplate_list_terms($node, $vids, $heading = TRUE, $wrapper_div = TRUE, $show = 'all', $prepend = '') {
	//KN algo, could be made into an N + K, change back if function issues. All styles are implemented in the CSS.
	$content = '';
	
	$terms = taxonomy_node_get_terms($node);
	foreach($vids as $vid => $heading_text) {
		$list_content = '';
		$vocab_content = '';
	
		$i = 0;
		if($wrapper_div) {
			$vocab_content .= '<div id="term-list-'.$vid.'" class="term-list">';
		}
		if($heading) {
			$vocab_content .= '<h3>'.check_plain($heading_text).'</h3>';
		}
		$vocab_content .= '<ul>';
		foreach($terms as $term) {
			if($term->vid == $vid) {
				$vocab_content .= '<li>'.$prepend.check_plain($term->name).'</li>';
				$i++;
			}
			if(is_numeric($show) && $i == $show) {
				break;
			}
		}
		$vocab_content .= '</ul>';
		if($wrapper_div) {
			$vocab_content .= '</div>';
		}
		if($i > 0) {
			$main_content .= $vocab_content;
		}
	}
	
	return $main_content;
}

function phptemplate_uc_product_price($price, $context, $options = array()) {
  return uc_price($price, $context, $options);
}

function phptemplate_uc_price($value, $context, $options) {
	return $value;
}

function phptemplate_render_tabs($tabs_array, $instock) {
		if($instock) {
			$script = 'jquery.tabs.trigger.js';	
		} else {
			$script = 'jquery.tabs.strigger.js';	
		}
	
		drupal_add_css(drupal_get_path('theme','wirelessgalaxy').'/jtabs/css/jquery.tabs.css', 'theme');
		drupal_add_js(drupal_get_path('theme','wirelessgalaxy').'/jtabs/js/jquery.tabs.js', 'theme');
		drupal_add_js(drupal_get_path('theme','wirelessgalaxy').'/jtabs/js/'.$script, 'theme');
		$tabs = '';
		$menu = '<ul>';
		foreach($tabs_array as $link => $tab) {
			$menu .= ' <li><a href="#'.$link.'">'.$tab['title'].'</a></li>';
			$tabs .= '<div id="'.$link.'">';
			$tabs .= $tab['content'];
			$tabs .= '</div>';
		}
		$menu .= '</ul>';
		$content = '<div id="prodinfo">';
		$content .= $menu;
		$content .= $tabs;
		$content .= '</div>';

		return $content;
}

function phptemplate_render_status($stock_status, &$available_flag) {
	$class = '';
	$message = '';
	switch($stock_status) {
		case 'instock':
			$class = 'available';
			$message = 'In Stock - Ships in 24 to 48 Hours';
			$available_flag = TRUE;
			break;
		case 'backordered':
			$class = 'available';
			$message = 'Backordered - Ships in 48 to 72 Hours'.phptemplate_get_theme_image('mark.png', array('alt' => '', 'class' => 'vtip', 'title' => 'Backordered Items are available at our 
vendors and need to be shipped to our location for quality control before going 
out to you. These orders usually take an extra 4 to 6 days to process. Please 
choose shipping accordingly.<br />
<br />
NOTICE: Majority of the stores online do not carry most of their products in 
house. However, Wireless Galaxy being the largest cellular wholesale provider 
in the nation, usually ships directly from its own warehouse. In the rare 
occasion a product goes out of stock, we like to keep you posted. :) <br />
<br />
For further details, or if you have a question regarding this product Call us @ 1-800-604-GLXY (4599).'));
			$available_flag = TRUE;
			break;
		case 'outofstock':
			$class = 'unavailable';
			$message = 'Out of Stock - This product is currently not available.';
			$available_flag = FALSE;
			break;
		case 'discontinued':
			$class = 'unavailable';
			$message = 'Discontinued - This product will not be available';
			$available_flag = FALSE;
			break;
		case 'automatic':
			//Modify later when Automatic Syncing is implemented, access the quantity table and display the appropriate message using the proper SKUs.
			$class = 'available';
			$message = 'Backordered - Ships in 48 to 72 Hours';
			$available_flag = TRUE;
			break;
	}
	return '<span class="'.$class.'">'.$message.'</span>';
}

function phptemplate_render_gallery($image_field, $title) {
	$content = '<div id="gallery-container">';
	$content .= '<div id="gallery-main-image">';
	$content .= l(theme('imagecache', 'product_big_thumb', $image_field[0]['filepath'], $image_field[0]['data']['alt'], $image_field[0]['data']['title']), imagecache_create_path('product_full_view', $image_field[0]['filepath']), array( 'html' => TRUE, 'attributes' => array('rel' => 'lightbox[product]')));
	$content .= '</div>';
	$content .= _wgtheme_social_buttons($title);
	$content .= _wgtheme_generate_gallery_jpane($image_field);
	$content .= '</div>';
	return $content;
}

function _wgtheme_social_buttons($title) {
	$path = isset($_GET['q']) ? $_GET['q'] : '<front>';
	$link_t = 'http://twitter.com/home?status=Checking out a '.$title.' @ '.url($path, array('absolute' => TRUE));
	$link_d = 'http://digg.com/submit?url='.url($path, array('absolute' => TRUE));
	
	$content = '<div id="socialbuttons">';
	$content .= l(phptemplate_get_theme_image('socialbuttons/tweetthis.gif', array('alt' => 'Tweet This', 'class' => 'twitterbtn')), $link_t, array('html' => TRUE));
	$content .= l(phptemplate_get_theme_image('socialbuttons/digg.gif', array('alt' => 'Digg It', 'class' => 'twitterbtn')), $link_d, array('html' => TRUE));
	$content .= '</div>';
	return $content;
}

function _wgtheme_generate_gallery_jpane($image_field) {
	if(count($image_field) > 1) {
		drupal_add_css(drupal_get_path('theme', 'wirelessgalaxy').'/jcarousel/css/skin.css', 'theme');
		drupal_add_js(drupal_get_path('theme', 'wirelessgalaxy').'/jcarousel/js/jquery.jcarousel.js', 'theme');
		drupal_add_js(drupal_get_path('theme', 'wirelessgalaxy').'/jcarousel/js/jquery.jcarousel.trigger.js', 'theme');
		
		$content = '<div id="gallery-carousel-container">';
		$content .= '<ul id="gallery-carousel" class="jcarousel-skin-tango">';
		foreach($image_field as $image) {
			$content .= '<li>'.l(theme('imagecache', 'product_small_thumb', $image['filepath'], $image['data']['alt'], $image['data']['title']), imagecache_create_path('product_full_view', $image['filepath']), array( 'html' => TRUE, 'attributes' => array('rel' => 'lightbox[product]'))).'</li>';
		}
		$content .= '</ul>';
		$content .= '</div>';
		return $content;
	} else {
		return '';
	}
}

function phptemplate_get_overview($content) {
	//Gets the first Paragraph from the content as the overview.
	$start = strpos($content, '<p>')+3;
	$end = strpos($content, '</p>');
	$generated_summary = substr($content, $start, ($end-$start));
	if(strpos($content, $generated_summary) > 50) {
		return substr($content, 0, 255);
	}
	return $generated_summary;
}

function phptemplate_uc_usps_option_label($service) {
  $output = 'U.S. Postal Service - ';
  $service_tag = substr($service, 9);
  
  if(strpos($service_tag, 'International') !== FALSE) {
	  if(strpos($service_tag, 'First-Class') !== FALSE) {
		  $output .= 'International Air Mail (10 - 14 days)';
	  } elseif(strpos($service_tag, 'Priority') !== FALSE) {
		  $output .= 'International Priority Mail (8 - 12 days)';
	  } elseif(strpos($service_tag, 'Express') !== FALSE) {
		  $output .= 'International Express Mail (3 - 5 days)';
	  } else {
		$output .= $service_tag;  
	  }
  } else {
	  if(strpos($service_tag, 'First-Class') !== FALSE) {
		  $output .= 'First-Class Mail (5 - 7 days)';
	  } elseif(strpos($service_tag, 'Priority') !== FALSE) {
		  $output .= 'Priority Mail (3 - 4 days)';
	  } elseif(strpos($service_tag, 'Express') !== FALSE) {
		  $output .= 'Overnight Express Mail (1 - 2 days)';
	  } else {
		$output .= $service_tag;  
	  }
  }
  
  return $output;
  /*
  if(strpos($service_tag, 'First-Class Mail Parcel') !== FALSE) {
  	$output .= 'First-Class Mail (5 - 7 days)';
  } elseif(strpos($service_tag, 'Priority Mail') !== FALSE) {
  	$output .= 'Priority Mail (3 - 4 days)';
  } elseif(strpos($service_tag, 'Express Mail') !== FALSE) {
  	$output .= 'Overnight Express Mail (1 - 2 days)';
  } elseif(strpos($service_tag, 'First-Class Mail International Package') !== FALSE) {
  	$output .= 'International Air Mail (10 - 14 days)';
  } elseif(strpos($service_tag, 'Priority Mail International') !== FALSE) {
  	$output .= 'International Priority Mail (8 - 12 days)';
  } elseif(strpos($service_tag, 'Express Mail International') !== FALSE) {
 	 $output .= 'International Express Mail (3 - 5 days)';
  } else {
  	$output .= $service_tag;
  }
  */
}

function phptemplate_breadcrumb($breadcrumb) {
  if (!empty($breadcrumb)) {
    return implode(' &gt; ', $breadcrumb);
  }
}

function phptemplate_get_ie_styles($version) {
		$content = '<!--[if IE '.$version.']>'."\n";
  		$content .= '<link type="text/css" rel="stylesheet" media="all" href="'. base_path() . path_to_theme() .'/style_ie'.$version.'.css" />'."\n";
		$content .= '<![endif]-->'."\n";
		return $content;
}

function phptemplate_get_theme_image($image_name, $attributes = array('alt' => '')) {
  return '<img src="'.base_path().path_to_theme().'/images/'.$image_name.'"'.drupal_attributes($attributes).' />';
}
function phptemplate_render_logo($image) {
	return l(phptemplate_get_theme_image($image, array('alt' => '', 'height' => 70, 'width' => 213)), '<front>', array('html' => TRUE));
}
function phptemplate_get_mc_class($barcounter) {
	if($barcounter == 0) {
		return 'mc-nobars';
	} elseif($barcounter == 1) {
		return 'mc-onebar';
	} else {
		return 'mc-bothbars';
	}
}

function phptemplate_get_cw_class($barcounter) {
	if($barcounter == 0) {
		return 'cw-nobars';
	} elseif($barcounter == 1) {
		return 'cw-onebar';
	} else {
		return 'cw-bothbars';
	}
}

function _str_replace_first($search, $replace, $subject) {
	$subject_original = $subject;
	$len = strlen($search);    
	$pos = 0;
	$pos = strpos($subject,$search,$pos);
	if($pos !== false) {                
		$subject = substr($subject_original,0,$pos);
		$subject .= $replace;
		$subject .= substr($subject_original,$pos+$len);
		$subject_original = $subject;
	}
	return($subject);
}

function _da_related_accs($related) {
	$content = '';
	if(is_array($related)) {
		foreach($related as $prod) {
			$prod->title = check_plain($prod->title);
			$content .= node_view($prod, TRUE, FALSE, FALSE);
		}
	} else {
		$content = $related;
	}

	return $content;
}

function wirelessgalaxy_preprocess_node(&$variables) {
	$variables['similar'] = theme_blocks('similar');
}