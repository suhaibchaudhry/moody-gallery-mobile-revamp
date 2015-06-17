<?php

/**
* Add include and setting files
*/

require_once(drupal_get_path('theme', 'mobile_jquery') . '/theme-settings.php');
require_once(drupal_get_path('theme', 'mobile_jquery') . '/includes/mobile_jquery.system.inc');
require_once(drupal_get_path('theme', 'mobile_jquery') . '/includes/mobile_jquery.theme.inc');
require_once(drupal_get_path('theme', 'mobile_jquery') . '/includes/mobile_jquery.comments.inc');
require_once(drupal_get_path('theme', 'mobile_jquery') . '/includes/mobile_jquery.forms.inc');
require_once(drupal_get_path('theme', 'mobile_jquery') . '/includes/mobile_jquery.menus.inc');
require_once(drupal_get_path('theme', 'mobile_jquery') . '/includes/mobile_jquery.pager.inc');
require_once(drupal_get_path('theme', 'mobile_jquery') . '/includes/mobile_jquery.filter.inc');
require_once(drupal_get_path('theme', 'mobile_jquery') . '/includes/mobile_jquery.taxonomy.inc');
require_once(drupal_get_path('theme', 'mobile_jquery') . '/includes/mobile_jquery.user.inc');
require_once(drupal_get_path('theme', 'mobile_jquery') . '/includes/mobile_jquery.upload.inc');


/**
 * Initialize theme settings
 */
global $theme_key;
if (db_is_active()) {
  mobile_jquery_initialize_theme_settings($theme_key);
}

/**
 * Implementation of template_preprocess_maintenance_page()
 */
function mobile_jquery_preprocess_maintenance_page(&$vars) {
  if (db_is_active()) {
    mobile_jquery_preprocess_page($vars);
  }
}

/**
 * Implementation of hook_preprocess()
 * 
 * @param $vars
 * @param $hook
 * @return Array
 */
function mobile_jquery_preprocess(&$vars, $hook) {
  // Collect all information for the active theme.
  $themes_active = array();
  global $theme_info;

  $vars['use_global']             = theme_get_setting('use_global');
  
  $vars['global_icon']            = theme_get_setting('global_icon');
  $vars['global_inset']           = theme_get_setting('global_inset');
  $vars['global_theme']           = theme_get_setting('global_theme');
  $vars['global_spliticon']       = theme_get_setting('global_spliticon');
  
  $vars['list_item_icon']         = $vars['use_global']?$vars['global_icon']:theme_get_setting('list_item_icon');
  $vars['list_item_inset']        = $vars['use_global']?$vars['global_inset']:theme_get_setting('list_item_inset');
  $vars['list_item_theme']        = $vars['use_global']?$vars['global_theme']:theme_get_setting('list_item_theme');
  $vars['list_item_dividertheme'] = $vars['use_global']?$vars['global_theme']:theme_get_setting('list_item_dividertheme');
  $vars['list_item_counttheme']   = $vars['use_global']?$vars['global_theme']:theme_get_setting('list_item_counttheme');
  $vars['list_item_splittheme']   = $vars['use_global']?$vars['global_theme']:theme_get_setting('list_item_splittheme');
  $vars['list_item_spliticon']    = $vars['use_global']?$vars['global_spliticon']:theme_get_setting('list_item_spliticon');
  
  $vars['menu_item_icon']         = $vars['use_global']?$vars['global_icon']:theme_get_setting('menu_item_icon');
  $vars['menu_item_inset']        = $vars['use_global']?$vars['global_inset']:theme_get_setting('menu_item_inset');
  $vars['menu_item_theme']        = $vars['use_global']?$vars['global_theme']:theme_get_setting('menu_item_theme');
  $vars['menu_item_dividertheme'] = $vars['use_global']?$vars['global_theme']:theme_get_setting('menu_item_dividertheme');
  $vars['menu_item_counttheme']   = $vars['use_global']?$vars['global_theme']:theme_get_setting('menu_item_counttheme');
  $vars['menu_item_splittheme']   = $vars['use_global']?$vars['global_theme']:theme_get_setting('menu_item_splittheme');
  $vars['menu_item_spliticon']    = $vars['use_global']?$vars['global_spliticon']:theme_get_setting('menu_item_spliticon');
  
  $vars['header_data_theme']      = $vars['use_global']?$vars['global_theme']:theme_get_setting('header_data_theme');
  $vars['content_data_theme']     = $vars['use_global']?$vars['global_theme']:theme_get_setting('content_data_theme');
  $vars['footer_data_theme']      = $vars['use_global']?$vars['global_theme']:theme_get_setting('footer_data_theme');  
  $vars['header_data_position']   = theme_get_setting('header_data_position');
  $vars['footer_data_position']   = theme_get_setting('footer_data_position');

  
  // If there is a base theme, collect the names of all themes that may have 
  // preprocess files to load.
  if ($theme_info->base_theme) {
    global $base_theme_info;
    foreach ($base_theme_info as $base) {
      $themes_active[] = $base->name;
    }
  }

  // Add the active theme to the list of themes that may have preprocess files.
  $themes_active[] = $theme_info->name;
  // Check all active themes for preprocess files that will need to be loaded.
  foreach ($themes_active as $name) {
    if (is_file(drupal_get_path('theme', $name) . '/includes/preprocess-' . str_replace('_', '-', $hook) . '.inc')) {
      include(drupal_get_path('theme', $name) . '/includes/preprocess-' . str_replace('_', '-', $hook) . '.inc');
    }
  }
}

function mobile_jquery_get_styles() {
  return array(
    'all' => array(
      'module' => array(
        'modules/node/node.css' => 1,
        'modules/system/defaults.css' => 1,
        'modules/system/system.css' => 1,
        'modules/system/system-menus.css' => 1,
        'modules/user/user.css' => 1,
        'sites/all/modules/admin/includes/admin.toolbar.base.css' => 1,
        'sites/all/modules/admin/includes/admin.toolbar.css' => 1,
        'sites/all/modules/admin/includes/admin.menu.css' => 1,
        'sites/all/modules/admin/includes/admin.devel.css' => 1,
        'sites/all/modules/devel/devel.css' => 1,
      ),
    ),
  );
}

function mobile_jquery_get_scripts() {
  return array(
    'module' => array(
      'misc/farbtastic/farbtastic.js' => 'farbtastic.js',
      'misc/teaser.js' => 'teaser.js',
      'misc/jquery.form.js' => 'jquery.form.js',
      'misc/ahah.js' => 'ahah.js',
      'misc/tabledrag.js' => 'tabledrag.js',
      'misc/autocomplete.js' => 'autocomplete.js',
      'sites/all/modules/admin/includes/jquery.drilldown.js' => 'admin.toolbar.js',
      'sites/all/modules/admin/includes/admin.toolbar.js' => 'admin.toolbar.js',
      'sites/all/modules/admin/includes/admin.menu.js' => 'admin.menu.js',
      'sites/all/modules/admin/includes/admin.devel.js' => 'admin.devel.js',
    ),
    'core' => array(
      'misc/tabledrag.js' => 'tabledrag.js',
    ),
  );
}




