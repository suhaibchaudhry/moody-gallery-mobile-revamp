<?php
	if(in_array($node->type, array('antennas_and_amplifiers', 'batteries', 'bluetooth', 'cases', 'chargers', 'charms', 'headsets', 'memory', 'misc', 'phone_holders', 'pouches', 'screen_protectors', 'sim_cards', 'data_cables'))) {
	include "node-accessory.tpl.php";
 } else { 
 	if($teaser) {
 ?>
	<div id="node-<?php print $node->nid; ?>" class="pagenodewrapper nodewrapper">
	  <h2><a href="<?php print $node_url ?>"><?php print $title ?></a></h2>
	  <div class="content">
	    <?php print $content ?>
	  </div>
	</div>
  <?php } else { ?>
  	<div id="node-<?php print $node->nid; ?>" class="pagenodewrapper nodewrapper">
	  <div class="content">
	    <?php print $content ?>
	  </div>
	</div>
  <?php } ?>
<?php } ?>