function returnID()
{
    var url_string = window.location.href;
    var url = new URL(url_string);
    var id = url.searchParams.get("id");
    return id;
}

function checkCheckboxes()
{
    for(i=1;i<=5;i++)
    {
        localID=(returnID()-1)*5+i;
        isItBooked(localID);
    }
}

$(document).ready(function () {
    loadDateAndTime(returnID());
    checkCheckboxes();
});

$("#checkbox1").change(function()
{
    nameOfUser=$("#nameOfUser").val();
    if(this.checked)
    {
        localID=(returnID()-1)*5+1;
        param=nameOfUser+","+localID;
        bookAppointment(param);
    }
    else
    {
        localID=(returnID()-1)*5+1;
        unbookAppointment(localID);
    }
});

$("#checkbox2").change(function()
{
    nameOfUser=$("#nameOfUser").val();
    if(this.checked)
    {
        localID=(returnID()-1)*5+2;
        param=nameOfUser+","+localID;
        bookAppointment(param);
    }
    else
    {
        localID=(returnID()-1)*5+2;
        unbookAppointment(localID);
    }
});

$("#checkbox3").change(function()
{
    nameOfUser=$("#nameOfUser").val();
    if(this.checked)
    {
        localID=(returnID()-1)*5+3;
        param=nameOfUser+","+localID;
        bookAppointment(param);
    }
    else
    {
        localID=(returnID()-1)*5+3;
        unbookAppointment(localID);
    }
});

$("#checkbox4").change(function()
{
    nameOfUser=$("#nameOfUser").val();
    if(this.checked)
    {
        localID=(returnID()-1)*5+4;
        param=nameOfUser+","+localID;
        bookAppointment(param);
    }
    else
    {
        localID=(returnID()-1)*5+4;
        unbookAppointment(localID);
    }
});

$("#checkbox5").change(function()
{
    nameOfUser=$("#nameOfUser").val();
    if(this.checked)
    {
        localID=(returnID()-1)*5+5;
        param=nameOfUser+","+localID;
        bookAppointment(param);
    }
    else
    {
        localID=(returnID()-1)*5+5;
        unbookAppointment(localID);
    }
});

function addDateAndTimeTableRow(response) {
    for(i=0;i<response.length;i++)
    {
        var iPlusOne=i+1;
        var id="#appointmentDateAndTime"+iPlusOne;
        $(id).html(response[i].date+"<br>"+response[i].time);
    }
}

function loadDateAndTime(param) {
  
    $.ajax({
        type: "GET",
        url: "../backend/serviceHandler.php",
        cache: false,
        data: {method: "queryDatesByAppointment",param:param},
        dataType: "json",
        success: function (response) {
            
            addDateAndTimeTableRow(response);
        },
    });
  }

function bookAppointment(param) {
  
    $.ajax({
        type: "GET",
        url: "../backend/serviceHandler.php",
        cache: false,
        data: {method: "queryBookAppointment",param:param},
        dataType: "json",
        success: function (response) {
            //alert("Successfully booked!");
        },
    });
  }

function unbookAppointment(param) {
  
    $.ajax({
        type: "GET",
        url: "../backend/serviceHandler.php",
        cache: false,
        data: {method: "queryUnbookAppointment",param:param},
        dataType: "json",
        success: function (response) {
            //alert("Successfully unbooked!");
        },
    });
  }

  function isItBooked(param) {
  
    $.ajax({
        type: "GET",
        url: "../backend/serviceHandler.php",
        cache: false,
        async: false,
        data: {method: "queryIsItBooked",param:param},
        success: function (response) {
            if(response==1)
            {
                localID=param%5;
                id="#checkbox"+localID;
                $(id).prop('checked', true);
            }
        },
        error: function()
        {
            
        }
    });
  }