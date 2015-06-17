<div class="dialogtitle">
<p class="title"><?php print l($node->title, 'node/'.$node->nid); ?></p>
<div class="closebtn"></div>
</div>
<div class="dialogcontent">
<div class="bigimage">
<?php print l(theme_imagecache('product', $node->field_image_cache[0]['filepath'], $node->field_image_cache[0]['data']['alt'], $node->field_image_cache[0]['data']['title']), 'node/'.$node->nid, array('html' => true)); ?>
</div>
<div class="quicklook-items">
<ul class="imagelist">
<?php
$i = 0;
foreach($node->field_image_cache as $image) {
	print '<li>'.theme_imagecache('uc_thumbnail', $image['filepath'], $image['data']['alt'], $image['data']['title'], array('rel' => base_path().imagecache_create_path('product', $image['filepath']))).'</li>';
	$i++;
	if($i == 4) {
		break;
	}
}
?>
</ul>
</div>
<div class="quickdetais">
<div class="quickprice">Price: <span><?php print uc_currency_format($node->sell_price) ?></span></div>
<?php print $node->body ?>
<?php print l('View Details', 'node/'.$node->nid, array('attributes' => array('class' => 'quick-view-details'))); ?>
</div>
</div>