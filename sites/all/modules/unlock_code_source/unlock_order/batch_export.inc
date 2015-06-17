<?php
/**
 * The $batch can include the following values. Only 'operations'
 * and 'finished' are required, all others will be set to default values.
 *
 * @param operations
 *   An array of callbacks and arguments for the callbacks.
 *   There can be one callback called one time, one callback
 *   called repeatedly with different arguments, different
 *   callbacks with the same arguments, one callback with no
 *   arguments, etc.
 *
 * @param finished
 *   A callback to be used when the batch finishes.
 *
 * @param title
 *   A title to be displayed to the end user when the batch starts.
 *
 * @param init_message
 *   An initial message to be displayed to the end user when the batch starts.
 *
 * @param progress_message
 *   A progress message for the end user. Placeholders are available.
 *   Placeholders note the progression by operation, i.e. if there are
 *   2 operations, the message will look like:
 *    'Processed 1 out of 2.'
 *    'Processed 2 out of 2.'
 *   Placeholders include:
 *     @current, @remaining, @total and @percentage
 *
 * @param error_message
 *   The error message that will be displayed to the end user if the batch
 *   fails.
 *
 * @param file
 *   Path to file containing the callbacks declared above. Always needed when
 *   the callbacks are not in a .module file.
 *
 */
function unlock_order_export($month = '', $year = '') {
	$oldfile = file_directory_path().'/'.file_create_filename('export.csv.tmp', 'unlock_order');
	$newfile = file_directory_path().'/'.file_create_filename('export.csv', 'unlock_order');
	$folder = file_directory_path().'/unlock_order';
	file_delete($oldfile);
	file_delete($newfile);
	file_check_directory($folder, FILE_CREATE_DIRECTORY);
	$fp = fopen($oldfile, 'a+');
	fputcsv($fp, array('Date Submitted', 'Date Completed', 'Tool ID', 'Username', 'User Email', 'Order ID', 'Status', 'Remote REF', 'IMEI', 'Model', 'Email', 'Cost', 'Sell Price', 'Profit', 'Notes'));
	fclose($fp);

  $batch = array(
    'operations' => array(
		array('unlock_order_export_process', array($month, $year, $oldfile, $newfile)),
      ),
    'finished' => 'unlock_order_export_save',
    'title' => t('Exporting Orders'),
    'init_message' => t('Gathering Data'),
    'progress_message' => '',
    'error_message' => t('Order Export has encountered an error. Contact DA Desigers for troubleshooting.'),
    'file' => drupal_get_path('module', 'unlock_order') . '/batch_export.inc',
  );
  batch_set($batch);

  // If this function was called from a form submit handler, stop here,
  // FAPI will handle calling batch_process().

  // If not called from a submit handler, add the following,
  // noting the url the user should be sent to once the batch
  // is finished.
  
  batch_process($newfile);
}

/**
 * Batch Operation Callback
 *
 * Each batch operation callback will iterate over and over until
 * $context['finished'] is set to 1. After each pass, batch.inc will
 * check its timer and see if it is time for a new http request,
 * i.e. when more than 1 minute has elapsed since the last request.
 *
 * An entire batch that processes very quickly might only need a single
 * http request even if it iterates through the callback several times,
 * while slower processes might initiate a new http request on every
 * iteration of the callback.
 *
 * This means you should set your processing up to do in each iteration
 * only as much as you can do without a php timeout, then let batch.inc
 * decide if it needs to make a fresh http request.
 *
 * @param options1, options2
 *   If any arguments were sent to the operations callback, they
 *   will be the first argments available to the callback.
 *
 * @param context
 *   $context is an array that will contain information about the
 *   status of the batch. The values in $context will retain their
 *   values as the batch progresses.
 *
 * @param $context['sandbox']
 *   Use the $context['sandbox'] rather than $_SESSION to store the
 *   information needed to track information between successive calls.
 *   The values in the sandbox will be stored and updated in the database
 *   between http requests until the batch finishes processing. This will
 *   avoid problems if the user navigates away from the page before the
 *   batch finishes.
 *
 * @param $context['results']
 *   The array of results gathered so far by the batch processing.
 *   The current operation can append its own.
 *
 * @param $context['message']
 *   A text message displayed in the progress page.
 *
 * @param $context['finished']
 *   A float number between 0 and 1 informing the processing engine
 *   of the completion level for the operation.
 *
 *   1 (or no value explicitly set) means the operation is finished
 *   and the batch processing can continue to the next operation.
 */
function unlock_order_export_process($month, $year, $oldfile, $newfile,  &$context) {
  if (!isset($context['sandbox']['progress'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['current_node'] = 0;
    $context['sandbox']['max'] = db_result(db_query("SELECT COUNT(*) FROM {unlock_orders} uo WHERE uo.status IN (".UNLOCK_FOUND.", ".UNLOCK_NOT_FOUND_NR.", ".UNLOCK_NOT_FOUND_R.")"));
 }

  // For this example, we decide that we can safely process
  // 5 nodes at a time without a timeout.
	$limit = 5;
	$fp = fopen($oldfile, 'a+');
  // With each pass through the callback, retrieve the next group of nids.
  $unlock_orders = db_query_range("SELECT * FROM {unlock_orders} uo WHERE uo.status IN (".UNLOCK_FOUND.", ".UNLOCK_NOT_FOUND_NR.", ".UNLOCK_NOT_FOUND_R.") AND uo.order_id > %d ORDER BY uo.order_id ASC", $context['sandbox']['current_node'], 0, $limit);
  while ($order = db_fetch_object($unlock_orders)) {
	$user = user_load($order->user_id);

    // Store some result for post-processing in the finished callback.
    $context['results'][] = $order->order_id;
	$row =  array(unlock_order_format_timestamp($order->timestamp), unlock_order_format_timestamp($order->ctimestamp), $order->tool_id, $user->name, $user->mail, $order->order_id, filter_xss(unlock_order_status($order->status)), $order->remote_order_id, $order->imei, $order->model, $order->cust_email, number_format($order->cost, 2), number_format($order->price, 2), number_format($order->price-$order->cost, 2), $order->notes);
	fputcsv($fp, $row);
    // Update our progress information.
    $context['sandbox']['progress']++;
    $context['sandbox']['current_node'] = $order->order_id;
    $context['message'] = t('Now Exporting Order #%order', array('%order' => $order->order_id));
  }
  fclose($fp);
  // Inform the batch engine that we are not finished,
  // and provide an estimation of the completion level we reached.
  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

/**
 * Batch 'finished' callback
 */
function unlock_order_export_save($success, $results, $operations) {
	$oldfile = file_directory_path().'/'.file_create_filename('export.csv.tmp', 'unlock_order');
	$newfile = file_directory_path().'/'.file_create_filename('export.csv', 'unlock_order');
  if ($success) {
    // Here we do something meaningful with the results.
    $message = count($results) .' orders exported.';
  } else {
    // An error occurred.
    // $operations contains the operations that remained unprocessed.
    $error_operation = reset($operations);
    $message = 'An error occured while exporting orders. Please speak to a DA Designers Tech Support agent for troubleshooting.';
  }
  file_move($oldfile, $newfile);
  drupal_set_message($message);
}