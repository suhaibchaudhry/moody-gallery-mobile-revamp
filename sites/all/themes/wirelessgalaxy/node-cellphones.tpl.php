<?php
//Start code for wholesale rendering
$default_price = $node->content['sell_price']['#value'];
$sale_price = '';

if($wholesale_price !== FALSE) {
    $sale_price .= '<p class="sprice strikethr">Sale Price: '.$default_price.'</p>';
    $sale_price .= '<p class="sprice">Your Wholesale Price: '.theme('uc_product_price', array('price' => $wholesale_price, 'qty' => 1), array('revision' => 'themed', 'type' => 'amount')).'</p>';
	$default_price = theme('uc_product_price', array('price' => $wholesale_price, 'qty' => 1), array('revision' => 'themed', 'type' => 'amount'));
} else {
	$sale_price .= '<p class="sprice">Sale Price: '.$default_price.'</p>';
}
//End code for wholesale rendering

if($teaser) {
	print phptemplate_render_teaser_elements($nid, $node->field_image_cache, $node->title, $node_url, $default_price, $node->content['add_to_cart']['#value'], $node->attributes, phptemplate_list_terms($node, array(51 => 'Features'), FALSE, FALSE, 4, '- '));
} else {
//Product full page template variables:
phptemplate_setup_tooltips();
$image_gallery = phptemplate_render_gallery($node->field_image_cache, $node->title);
$full_description = $node->content['body']['#value'];
//$overview = filter_xss(phptemplate_get_overview($full_description), array('strong'));
$overview = $teaser_val;
$stock = $node->field_stock_type[0]['value'];
$regular_price = $node->content['list_price']['#value'];
$add_to_cart = str_replace('{color_tooltip}', phptemplate_get_theme_image('mark.png', array('alt' => '', 'class' => 'vtip', 'title' => 'All colors might not be available at all times. If a color
you choose is currently out of stock, you will be contacted by a representative
with an alternative color option or ETA (estimated time of arrival).
<br /><br />
If you are particular about a certain color please feel free
to give us a call at 1-800-604-GLXY (4599) and ask for a stock check. :)
<br /><br />
Wireless Galaxy is dedicated to offering our customers the
most diverse variety of cell phones and related products available in the
nation!')), _str_replace_first('<option value="" selected="selected">Please select</option>', '', $node->content['add_to_cart']['#value']));
$condition = phptemplate_get_selected_term_for_node('Condition', $node, 29);

$tabs = array();

$tabs['overview'] = array(
	'title' => 'Overview',
	'content' => phptemplate_list_terms($node, array(51 => 'Features', 28 => 'What comes in the box?', 21 => 'Recommended For'))
);

$tabs['details'] = array(
	'title' => 'Detailed Description',
	'content' => '<h3>'.$title.'</h3>'.$full_description
);

$tabs['compatibility'] = array(
	'title' => 'Similar Phones',
	'content' => $similar
);

$tabs['related'] = array(
	'title' => 'Accessories',
	'content' => _da_related_accs($related)
);

$available_flag = TRUE;
?>
<div id="node-<?php print $node->nid; ?>" class="cellphonewrapper pagenodewrapper nodewrapper">
  <div id="inside-left-bar">
  	<?php print $image_gallery; ?>
    <div id="partnocont">
    	<p>
        	Part # <?php print $node->model ?>
        </p>
    </div>
  </div>
  <div id="inside-right-region">
  	<div class="product_overview"><?php print $overview; ?></div>
	<p class="availability">Availability: <?php print phptemplate_render_status($stock, $available_flag); ?></p>
    <p class="condition"><?php print $condition ?></p>
	<p class="msrp">Regular Price: <span class="strike"><?php print $regular_price; ?></span></p>
	<?php print $sale_price ?>
    <p class="contract">(No Service Contract Required)</p>
    <?php if(in_array($stock, array('instock', 'backordered'))) : ?>
		<?php print $add_to_cart; ?>
    	<div class="freeshippingofr">
    		<p>
    			This Item qualify's for
    	  		<br />
    	    	<strong>Free Shipping</strong>
    	    </p>
    	</div>
    <?php endif; ?>
    <h2>Cell Phone Details</h2>
    <?php print phptemplate_render_tabs($tabs, $available_flag); ?>
  </div>
</div>
<?php
}
?>