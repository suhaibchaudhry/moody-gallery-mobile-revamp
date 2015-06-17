<div id="block-<?php print $block->module .'-'. $block->delta; ?>" class="block block-<?php print $block->module ?><?php print $block_image ? ' block-image' : '' ?>">
<?php if (!empty($block->subject)): ?>
  <h2><?php print $block->subject ?></h2>
<?php endif;?>
<?php if($block_image) { ?>
	<?php $block_link = filter_xss($block->content); ?>
    <?php if($block_link == '#') { ?>
    <?php print theme_image($block_image); ?>
    <?php } else { ?>
  	<?php print l(theme_image($block_image), $block_link, array('html' => true)); ?>
    <?php } ?>
<?php } else { ?>
	<div class="block-content"><?php print $block->content ?></div>
<?php } ?>
</div>
