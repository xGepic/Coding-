var modal = document.getElementById("myModal");
var button = document.getElementById("myBtn");
var close = document.getElementsByClassName("close")[0];
var lastAddedAppointmentId;

$(document).ready(function () {
  loadAppointments();
});

button.onclick = function () {
  modal.style.display = "block";
};
close.onclick = function () {
  modal.style.display = "none";
};

window.onclick = function (event) {
  if (event.target == modal) {
    modal.style.display = "none";
  }
};

function addAppointmentTableRow(id,title, location, duration, information) {

    var link = document.createElement("a");
    var linkUrl="Testapp.html?id="+id;
    link.setAttribute("href", linkUrl);//todo
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

$('#theButton').on('click', function () {
  var param=$('#title').val()+","+$('#location').val()+","+$('#duration').val()+","+$('#information').val();
  createNewAppointment(param);
  var paramDateAndTime=lastAddedAppointmentId+","+$('#appointmentoption1').val()+","+$('#appointmentoption2').val()+","+$('#appointmentoption3').val()+","+$('#appointmentoption4').val()+","+$('#appointmentoption5').val();
  postDateTimeArray(paramDateAndTime);
})

function loadAppointments() {
  
  $.ajax({
      type: "GET",
      url: "../backend/serviceHandler.php",
      cache: false,
      data: {method: "queryAppointments"},
      dataType: "json",
      success: function (response) {
        for(var i=0;i<response.length;i++)
        {
          addAppointmentTableRow(response[i].id,response[i].titel,response[i].ort,response[i].duration,response[i].info);
        }
      }
      
  });
}

function createNewAppointment(param) {
  
  $.ajax({
      type: "GET",
      url: "../backend/serviceHandler.php",
      cache: false,
      data: {method: "queryPostAppointment",param:param},
      dataType: "json",
      async: false,
      success: function (response) {
        lastAddedAppointmentId=response;
        addAppointmentTableRow(response,$('#title').val(),$('#location').val(),$('#duration').val(),$('#information').val());
      },
  });
}

function postDateTimeArray(param) {
  
  $.ajax({
      type: "GET",
      url: "../backend/serviceHandler.php",
      cache: false,
      data: {method: "queryPostDateTimeArray",param:param},
      dataType: "json",
      async: false,
      success: function (response) {
        alert("Successfully added date and time array");
      },
  });
}

function deleteRow() {
  var table = document.getElementById("myTable");
  var rowCount = table.rows.length;
  if (rowCount < 3) {
  } else {
    table.deleteRow(rowCount - 1);
  }
}
