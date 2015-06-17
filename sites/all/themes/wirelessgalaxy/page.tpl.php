<?php
$barcounter = 0;
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
	<?php print $head ?>
    <?php if($is_front) : ?>
    <title><?php print $site_name ?></title>
    <?php else: ?>
    <title><?php print $head_title ?></title>
    <?php endif; ?>
	<?php print $styles ?>
	<?php print $scripts ?>
	<?php print phptemplate_get_ie_styles(6); ?>
	<?php print phptemplate_get_ie_styles(7); ?>
    <?php print phptemplate_get_ie_styles(8); ?>
</head>

<body>
 <div id="container">
  <div id="header">
  	<div id="topsect">
    	<div id="logo"><?php print phptemplate_render_logo('logo.png'); ?></div>
        <div id="toprpane">
        	<div id="contactpane">
            	<div id="usermenupane">
                	<?php if(!empty($usermenupane)) : ?>
						<?php print $usermenupane; ?>
                    <?php endif; ?>
                </div>
            	<div id="contactinfo">
                	<p><span>Mon - Fri :: 9AM - 5PM (CST)</span> 1-800-604-GLXY</p>
                    <p class="number">(4599)</p>
                </div>
            </div>
            <div id="submainmenu">
            	<div id="leftcurve"></div>
                <?php if (!empty($secondary_links)) : ?>
        			<?php print theme('links', $secondary_links) ?>
        		<?php endif; ?>
                <div id="rightcurve"></div>
            </div>
        </div>
    </div>
    <div id="mainnavbar">
        <?php if (!empty($primary_links)) : ?>
        	<?php print theme('links', $primary_links) ?>
        <?php endif; ?>
        <div id="searchpane">
        	<?php print $search_box ?>
        </div>
    </div>
  </div>
  
  <div id="infobar">
  	
  	<div id="browsepane">
    	<?php if(!empty($userpanel)) : ?>
        	<?php print $userpanel ?>
        <?php endif; ?>
    </div>
    
    <div id="liveperson"><?php print $live_person ?></div>    
    <div id="feeshippromo">
    	<p class="shipping">
        	FREE SHIPPING<br />
        	<span>ON ORDERS OVER $50<br />
			(U.S &amp; CANADA ONLY)</span>
        </p>
    </div>
  </div>
  <?php if(!empty($top_left) || !empty($top_right)) : ?>
  <div id="regiontop">
  	 <div class="tbblockcontainer tbblk-left">
    	<div class="block-main-content">
        	<?php if(!empty($top_left)) : ?>
        		<?php print $top_left ?>
            <?php endif; ?>
        </div>
     </div>
     <div class="tblockcontainer tbblk-right">
    	<div class="block-main-content">
        	<?php if(!empty($breadcrum)): ?>
        		<?php print $breadcrum; ?>
        	<?php endif; ?>
        	<?php if(!empty($top_right)) : ?>
            	<?php print $top_right?>
            <?php endif; ?>
        </div>
     </div>
  </div>
  <?php endif; ?>
  <?php if(!$is_front) : ?>
  <div id="breadcrumbbar">
  	<div class="bclinks"><?php print $breadcrumb.' &gt; &nbsp; <strong>'.$title.'</strong>' ?></div>
    <div id="bc-block-content">
    	<?php if(!empty($breadcrum)): ?>
        	<?php print $breadcrum; ?>
        <?php endif; ?>
    </div>
  </div>
  <?php endif; ?>
  <?php print phptemplate_get_theme_image('gradiant.jpg', array('alt' => '', 'class' => 'gradiantpic', 'height' => '168', 'width' => '980')) ?>
  <?php if (!empty($left) && (empty($node->shippable) || arg(2) == 'edit')): ?>
  <?php $barcounter++; ?>
  <div id="regionleft">
  	<?php print $left ?>
  </div>
  <?php endif; ?>
	
  <?php if (!empty($right) && (arg(0) != 'admin' || arg(2) == 'block') && arg(1) != 'add' && arg(2) != 'edit'): ?>
  <?php $barcounter++; ?>
  <div id="regionright">
	<div class="sbblockcontainer sbblk-right">
    	<div class="topcurve"></div>
        <div class="blocksmainwrap">
			<?php print $right ?>
        </div>
        <div class="bottomcurve"></div>
    </div>
  </div>
  <?php endif; ?>

  <div id="mainContent" class="<?php print phptemplate_get_mc_class($barcounter); ?>">
  	<div id="contentwrapper" class="<?php print phptemplate_get_cw_class($barcounter); ?>">
    	<?php if(!$is_front) : ?>
        	<h1><?php print $title ?></h1>
		<?php endif; ?>
       	<?php if ($tabs): print '<div id="tabs-wrapper" class="clear-block">'. $tabs .'</div>'; endif; ?>
        <?php if($messages): print $messages; endif; ?>
    	<?php print $content ?>
    </div>
  </div>
  <br class="clearing_break" />
</div>
<div id="footer">
    <div id="inquiry">
    	<p>
        Don't see what you are looking for? Email us your inquiry at <a href="mailto:inquiry@wirelessgalaxy.com">inquiry@wirelessgalaxy.com</a> or <?php print l('Click here', '', array('attributes' => array('onclick' => "window.open('https://server.iad.liveperson.net/hc/18919672/?cmd=file&file=visitorWantsToChat&site=18919672&byhref=1&imageUrl=https://server.iad.liveperson.net/hcp/Gallery/ChatButton-Gallery/English/General/1a/','Live Customer Support Chat','menubar=0,width=475,height=400,toolbar=0,scrollbars=1'); return false;"))); ?> to speak with a representative NOW!
        </p>
    </div>
    <div id="navwrapper">
    	<div id="footnav">
        	<div id="footnav-1" class="ftnav">
            	<?php if(!empty($footer1)) : ?>
            		<?php print $footer1 ?>
                <?php endif; ?>
            </div>
            <div id="footnav-2" class="ftnav">
            	<?php if(!empty($footer2)) : ?>
            		<?php print $footer2 ?>
                <?php endif; ?>
            </div>
            <div id="footnav-3" class="ftnav">
            	<?php if(!empty($footer3)) : ?>
            		<?php print $footer3 ?>
                <?php endif; ?>
            </div>
            <div id="footnav-4" class="ftnav">
            	<?php if(!empty($footer4)) : ?>
                	<?php print $footer4 ?>
                <?php endif; ?>
            </div>
            <div id="footnav-5" class="ftnav ftnavfeed">
            	<?php if(!empty($footer5)) : ?>
                	<?php print $footer5 ?>
                <?php endif; ?>
            	<div id="feeds-l" class="feedimgs">
                	<ul>
                    	<li><a href="http://feeds.feedburner.com/wirelessgalaxy" rel="nofollow"><?php print phptemplate_get_theme_image('feedicons/xml.png') ?></a></li>
   						<li><a href="http://fusion.google.com/add?feedurl=http://feeds.feedburner.com/wirelessgalaxy" rel="nofollow"><?php print phptemplate_get_theme_image('feedicons/google.png') ?></a></li>
   						<li><a href="http://add.my.yahoo.com/rss?url=http://feeds.feedburner.com/wirelessgalaxy" rel="nofollow"><?php print phptemplate_get_theme_image('feedicons/yahoo.png') ?></a></li>
   						<li><a href="http://my.msn.com/addtomymsn.armx?id=rss&amp;ut=http://feeds.feedburner.com/wirelessgalaxy" rel="nofollow"><?php print phptemplate_get_theme_image('feedicons/msn.png') ?></a></li>
   						<li><a href="http://feeds.my.aol.com/add.jsp?url=http://feeds.feedburner.com/wirelessgalaxy" rel="nofollow"><?php print phptemplate_get_theme_image('feedicons/aol.png') ?></a></li>
                    </ul>
                </div>
                <div id="feeds-r" class="feedimgs">
                	<ul>
   						<li><a href="http://www.bloglines.com/sub/http://feeds.feedburner.com/wirelessgalaxy" rel="nofollow"><?php print phptemplate_get_theme_image('feedicons/bloglines.png') ?></a></li>
  			 			<li><a href="http://www.bloglines.com/sub/http://feeds.feedburner.com/wirelessgalaxy" rel="nofollow"><?php print phptemplate_get_theme_image('feedicons/netvibes.png') ?></a></li>
   						<li><a href="http://www.pageflakes.com/subscribe.aspx?url=http://feeds.feedburner.com/wirelessgalaxy" rel="nofollow"><?php print phptemplate_get_theme_image('feedicons/pageflakes.png') ?></a></li>
   						<li><a href="http://www.rojo.com/add-subscription?resource=http://feeds.feedburner.com/wirelessgalaxy" rel="nofollow"><?php print phptemplate_get_theme_image('feedicons/rojo.png') ?></a></li>
   						<li><a href="http://www.springwidgets.com/widgetize/23/?param=http://feeds.feedburner.com/wirelessgalaxy" rel="nofollow"><?php print phptemplate_get_theme_image('feedicons/widget.png') ?></a></li>
  					</ul>
                </div>
            </div>
            <?php print phptemplate_get_theme_image('cards.png', array('alt' => 'We accept American Express, Visa, MasterCard, and PayPal.', 'height' => '69', 'width' => '479', 'class' => 'ftcardsimg')) ?>
        </div>
    </div>
    <div id="credits">
		<p>
            <?php print $footer_message ?>
        </p>
    </div>
</div>
<?php print $closure ?>
</body>
</html>