// Extend the default Number object with a formatMoney() method:
// usage: someVar.formatMoney(decimalPlaces, symbol, thousandsSeparator, decimalSeparator)
// defaults: (2, "$", ",", ".")
Number.prototype.formatMoney = function(places, symbol, thousand, decimal) {
	places = !isNaN(places = Math.abs(places)) ? places : 2;
	symbol = symbol !== undefined ? symbol : "$";
	thousand = thousand || ",";
	decimal = decimal || ".";
	var number = this, 
	    negative = number < 0 ? "-" : "",
	    i = parseInt(number = Math.abs(+number || 0).toFixed(places), 10) + "",
	    j = (j = i.length) > 3 ? j % 3 : 0;
	return symbol + negative + (j ? i.substr(0, j) + thousand : "") + i.substr(j).replace(/(\d{3})(?=\d)/g, "$1" + thousand) + (places ? decimal + Math.abs(number - i).toFixed(places).slice(2) : "");
};
var InvoicehandlerAttach = true;
Drupal.behaviors.stormSearchInvoices = function() {
	if(InvoicehandlerAttach) {
		$('.javascript-enabled').removeClass('javascript-enabled');
		$('.javascript-disabled').remove();
		
		InvoicehandlerAttach = false;
		$('.invoice-search-form').bind('submit', function(e) {
			e.preventDefault();
			e.stopPropagation();

			var invoice_number = $(this).find('.invoice-number');
			var invoice_loader = $('.invoice-loader');
			var invoice_result = $('.invoice-results');

			if(invoice_number.val()) {
				invoice_number.removeClass('error');
				invoice_result.empty();
					invoice_loader.css({display: 'block'});
				$.getJSON(Drupal.settings.basePath+'payment/'+invoice_number.val().replace(/[\.,-\/#!@$%\^&\*;:{}=\-_`~()]/g, '').replace(/\s/g, ''), function(data) {
					//console.log(data);
					//console.log(Drupal.settings.basePath+'payment/'+invoice_number.val());
					if(data.found) {
						var markup = '<div class="invoice-information">';

						markup += '<div class="lpanel">';
						markup += '<p><span class="invoice-label">Company: </span>'+data.organization+'</p>';
						markup += '<p><span class="invoice-label">Invoice #: </span>'+data.nid+'</p>';
							markup += '<p><span class="invoice-label">Description: </span>'+data.title+'</p>';
						markup += '</div>';

						markup += '<div class="rpanel">';
						if(data.paid) {
								markup += '<p><span class="invoice-paid">Invoice Paid in Full</span></p>';
						} else {
								markup += '<p><span class="invoice-label">Invoice Total: </span>'+parseFloat(data.total).formatMoney()+'</p>';
						}
						markup += '<p><span class="invoice-label">Invoice Date: </span>'+data.date+'</p>';
						markup += '<a target="_blank" class="view-invoice-button" href="'+Drupal.settings.basePath+'storminvoicecharge/invoice/'+data.nid+'">View Invoice</a>';
						markup += '</div>';

						markup += '</div>';

						invoicePopulateResult(markup, invoice_result, invoice_loader);

						if(!data.paid && typeof data.payment_form !== "undefined") {
							invoice_result.append(data.payment_form);
							invoicePaymentHandler($('.payment-form'));
						}
					} else {
						invoicePopulateResult('<div class="not-found">The invoice number you provided could not be found. Please try again.<br />For further assistance please call <strong>1 (800) 789-9736</strong>.</div>', invoice_result, invoice_loader);
					}
					Drupal.attachBehaviors();
				});
			} else {
				invoice_number.addClass('error');
			}
		});
	}
}

function invoicePopulateResult(markup, invoice_result, invoice_loader) {
	invoice_loader.css({display: 'none'});
	invoice_result.css({opacity: 0});
	invoice_result.html(markup);
	invoice_result.stop().animate({opacity: 1}, 'slow');
}

function paymentPopulateResult(markup, paymentForm) {
	paymentForm.find('.payment-response').css({opacity: 0}).empty().append(markup).stop().animate({opacity: 1}, 'slow');
}

function invoicePaymentHandler(paymentForm) {
	paymentForm.bind('submit', function(e) {
		e.preventDefault();
		e.stopPropagation();
		if(checkRequiredFields($('#edit-first-name, #edit-last-name, #edit-ccnumber, #edit-cvv'))) {
			$submitBtn = paymentForm.find('.form-submit');
			$submitBtn.attr('disabled', 'disabled');
			$.post(Drupal.settings.basePath+'storminvoicecharge/payment-callback', paymentForm.serialize(), function(data) {
				if(data.error) {
					$submitBtn.removeAttr('disabled');
					$submitBtn.val('Try Again');
					//paymentForm.find('.payment-response').empty().append('<div class="payment-error"><p>'+data.message+'</p></div>');
					paymentPopulateResult('<div class="payment-error"><p>'+data.message+'</p></div>', paymentForm);
				} else {
					paymentPopulateResult('<div class="payment-success"><p>'+data.message+'</p></div>', paymentForm);
					//paymentForm.find('.payment-response').empty().append('<div class="payment-success"><p>'+data.message+'</p></div>');
				}
			});
		}
	});
}

function checkRequiredFields(fields) {
	var success = true;
	fields.removeClass('error');
	fields.each(function() {
		if($(this).val() === "") {
			success = false;
			$(this).addClass('error');
		}
	});

	return success;
}