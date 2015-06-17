<?php
// $Id: block_tab.admin.inc,v 1.2 2011/02/09 05:55:22 hosszukalman Exp $
/**
 * @file
 *
 */


function block_tab_admin_settings() {
  $regions = system_region_list(variable_get('theme_default', 'garland'));

  $form = array();
  $form['block_tab-regions'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Regions should be tabified'),
    '#options' => $regions,
    '#default_value' => variable_get('block_tab-regions', array()),
  );

  return system_settings_form($form);
}