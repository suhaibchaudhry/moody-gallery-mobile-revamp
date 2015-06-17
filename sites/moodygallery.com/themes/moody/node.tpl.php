<div id="node-<?php print $node->nid; ?>" class="node<?php if ($sticky) { print ' sticky'; } ?><?php if (!$status) { print ' node-unpublished'; } ?><?php if($teaser) { print ' node-teaser'; } else { print ' node-full'; } ?><?php if($node->type) { print ' node-type-'.$node->type; }?>">

<?php if ($teaser): ?>
  <h2><a href="<?php print $node_url ?>" title="<?php print $title ?>"><?php print $title ?></a></h2>
<?php endif; ?>

  <div class="node-content clear-block">
    <?php print $content ?>
    <?php if($node->parent_nodes):?><div class="parent-nodes"><?php print phptemplate_parent_nodes($node->parent_nodes); ?></div><?php endif; ?>
  </div>

  <div class="clear-block">
    <?php if ($links): ?>
      <div class="links"><?php print $links; ?></div>
    <?php endif; ?>
  </div>
</div>