<?php

/**
 * @file comment.tpl.php
 * Default theme implementation for comments.
 *
 * Available variables:
 * - $author: Comment author. Can be link or plain text.
 * - $content: Body of the post.
 * - $date: Date and time of posting.
 * - $links: Various operational links.
 * - $new: New comment marker.
 * - $picture: Authors picture.
 * - $signature: Authors signature.
 * - $status: Comment status. Possible values are:
 *   comment-unpublished, comment-published or comment-preview.
 * - $submitted: By line with date and time.
 * - $title: Linked title.
 *
 * These two variables are provided for context.
 * - $comment: Full comment object.
 * - $node: Node object the comments are attached to.
 *
 * @see template_preprocess_comment()
 * @see theme_comment()
 */
?>
<div data-role="collapsible" data-collapsed="false" class="comment<?php print $comment->new ? ' comment-new' : ''; print ' '. $status; ?> clear-block">
  <h3>
  <?php print $title ?>  
  <?php if ($comment->new): ?>
    <span class="new"><?php print $new ?></span>
  <?php endif; ?>
  </h3>
  <div class="content-wrapper">
  <div class="submitted">
    <?php print $picture ?>
    <?php print $submitted ?>
  </div>

  <div class="content">
    <?php print $content ?>
    <?php if ($signature): ?>
    <div class="user-signature clear-block">
      <?php print $signature ?>
    </div>
    <?php endif; ?>
  </div>
  <?php if (!empty($links)): ?>
  <?php print $links ?>
  <?php endif; ?>
  </div>
</div>