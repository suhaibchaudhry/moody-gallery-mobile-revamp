<?php
//Theme breadcrums
function phptemplate_breadcrumb($breadcrumb) {
  if ((module_exists('taxonomy_breadcrumb')) && arg(0) == 'taxonomy' && arg(1) == 'term' && is_numeric(arg(2))) {
    require_once(drupal_get_path('module', 'taxonomy_breadcrumb') . '/taxonomy_breadcrumb.inc');
    $breadcrumb = _taxonomy_breadcrumb_generate_breadcrumb(arg(2));
  }

  //return theme_breadcrumb($breadcrumb);
  
  if (!empty($breadcrumb)) {
    return implode(' > ', $breadcrumb);
  }
}

function phptemplate_get_login_state() {
	global $user;
	if($user->uid) {
		return 'true';	
	} else {
		return 'false';	
	}
}

function phptemplate_preprocess_page(&$vars) {
	//Add themepath for theme js
	drupal_add_js(array('pathToTheme' => base_path().path_to_theme()), 'setting');
	//Seperate primary and secondary tabs
	$vars['tabs2'] = menu_secondary_local_tasks();

	//Make logo dimensions available to theme
	global $theme_key;
	$logo_path = theme_get_setting('logo_path');
	if($logo_path) {
		$dimensions = getimagesize($logo_path);
	} else {
		$dimensions = getimagesize(drupal_get_path('theme', $theme_key).'/logo.png');
	}
	$vars['logo_width'] = $dimensions[0];
	$vars['logo_height'] = $dimensions[1];
	
	//Flag for disabling/enabling children of primary menus
	$show_children = theme_get_setting('show_children');
	if(is_null($show_children) || !$show_children) {
		$vars['primary_links_children'] = '';
	} else {
		$vars['primary_links_children'] = phptemplate_get_primary_children();
	}
}

function phptemplate_preprocess_node(&$vars) {
	//Determine if product is last in row
	if($vars['type'] == 'product') {
		static $i = 1;
		$vars['last_in_row'] = ($i%4 == 0);
		$i++;
	}
	$vars['node_region'] = theme('blocks', 'node_region');
}

function phptemplate_menu_local_tasks() {
  return menu_primary_local_tasks();
}

//Wrap fieldsets into a div
function phptemplate_fieldset($element) {
	if (!empty($element['#collapsible'])) {
		drupal_add_js('misc/collapse.js');

		if (!isset($element['#attributes']['class'])) {
 			$element['#attributes']['class'] = '';
		}

		$element['#attributes']['class'] .= ' collapsible';

		if (!empty($element['#collapsed'])) {
 			$element['#attributes']['class'] .= ' collapsed';
 		}
 	}

	return '<div class=\'fieldset-outer\'><fieldset'. drupal_attributes($element['#attributes']) .'>'. ($element['#title'] ? '<legend>'. $element['#title'] .'</legend>' : '') . (isset($element['#description']) && $element['#description'] ? '<div>'. $element['#description'] .'</div>' : '') . (!empty($element['#children']) ? $element['#children'] : '') . (isset($element['#value']) ? $element['#value'] : '') ."</fieldset></div>\n";
}

//Generate a class for the content container based on the number of sidebars
function phptemplate_content_class($left, $right) {
	if($left && $right) {
		return ' both-bars';
	} elseif($left || $right) {
		return ' one-bar';
	} else {
		return ' no-bars';
	}
}

//Hide form fields from node form
function phptemplate_node_form($form) {
	#disable menu
	//unset($form['menu']);
	
	# disable revisions
	unset($form['revision_information']);

	return theme_node_form($form);
}

function phptemplate_node_submitted($node) {
	return format_date($node->created, 'custom', 'F jS, Y');
}

function phptemplate_trim_string($string, $max_chars) {	
	preg_match('/^.{1,'.($max_chars - 4).'}\b/s', $string, $match);
	if(strlen($string) > $max_chars) {
		return $match[0].' ...';	
	} else {
		return $string;	
	}
}

//Get a rendered list of child elements of the current primary menu page. Styling Works properly for only depth = 1
function phptemplate_get_primary_children() {
	$tree = menu_tree_page_data('primary-links');
	foreach($tree as $menu_item) {
		if($menu_item['link']['in_active_trail']) {
			if($menu_item['below']) {
				return menu_tree_output($menu_item['below']);
			} else {
				return '';	
			}
		}
	}

	return '';
}
//Theme UC Price
function phptemplate_uc_price($value, $context, $options) {
   $output = '';
   if($value != '$0.00') {
  	// Fixup class names.
  	if (!isset($context['class']) || !is_array($context['class'])) {
  	  $context['class'] = array();
  	}
  	foreach ($context['class'] as $key => $class) {
  	  $context['class'][$key] = 'uc-price-'. $class;
  	}
  	$context['class'][] = 'uc-price';
  	// Class the element.
 	$output = '<span class="'. implode(' ', $context['class']) .'">';
 	// Prefix(es).
  	if ($options['label'] && isset($options['prefixes'])) {
    	$output .= '<span class="price-prefixes">'. str_replace(array('List Price: '), array('Retail: '), implode('', $options['prefixes'])) .'</span>';
  	}
  	// Value.
  	$output .= $value;
  	// Suffix(es).
  	if ($options['label'] && isset($options['suffixes'])) {
   		$output .= '<span class="price-suffixes">'. implode('', $options['suffixes']) .'</span>';
  	}
  	$output .= '</span>';
  }
  return $output;
}
