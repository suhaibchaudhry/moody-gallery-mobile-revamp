<?php /*Requires a present called search for displaying search result images*/ ?>
<?php $node = $result["node"] ?>
<div class="search-result">
	<div class="title"><p><a href="<?php print $url ?>"><?php print $title ?></a></p></div>
    <?php if($node->field_image_cache[0]) { ?>
	<div class="image"><a href="<?php print $url ?>"><?php print theme('imagecache', 'search', $node->field_image_cache[0]["filepath"], $node->field_image_cache[0]["data"]["alt"], $node->field_image_cache[0]["data"]["title"]); ?></a></div>
    <?php } ?>
    <div class="snippet"><p><?php print $snippet ?></p></div>
</div>