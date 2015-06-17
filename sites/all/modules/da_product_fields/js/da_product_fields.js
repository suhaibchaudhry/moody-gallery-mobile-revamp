$(document).ready(function() {
	da_update_prcnt_from_sell();
});

function da_update_sell_from_prcnt() {
	$("input[name='sell_price']").val((1+(parseFloat($("input[name='percent_retail']").val())/100))*parseFloat($("input[name='cost']").val()));
}
function da_update_prcnt_from_sell() {
	$("input[name='percent_retail']").val(((parseFloat($("input[name='sell_price']").val()) - parseFloat($("input[name='cost']").val()))/parseFloat($("input[name='cost']").val())*100));
}