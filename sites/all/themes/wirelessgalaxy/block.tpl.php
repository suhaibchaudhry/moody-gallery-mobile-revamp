<?php if($block->region == 'footer1' || $block->region == 'footer2' || $block->region == 'footer3') { ?>
	<h3><?php print $block->subject ?></h3>
	<?php print $block->content ?>
<?php } elseif($block->region == 'left') { ?>
	<div class="sbblockcontainer sbblk-left">
	  <div class="topcurve">
	  	<h3><?php print $block->subject ?></h3>
	  </div>
	  <div class="block-main-content">
      	<div class="lftblk-container">
	  		<?php print $block->content ?>
        </div>
	  </div>
	  <div class="bottomcurve"></div>
	</div>
<?php } elseif($block->region == 'right') { ?>
	<div class="block-main-content">
  		<?php if(!empty($block->subject)) : ?>
    		<h3><?php print $block->subject ?></h3>
        <?php endif; ?>
    	<?php print $block->content ?>
	</div>
<?php } elseif($block->region == 'content') { ?>
    <div class="content-block-stuff">
  		<?php if(!empty($block->subject)) : ?>
    		<h3 class="content-blocks"><?php print $block->subject ?></h3>
        <?php endif; ?>
    	<?php print $block->content ?>
	</div>
<?php 
} else {  //for blocks in all other regions need touch up
	print $block->content;
}
?>