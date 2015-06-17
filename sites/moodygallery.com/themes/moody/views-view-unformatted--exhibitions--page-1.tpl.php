<?php
//HIDE LAST RESULT - Do not show current exhibition in upcomming
// $Id: views-view-unformatted.tpl.php,v 1.6 2008/10/01 20:52:11 merlinofchaos Exp $
/**
 * @file views-view-unformatted.tpl.php
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<?php if (!empty($title)): ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>
<?php $range = range(0, moody_get_front_value()-1); ?>
<?php $i = 0; ?>
<?php foreach ($rows as $id => $row): ?>
  <?php if((!isset($_GET['page']) || $_GET['page'] != 1) && !in_array($i, $range)) :?>
  <div class="<?php print $classes[$id]; ?>">
    <?php print $row; ?>
  </div>
  <?php endif; ?>
  <?php $i++; ?>
<?php endforeach; ?>