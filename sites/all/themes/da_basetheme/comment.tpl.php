<div class="comment<?php print ' '.$status.' '. $zebra; ?>">

	<div class="clear-block">
		<h3><?php print theme('username', $comment); ?></h3>
		<div class="comment-content">
			<?php print $content ?>
		</div>
	</div>

  <?php if ($links): ?>
    <div class="links"><?php print $links ?></div>
  <?php endif; ?>
</div>
