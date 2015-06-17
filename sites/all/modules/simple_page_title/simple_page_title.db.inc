<?php
/**
 * @file
 * Simple Page Title - Database Helper Functions
 *
 * @author
 * Jamie Giberti <jagiberti@gmail.com>
 */

/**
 * Simple DB Function to insert a row into the simple_page_title DB table.
 * @param string $path
 * @param string $page_title
 * @return bool
 */
function simple_page_title_add_page_title_to_db($path, $page_title) {
  $sql = 'INSERT INTO {simple_page_title} (path, page_title) VALUES ("%s","%s")';
  $result = db_query($sql, $path, $page_title);
  return $result;
}

/**
 * Simple DB Function to update a row in the simple_page_title DB table.
 * @param string $path
 * @param string $page_title
 * @return unknown_type
 */
function simple_page_title_update_page_title_for_path($path, $page_title) {
  $sql = 'UPDATE {simple_page_title} SET page_title = "%s" WHERE path = "%s"';
  $result = db_query($sql, $page_title, $path);
  return $result;
}

/**
 * Simple DB Function to delete a row in the simple_page_title DB table.
 * @param string $path
 * @return bool
 */
function simple_page_title_delete_page_title_for_path($path) {
  $sql = 'DELETE FROM {simple_page_title} WHERE path = "%s"';
  $result = db_query($sql, $path);
  return $result;
}

/**
 * Function to return a count of the number of records for a particular path (should never be greater than one)
 * @param string $path
 * @param string $path_alias
 * @return int
 */
function simple_page_title_get_page_title_for_path_count($path, $path_alias = NULL) {
  $sql = 'SELECT COUNT(*) as path_count FROM {simple_page_title} WHERE path = "%s"';
  if (empty($path_alias)) {
    $result = db_query($sql, $path);
  } 
  else {
    $sql .= ' OR path = "%s"';
    $result = db_query($sql, $path, $path_alias);
  }

  $result_object = db_fetch_object($result);
  return $result_object->path_count;
}

/**
 * Function to return an object for a given id
 * @param string $path
 * @param string $path_alias
 * @return object
 */
function simple_page_title_get_page_title_object_for_id($id) {
  $sql = 'SELECT * FROM {simple_page_title} WHERE pt_id = %d';
  $result = db_query($sql, $id);
  $result_object = db_fetch_object($result);
  return $result_object;
}

/**
 * Function to return an object for a particular path (should never be greater than one match)
 * @param string $path
 * @param string $path_alias
 * @return object
 */
function simple_page_title_get_page_title_object_for_path($path, $path_alias = NULL) {
  $sql = 'SELECT * FROM {simple_page_title} WHERE path = "%s"';
  if (empty($path_alias)) {
    $result = db_query($sql, $path);
  } 
  else {
    $sql .= ' OR path = "%s"';
    $result = db_query($sql, $path, $path_alias);
  }
  
  if (!empty($path_alias)) 
  $result_object = db_fetch_object($result);
  return $result_object;
}

/**
 * Function to retrieve the weight of a given module from the system table
 * @param string $module_name
 * @return int
 */
function simple_page_title_get_module_weight($module_name) {
  $sql = 'SELECT weight FROM {system} WHERE name = "%s"';
  $module_weight = (int) db_result(db_query($sql, $module_name));
  return $module_weight;
}

/**
 * Function to update the weight of a module in the system table
 * @param string $module_name
 * @param int $module_weight
 * @return bool
 */
function simple_page_title_update_module_weight($module_name, $module_weight) {
  $sql = 'UPDATE {system} SET weight = %d WHERE name = "%s"';
  $result = db_query($sql, $module_weight, $module_name);
  return $result;
}
