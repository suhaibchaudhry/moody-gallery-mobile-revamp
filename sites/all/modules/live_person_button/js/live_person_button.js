$(document).ready(function() {
	$("#_lpChatRating").attr('target', '_blank');
	$("#_lpChatBtn").attr('target', 'chat'+Drupal.settings.live_person.lpAccount);
	$("#_lpChatBtn").click(function(){
		lpButtonCTTUrl = 'https://server.iad.liveperson.net/hc/'+Drupal.settings.live_person.lpAccount+'/?cmd=file&file=visitorWantsToChat&site='+Drupal.settings.live_person.lpAccount+'&imageUrl='+Drupal.settings.live_person.image_root+'&referrer='+escape(document.location);
		lpButtonCTTUrl = (typeof(lpAppendVisitorCookies) != 'undefined' ? lpAppendVisitorCookies(lpButtonCTTUrl) : lpButtonCTTUrl); lpButtonCTTUrl = ((typeof(lpMTag)!='undefined' && typeof(lpMTag.addFirstPartyCookies)!='undefined')?lpMTag.addFirstPartyCookies(lpButtonCTTUrl):lpButtonCTTUrl);window.open(lpButtonCTTUrl,'chat18919672','width='+Drupal.settings.live_person.width+',height='+Drupal.settings.live_person.height+',resizable=yes');
	});
});