//Var for Modal
var modal = document.getElementById("myModal");
//Var for Add App Button
var button = document.getElementById("myBtn");
//Var for Close Modal
var close = document.getElementsByClassName("close")[0];
//Var for Last Added Appointment
var lastAddedAppointmentId;

//Function that loads Appointments as soon as DOM is ready for JS Code
$(document).ready(function () {
  loadAppointments();
});

//On Click the Button will show the Modal
button.onclick = function () {
  modal.style.display = "block";
};

//On Click at the "X" the Modal will be closed
close.onclick = function () {
  modal.style.display = "none";
};

//By Clicking somewhere next to the Modal, the Modal will be closed as well
window.onclick = function (event) {
  if (event.target == modal) {
    modal.style.display = "none";
  }
};

//Funtion to add a new Appointment to the Table
function addAppointmentTableRow(id, title, location, duration, information) {
  var link = document.createElement("a");
  var linkUrl = "Testapp.html?id=" + id;
  link.setAttribute("href", linkUrl);
  link.setAttribute("id", id);
  var linkText = document.createTextNode(title);
  link.appendChild(linkText);

  var table = document.getElementById("myTableAppointment");
  var rowCount = table.rows.length;
  var row = table.insertRow(rowCount);
  var cell1 = row.insertCell(0);
  var cell2 = row.insertCell(1);
  var cell3 = row.insertCell(2);
  var cell4 = row.insertCell(3);
  cell1.appendChild(link);
  cell2.innerHTML = location;
  cell3.innerHTML = duration;
  cell4.innerHTML = information;
}

//Function that triggers by clicking the add button in the Modal
$("#theButton").on("click", function () {
  //Title, location, duration and information will be used to create an Appointment and to display it on our index.html
  var param =
    $("#title").val() +
    "," +
    $("#location").val() +
    "," +
    $("#duration").val() +
    "," +
    $("#information").val();
  createNewAppointment(param);
  var paramDateAndTime =
  //The 5 Appointment Options will be sent to the backend to get displayed on the appropriate Site
    lastAddedAppointmentId +
    "," +
    $("#appointmentoption1").val() +
    "," +
    $("#appointmentoption2").val() +
    "," +
    $("#appointmentoption3").val() +
    "," +
    $("#appointmentoption4").val() +
    "," +
    $("#appointmentoption5").val();
  postDateTimeArray(paramDateAndTime);
});

//Function that loads the Appointments from the Backend with the help of Ajax
function loadAppointments() {
  $.ajax({
    type: "GET",
    url: "../backend/serviceHandler.php",
    cache: false,
    data: { method: "queryAppointments" },
    dataType: "json",
    success: function (response) {
      for (var i = 0; i < response.length; i++) {
        addAppointmentTableRow(
          response[i].id,
          response[i].titel,
          response[i].ort,
          response[i].duration,
          response[i].info
        );
      }
    },
  });
}

//Function to create a new Appointment with the help of Ajax
function createNewAppointment(param) {
  $.ajax({
    type: "GET",
    url: "../backend/serviceHandler.php",
    cache: false,
    data: { method: "queryPostAppointment", param: param },
    dataType: "json",
    async: false,
    success: function (response) {
      lastAddedAppointmentId = response;
      addAppointmentTableRow(
        response,
        $("#title").val(),
        $("#location").val(),
        $("#duration").val(),
        $("#information").val()
      );
    },
  });
}

//Function that takes all dates and times from appointment and sends them to backend with the help of Ajax
function postDateTimeArray(param) {
  $.ajax({
    type: "GET",
    url: "../backend/serviceHandler.php",
    cache: false,
    data: { method: "queryPostDateTimeArray", param: param },
    dataType: "json",
    async: false,
    success: function (response) {
      //alert("Successfully added date and time array");
    },
  });
}

//Function to delete the Post from Backend with the help of Ajax
function deletePost(param) {
  $.ajax({
    type: "GET",
    url: "../backend/serviceHandler.php",
    cache: false,
    data: { method: "queryDeleteAppointment", param: param },
    dataType: "json",
    success: function (response) {
      //alert("Successfully deleted post!");
    }
  });
}

//Function to Delete a Post from our Table
//The Table alawys has at least one row because that is where the header of the Table is located
function deleteOne() {
  var table = document.getElementById("myTableAppointment");
  var rowCount = table.rows.length;

  if (rowCount == 1) {
    alert("There are no Appointments to delete!");
  } else {
    var whichApp = prompt(
      "Enter the Number of the Appointment that has to be deleted "
    );
    if (whichApp < 1) {
      alert("Error!");
      return;
    }
    var realID=table.rows[whichApp].cells[0].children[0].id;
    table.deleteRow(whichApp);
    deletePost(realID);
  }
}
