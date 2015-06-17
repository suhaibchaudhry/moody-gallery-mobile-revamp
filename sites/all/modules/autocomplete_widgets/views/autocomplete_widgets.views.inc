<?php

/**
 * @file
 * Autocomplete widgets integration with Views 3.x.
 */

/**
 * Implementation of hook_views_plugins().
 */
function autocomplete_widgets_views_plugins() {
  return array(
    'exposed_form' => array(
      'autocomplete_widgets_basic' => array(
        'title' => t('Autocomplete widgets'),
        'help' => t('Allow to use autocomplete widgets for CCK Text and Number exposed filters.'),
        'handler' => 'autocomplete_widgets_basic_exposed_form_plugin',
        'uses row plugin' => FALSE,
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
        'parent' => 'basic',
      ),
    ),
  );
}
