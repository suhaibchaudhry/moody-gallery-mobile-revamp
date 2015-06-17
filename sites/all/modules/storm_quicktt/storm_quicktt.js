// $Id: storm_quicktt.js,v 1.5 2009/11/03 20:09:19 jurgenhaas Exp $
(function ($) {

Drupal.admin = Drupal.admin || {};

Drupal.behaviors.stormquicktt = function (context) {
  Drupal.admin.stormquickttInit();
};

Drupal.admin.stormquickttInit = function () {
  $('#stormquicktt #edit-selects-projects:not(.storm-quicktt-processed)')
    .addClass('storm-quicktt-processed')
    .change(function () {
      $('.storm-quicktt-timer').stopTime();
      var id = this.value;
      var x = $('#stormquicktt #edit-selects-mode')[0];
      var mode = $('#stormquicktt #edit-selects-mode')[0].checked;
      Drupal.admin.stormquickttInteract("startstop", id, mode);
    })
  $('.storm-quicktt-pause:not(.storm-quicktt-processed)')
    .addClass('storm-quicktt-processed')
    .click(function () {
      Drupal.admin.stormquickttInteract("pause", 0, 0);
    })
  $('.storm-quicktt-resume:not(.storm-quicktt-processed)')
    .addClass('storm-quicktt-processed')
    .click(function () {
      Drupal.admin.stormquickttInteract("resume", 0, 0);
    })
  $('#edit-storm-quicktt-note:not(.storm-quicktt-processed)')
    .addClass('storm-quicktt-processed')
    .change(function () {
      Drupal.admin.stormquickttInteract("note", this.value, 0);
      this.value = '';
      $(this).focus();
    })
  Drupal.admin.stormquickttInitTimer();
};

Drupal.admin.stormquickttInitTimer = function () {
  $('.storm-quicktt-timer').everyTime(60000, function(i) {
      Drupal.admin.stormquickttInteract("update", 0, 0);
    });
};

Drupal.admin.stormquickttInteract = function (_op, _nid, _mode) {
  $.ajax({
    url: Drupal.settings.storm_quicktt_url,
    global: false,
    type: "POST",
    data: ({
      op : _op,
      nid : _nid,
      mode: _mode
    }),
    dataType: "html",
    complete: function() {
      
    },
    success: function (answer) {
      if (answer=='OK') {
        switch (_op) {
          case 'pause':
            $('.storm-quicktt-pause').hide();
            $('.storm-quicktt-resume').show();
            break;
          case 'resume':
            $('.storm-quicktt-pause').show();
            $('.storm-quicktt-resume').hide();
            break;
        }
      }
      else {
        switch (_op) {
          case 'update':
            if (answer == '') {
              //This shouldn't happen
            }
            else {
              $('.storm-quicktt-timer').stopTime();
              $('.storm-quicktt-timer').html(answer);
              Drupal.admin.stormquickttInitTimer();
            }
            break;
          default:
            $('#sdb-timetracking').html(answer);
            $('.storm-quicktt-info').html(answer);
            try {
              Drupal.admin.stormdashboardInitComponents();
            } catch (e) {
              //in this case storm_dashboard is not installed, doesn't matter
            }
            Drupal.admin.stormquickttInit();
            break;
        }
      }
    },
    error: function (XMLHttpRequest, textStatus, errorThrown) {
      alert(XMLHttpRequest.statusText);
    }
  });
};

})(jQuery);
