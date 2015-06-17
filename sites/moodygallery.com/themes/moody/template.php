<?php
function phptemplate_filefield_file($file) {
  // Views may call this function with a NULL value, return an empty string.
  if (empty($file['fid'])) {
    return '';
  }

  $path = $file['filepath'];
  $url = file_create_url($path);
  $icon = theme('filefield_icon', $file);
  
  $options = array(
    'attributes' => array(
      'type' => $file['filemime'] . '; length=' . $file['filesize'],
    ),
  );

  return '<div class="filefield-file">'. $icon . l('Download Artist\'s CV', $url, $options) .'</div>';
}

function moody_preprocess_node(&$vars) {
	//Get Parent Objects, update the module later
	$node = $vars['node'];
	$node->parent_nodes = array();
	if(db_table_exists('content_field_featured_artist')) {
		$sql = "SELECT f.nid FROM {content_field_featured_artist} f WHERE f.field_featured_artist_nid = %d";	
	} else {
		$sql = "SELECT n.nid FROM {content_type_exhibition} n WHERE n.field_featured_artist_nid = %d";
	}
	$parent_nodes = db_query($sql, $node->nid);
	while($parent_node = db_fetch_object($parent_nodes)) {
		$node->parent_nodes[] = node_load($parent_node->nid);
	}
}

function moody_preprocess_page(&$vars) {
	if(function_exists('moody_get_front_value') && moody_get_front_value() > 1) {
		foreach($vars['primary_links'] as $id => $link) {
			if(strpos($id, 'menu-268') !== FALSE) {
				$vars['primary_links'][$id]['title'] = 'Current Exhibitions';
			}
		}
	}
}

function phptemplate_parent_nodes($parent_nodes) {
	$content = '';
	foreach($parent_nodes as $parent_node) {
		$year = substr($parent_node->field_event_date[0]['value'], 0, strpos($parent_node->field_event_date[0]['value'], '-'));
		$content .= '<div class="parent_node">'.l($parent_node->title, 'node/'.$parent_node->nid).', Moody Gallery '.$year.'</div>';
	}
	return $content;
}

function moody_date_all_day_label() {
  return '';
}