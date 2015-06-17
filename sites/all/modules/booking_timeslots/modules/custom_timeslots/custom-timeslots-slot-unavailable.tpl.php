<?php
/**
 * @file
 *   Default theme implementation to format the available slot.
 * 
 * @version
 *   $Id: custom-timeslots-slot-unavailable.tpl.php,v 1.1.2.1 2009/09/23 14:57:19 kenorb Exp $
 * 
 * Copy this file in your theme directory to create a custom themed footer.
 *
 * Available variables:
 * - $node: node object
 * - $link: link to the booking timeslot
 * - $title: language object
 *
 * @see template_preprocess_custom_timeslots_slot_unavailable()
 */
?>
<?php
print '<center>' . l(t('Slot unavailable.'), "node/$node->nid") . '</center>';
print node_view($node, TRUE, TRUE);
?>

