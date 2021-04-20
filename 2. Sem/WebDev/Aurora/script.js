$(window).on("load", function() {
    "use strict";

    $(".user-info").on("click", function(){
        $(this).next(".user-account-settingss").toggleClass("active");
    });

});
