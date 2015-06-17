<?php

/**
 * @file
 */

function theme_stormknowledgebase_list($header, $kbs) {
  $rows = array();
  $topics = stormattribute_attributes_bydomain('Knowledge base topic');

  foreach ($kbs as $kb) {
    $n = new stdClass();
    $n->nid = $kb->nid;
    $n->uid = $kb->uid;
    $n->type = 'stormknowledgebase';
    $rows[] = array(
      l($kb->title, 'node/'. $kb->nid),
      $topics[values][$kb->topic],
      array(
        'data' => storm_icon_edit_node($n, $_GET) .'&nbsp;'. storm_icon_delete_node($n, $_GET),
        'class' => 'storm_list_operations',
      ),
    );
  }
  $o = theme('table', $header, $rows);
  return $o;
}

function theme_stormknowledgebase_view($node, $teaser = FALSE, $page = FALSE) {
  drupal_add_css(drupal_get_path('module', 'storm') . '/storm-node.css', 'module');
  
  $node = node_prepare($node, $teaser);
  $l_pos = 1; // Used to increase the link position number (see issue 814820)
  
  $node->content['links'] = array(
    '#prefix' => '<div class="stormlinks"><dl>',
    '#suffix' => '</dl></div>',
    '#weight' => $l_pos++,
  );

  $node->content['group1'] = array(
    '#prefix' => '<div class="stormfields">',
    '#suffix' => '</div>',
    '#weight' => module_exists('content') ? content_extra_field_weight($node->type, 'group1') : -20,
  );

  $node->content['group1']['topic'] = array(
    '#prefix' => '<div class="topic">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('Topic'), stormattribute_value('Knowledge base topic', $node->topic)),
    '#weight' => 1,
  );

  $node->content['body_field'] = array(
    '#prefix' => '<div class="stormbody">',
    '#suffix' => '</div>',
    '#value' => theme('storm_view_item', t('Description'), $node->content['body']['#value']),
    '#weight' => module_exists('content') ? content_extra_field_weight($node->type, 'body_field') : -18,
  );
  unset($node->content['body']);
  
  return $node;
}

