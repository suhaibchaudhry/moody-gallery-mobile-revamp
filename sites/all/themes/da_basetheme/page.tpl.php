<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<?php print $head ?>
<title><?php print $head_title ?></title>
<?php print $styles ?>
<?php print $scripts ?>
</head>

<body>
<div class="container">
	<div class="containerbg login-<?php print phptemplate_get_login_state() ?>">
	<div class="header">
  	<div class="logo">
    	<a href="<?php print $base_path ?>"><img src="<?php print $logo ?>" alt="<?php print $site_title ?>" height="<?php print $logo_height ?>" width="<?php print $logo_width ?>" /></a>
  	</div>
    <div class="header_right">
		<?php if(isset($search_box)) : ?><div class="search_box"><?php print $search_box ?></div><?php endif; ?>
        <?php if (isset($secondary_links)) : ?><?php print theme('links', $secondary_links, array()) ?><?php endif; ?>
   		<?php if(isset($header)) : ?><div class="header_left"><?php print $header ?></div><?php endif; ?>
        <?php if(isset($site_slogan)) :?><div class="slogan"><?php print $site_slogan ?></div><?php endif; ?>
     </div>
     <?php if(isset($header_two)) : ?><div class="header_right"><?php print $header_two ?></div><?php endif; ?>
  </div>
  <?php if (isset($primary_links)) : ?>
  	<div class="primary_nav"><?php print theme('links', $primary_links, array()) ?></div>
    <?php if($primary_links_children) : ?><div class="primary_children"><?php print $primary_links_children ?></div><?php endif; ?>
  <?php endif; ?>
  <?php if($messages) : ?>
    <div class="system-messages"><?php print $messages ?></div>
  <?php endif; ?>
  <?php if($top_pane) : ?>
  <div class="top_pane">
  	<?php print $top_pane ?>
  </div>
  <?php endif; ?>
  <?php if($left) : ?>
  <div class="sidebar_left">
  	<?php print $left ?>
  </div>
  <?php endif; ?>
  <div class="content<?php print phptemplate_content_class($left, $right) ?>"<?php if(isset($node->nid)): ?> id="content-id-<?php print $node->nid ?>"<?php endif; ?>>
  	<?php if($breadcrumb) : ?><div class="breadcrumb"><?php print $breadcrumb . ' › ' . $title; ?></div><?php endif; ?>
    <?php if ($title && !$is_front): ?>
		<h1 class="title <?php print $node->type ?>"><?php print $title; ?></h1>
		<?php endif; ?>
    <?php if($tabs && !$is_front) : ?><?php print '<div class="tabs"><ul class="tabs primary">'.$tabs.'</ul></div>' ?><?php endif; ?>
    <?php if($tabs2 && !$is_front) : ?><?php print '<div class="tabs"><ul class="tabs2 secondary">'.$tabs2.'</ul></div>' ?><?php endif; ?>
  	<?php print $content ?>
  </div>
  <?php if($right) : ?>
  <div class="sidebar_right">
  	<?php print $right ?>
  </div>
  <?php endif; ?>
  <div class="footer">
  	<?php print $footer ?>
    <p class="footer-message"><?php print $footer_message ?></p>
  </div>
  </div>
</div>
<?php print $closure; ?>
</body>
</html>