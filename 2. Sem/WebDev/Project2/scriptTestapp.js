//Function that searches and returns the ID of an Appointment
function returnID() {
  var url_string = window.location.href;
  var url = new URL(url_string);
  var id = url.searchParams.get("id");
  return id;
}

//Load Date and Time as soon as DOM is ready for JS Code
$(document).ready(function () {
  loadDateAndTime(returnID());
  loadHistoryTable(returnID());
  //checkCheckboxes();
});

//Function that sends name to Backend when the Checkbox1 is active
$("#checkbox1").change(function () {
  nameOfUser = $("#nameOfUser").val();
  commentOfUser = $("#commentOfUser").val();
  if (this.checked) {
    localID = (returnID() - 1) * 5 + 1;
    param = localID + "," + nameOfUser + "," + commentOfUser;
    bookAppointment(param);
  } else {
    localID = (returnID() - 1) * 5 + 1;
    unbookAppointment(localID);
  }
});

//Function that sends name to Backend when the Checkbox2 is active
$("#checkbox2").change(function () {
  nameOfUser = $("#nameOfUser").val();
  commentOfUser = $("#commentOfUser").val();
  if (this.checked) {
    localID = (returnID() - 1) * 5 + 2;
    param = localID + "," + nameOfUser + "," + commentOfUser;
    bookAppointment(param);
  } else {
    localID = (returnID() - 1) * 5 + 2;
    unbookAppointment(localID);
  }
});

//Function that sends name to Backend when the Checkbox3 is active
$("#checkbox3").change(function () {
  nameOfUser = $("#nameOfUser").val();
  commentOfUser = $("#commentOfUser").val();
  if (this.checked) {
    localID = (returnID() - 1) * 5 + 3;
    param = localID + "," + nameOfUser + "," + commentOfUser;
    bookAppointment(param);
  } else {
    localID = (returnID() - 1) * 5 + 3;
    unbookAppointment(localID);
  }
});

//Function that sends name to Backend when the Checkbox4 is active
$("#checkbox4").change(function () {
  nameOfUser = $("#nameOfUser").val();
  commentOfUser = $("#commentOfUser").val();
  if (this.checked) {
    localID = (returnID() - 1) * 5 + 4;
    param = localID + "," + nameOfUser + "," + commentOfUser;
    bookAppointment(param);
  } else {
    localID = (returnID() - 1) * 5 + 4;
    unbookAppointment(localID);
  }
});

//Function that sends name to Backend when the Checkbox5 is active
$("#checkbox5").change(function () {
  nameOfUser = $("#nameOfUser").val();
  commentOfUser = $("#commentOfUser").val();
  if (this.checked) {
    localID = (returnID() - 1) * 5 + 5;
    param = localID + "," + nameOfUser + "," + commentOfUser;
    bookAppointment(param);
  } else {
    localID = (returnID() - 1) * 5 + 5;
    unbookAppointment(localID);
  }
});

//Function that adds Date and time to the appropiate location in Frontend
function addDateAndTimeTableRow(response) {
  for (i = 0; i < response.length; i++) {
    var iPlusOne = i + 1;
    var idDT = "#appointmentDateAndTime" + iPlusOne;
    $(idDT).html(response[i].date + "<br>" + response[i].time);
    if (response[i].nameVonBenutzer != null) {
    }
  }
}

function addHistoryTableRow(response) {
  var name = response.nameVonBenutzer;
  var date = response.date;
  var time = response.time;
  var comment=response.comment;
  var table = document.getElementById("HistoryTabelle");
  var row = document.createElement("TR");
  row.setAttribute("id", response.id);
  var cell1 = document.createElement("TD");
  var cellText1 = document.createTextNode(name);
  cell1.appendChild(cellText1);
  row.appendChild(cell1);
  var cell2 = document.createElement("TD");
  var cellText2 = document.createTextNode(date);
  cell2.appendChild(cellText2);
  row.appendChild(cell2);
  var cell3 = document.createElement("TD");
  var cellText3 = document.createTextNode(time);
  cell3.appendChild(cellText3);
  row.appendChild(cell3);
  var cell4 = document.createElement("TD");
  var cellText4 = document.createTextNode(comment);
  cell4.appendChild(cellText4);
  row.appendChild(cell4);
  table.appendChild(row);
}


//Function that loads Date and Time from Backend with the help of ajax
function loadDateAndTime(param) {
  $.ajax({
    type: "GET",
    url: "../backend/serviceHandler.php",
    cache: false,
    data: { method: "queryDatesByAppointment", param: param },
    dataType: "json",
    success: function (response) {
      addDateAndTimeTableRow(response);
    },
  });
}

function loadHistoryTable(param)
{
    $.ajax({
        type: "GET",
        url: "../backend/serviceHandler.php",
        cache: false,
        data: { method: "queryVotingsByAppointment", param: param },
        dataType: "json",
        success: function (response) {
            for (var i = 0; i < response.length; i=i+2) {
                var temp={nameVonBenutzer:response[i].nameVonBenutzer, date:response[i+1].date, time:response[i+1].time, comment:response[i].comment};
                addHistoryTableRow(temp);
            }
        },
      });
}

//Function that is called when a checkbox is ticked to send information to backend
function bookAppointment(param) {
  $.ajax({
    type: "GET",
    url: "../backend/serviceHandler.php",
    cache: false,
    data: { method: "queryBookAppointment", param: param },
    dataType: "json",
    async: true,
    success: function (response) {
        var temp = {nameVonBenutzer:document.getElementById("nameOfUser").value, date:response.date, time:response.time, comment:document.getElementById("commentOfUser").value};
        addHistoryTableRow(temp);
    },
  });
}
