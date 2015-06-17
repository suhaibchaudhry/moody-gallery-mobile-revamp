<?php
/**
 * @file
 *   Default theme implementation to format the available slot.
 * 
 * @version
 *   $Id: custom-timeslots-slot-available.tpl.php,v 1.1.2.2 2009/10/09 11:19:48 kenorb Exp $
 * 
 * Copy this file in your theme directory to create a custom themed footer.
 *
 * Available variables:
 * - $node: node object
 * - $link: link to the booking timeslot
 * - $title: language object
 *
 * @see template_preprocess_custom_timeslots_slot_available()
 */
?>
<?php
$now_date = date("Y-n-d");
$curr_date = $_GET['curr_date'];
if ($curr_date && $curr_date < $now_date) {
  print $title;
} else {
  print "<a href='$link'>" . $title . '</a>';
}
?>

