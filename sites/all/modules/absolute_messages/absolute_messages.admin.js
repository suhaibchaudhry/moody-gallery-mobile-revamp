(function ($) {

  $(document).ready(function(){

    // Show/hide "Automatically dismiss ... messages after ... seconds"
    // textfield based on relevant checkbox value.
    $(".absolute-message-dismiss-checkbox").click(function(){
      var message_type = $(this).attr("id").replace("edit-absolute-messages-dismiss-", "");
      if ($(this).attr("checked")) {
        $("#absolute-messages-dismiss-time-"+message_type+"-wrapper").show();
      } else {
        $("#absolute-messages-dismiss-time-"+message_type+"-wrapper").hide();
      }
    });

  });

})(jQuery);
