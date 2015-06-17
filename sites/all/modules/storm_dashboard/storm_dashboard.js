// $Id: storm_dashboard.js,v 1.12 2009/11/15 17:19:00 jurgenhaas Exp $
(function ($) {

Drupal.admin = Drupal.admin || {};

Drupal.behaviors.stormdashboard = function (context) {
  Drupal.admin.stormdashboardInitComponents();
  if ($('#sdb').size() > 0) {
    Drupal.admin.stormdashboardInteract("getStack", 0, 0, true);
  }
  // Calculate top and left offset for the sdb-lightbox.
  var width = 830;
  var height = 430;
  var arrayPageSize   = Drupal.admin.getPageSize();
  var top  = (arrayPageSize[3] - height) / 2;
  var left = (arrayPageSize[2] - width) / 2;
  $('#sdb-light').css({
    'zIndex': '10500',
    'top': top + 'px',
    'left': left + 'px'
  });
};

Drupal.admin.stormdashboardInitComponents = function () {
  $('#sdb-timetracking .icon:not(.storm-dashboard-processed)')
    .addClass('storm-dashboard-processed')
    .click(function () {
      $('#sdb-light').toggle('fast');
      $('#sdb-timetracking').toggleClass('sdb-light-visible');
    });
  $('.storm-dashboard-active:not(.storm-dashboard-processed)')
    .addClass('storm-dashboard-processed')
    .change(function () {
      var tid = this.getAttribute('id')+'-content';
      var nid = this.value;
      Drupal.admin.stormdashboardInteract("getChilds", tid, nid, true);
    })
  $('#edit-collapse-on-select:not(.storm-dashboard-processed)')
    .addClass('storm-dashboard-processed')
    .click(function () {
      var mode = this.checked;
      Drupal.admin.stormdashboardInteract("setAutoCollapseMode", mode, '', false);
    })
  $('.storm-dashboard-unselect:not(.storm-dashboard-processed)')
    .addClass('storm-dashboard-processed')
    .click(function () {
      var s = $(this).parents('fieldset').find('select').get(0);
      var tid = s.getAttribute('id')+'-content';
      var nid = 0;
      s.selectedIndex = -1;
      Drupal.admin.stormdashboardInteract("getChilds", tid, nid, true);
    })
  $('#sdb-org .toggle:not(.storm-dashboard-processed)')
    .addClass('storm-dashboard-processed')
    .click(function () {
      Drupal.admin.toggleOrg();
    })
  $('.sdb-timetracking-trigger:not(.storm-dashboard-processed)')
    .addClass('storm-dashboard-processed')
    .click(function () {
      var info = 0;
      var status = $(this).hasClass('timetracking-active');
      $('.timetracking-active').removeClass('timetracking-active');
      if (status) {
        info = 0;
      }
      else {
        $(this).addClass('timetracking-active');
        info = this.getAttribute('id');
      }
      try {
        $('.storm-quicktt-timer').stopTime();
      } catch (e) {
        // Storm QuickTT not available, doesn't matter
      }
      Drupal.admin.stormdashboardInteract("startTimeTracking", info, 0, true);
    })
  try {
    Drupal.admin.stormquickttInit();
  } catch (e) {
    // Storm QuickTT not available, doesn't matter
  }
};

Drupal.admin.hide = function (sel) {
  $(sel).hide("slow");
}

Drupal.admin.show = function (sel) {
  $(sel).show("slow");
}

Drupal.admin.toggleOrg = function () {
  if ($('#sdb-org .right').css('display') == 'none') {
    Drupal.admin.show('#sdb-org .orgtoggle');
  }
  else {
    Drupal.admin.hide('#sdb-org .orgtoggle');
  }
};

// getPageScroll()
// Returns array with x,y page scroll values.
// Core code from - quirksmode.com.
// borrowed from Lightbox.js
Drupal.admin.getPageScroll = function() {

  var xScroll, yScroll;

  if (self.pageYOffset) {
    yScroll = self.pageYOffset;
    xScroll = self.pageXOffset;
  }
  else if (document.documentElement && document.documentElement.scrollTop) {  // Explorer 6 Strict.
    yScroll = document.documentElement.scrollTop;
    xScroll = document.documentElement.scrollLeft;
  }
  else if (document.body) {// All other Explorers.
    yScroll = document.body.scrollTop;
    xScroll = document.body.scrollLeft;
  }

  arrayPageScroll = [xScroll,yScroll];
  return arrayPageScroll;
};

// getPageSize()
// Returns array with page width, height and window width, height.
// Core code from - quirksmode.com.
// Edit for Firefox by pHaez.
// borrowed from Lightbox.js
Drupal.admin.getPageSize = function() {

  var xScroll, yScroll;

  if (document.body.scrollHeight > document.body.offsetHeight) { // all but Explorer Mac
    xScroll = document.body.scrollWidth;
    yScroll = document.body.scrollHeight;
  }
  else if (window.innerHeight && window.scrollMaxY) {
    xScroll = window.innerWidth + window.scrollMaxX;
    yScroll = window.innerHeight + window.scrollMaxY;
  }
  // Explorer Mac...would also work in Explorer 6 Strict, Mozilla and Safari.
  else {
    xScroll = document.body.offsetWidth;
    yScroll = document.body.offsetHeight;
  }

  var windowWidth, windowHeight;

  if (self.innerHeight) { // All except Explorer.
    if (document.documentElement.clientWidth) {
      windowWidth = document.documentElement.clientWidth;
    }
    else {
      windowWidth = self.innerWidth;
    }
    windowHeight = self.innerHeight;
  }
  // Explorer 6 Strict Mode.
  else if (document.documentElement && document.documentElement.clientHeight) {
    windowWidth = document.documentElement.clientWidth;
    windowHeight = document.documentElement.clientHeight;
  }
  else if (document.body) { // Other Explorers.
    windowWidth = document.body.clientWidth;
    windowHeight = document.body.clientHeight;
  }


  // For small pages with total height less then height of the viewport.
  if (yScroll < windowHeight) {
    pageHeight = windowHeight;
  }
  else {
    pageHeight = yScroll;
  }


  // For small pages with total width less then width of the viewport.
  if (xScroll < windowWidth) {
    pageWidth = windowWidth;
  }
  else {
    pageWidth = xScroll;
  }

  arrayPageSize = [pageWidth, pageHeight, windowWidth, windowHeight];
  return arrayPageSize;
};

Drupal.admin.stormdashboardInteract = function (_op, _id, _nid, _display) {
  $.ajax({
    url: Drupal.settings.storm_dashboard_url,
    global: false,
    type: "POST",
    data: ({
      op : _op,
      id : _id,
      nid : _nid,
      mainView : ($('#sdb.main').size() > 0)
    }),
    dataType: "html",
    beforeSend: function() {
      if (_display) {
        $("#sdb-loading").show("fast");
      }
    },
    complete: function() {
      $("#sdb-loading").hide("fast");
    },
    success: function (answer) {
      if (answer=='') {
        return;
      }
      try {
        var x = JSON.parse(answer, '');
        for (var i = 0; i < x.length; i++) {
          switch (x[i].cmd) {
            case 'modContent':
              $(x[i].selector).html(x[i].content);
              break;
            case 'replaceContent':
              $(x[i].selector).replaceWith(x[i].content);
              break;
            case 'addClass':
              $(x[i].selector).addClass(x[i].content);
              break;
            case 'removeClass':
              $(x[i].selector).removeClass(x[i].content);
              break;
            case 'hide':
              Drupal.admin.hide(x[i].selector);
              break;
            case 'show':
              Drupal.admin.show(x[i].selector);
              break;
            case 'sdblight':
                $('body').append('<div id="sdb-light">'+x[i].content+'</div>');
              break;
            case 'alert':
              alert(x[i].content);
              break;
          }
        }
        Drupal.admin.stormdashboardInitComponents();
      } catch (e) {
        alert('Error: Feedback from server has been ' + answer.substr(0,500));
      }
    },
    error: function (XMLHttpRequest, textStatus, errorThrown) {
      alert(XMLHttpRequest.statusText);
    }
  });
};

})(jQuery);
