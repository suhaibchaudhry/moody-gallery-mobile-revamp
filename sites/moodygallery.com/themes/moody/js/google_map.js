Drupal.behaviors.google_maps = function(context) {
	$('.googlemap', context).append('<iframe width="400" height="320" frameborder="0" scrolling="no" marginheight="0" marginwidth="0" src="http://maps.google.com/maps?f=q&amp;source=s_q&amp;hl=en&amp;geocode=&amp;q=2815+COLQUITT++HOUSTON,+TX+77098+&amp;aq=&amp;sll=37.0625,-95.677068&amp;sspn=42.495706,79.013672&amp;ie=UTF8&amp;hq=&amp;hnear=2815+Colquitt+St,+Houston,+Texas+77098&amp;ll=29.734645,-95.421753&amp;spn=0.023849,0.034246&amp;z=14&amp;iwloc=A&amp;output=embed"></iframe><br /><small><a href="http://maps.google.com/maps?f=q&amp;source=embed&amp;hl=en&amp;geocode=&amp;q=2815+COLQUITT++HOUSTON,+TX+77098+&amp;aq=&amp;sll=37.0625,-95.677068&amp;sspn=42.495706,79.013672&amp;ie=UTF8&amp;hq=&amp;hnear=2815+Colquitt+St,+Houston,+Texas+77098&amp;ll=29.734645,-95.421753&amp;spn=0.023849,0.034246&amp;z=14&amp;iwloc=A" style="color:#0000FF;text-align:left">View Larger Map</a></small>');
}

Drupal.behaviors.styleBreadCrumbs = function(context) {
	$(".container .content", context).prepend('<div class="article-title-crumb" />');
	$(".article-title-crumb", context).append($('.breadcrumb'));
	$(".article-title-crumb", context).append($('h1.title'));
}