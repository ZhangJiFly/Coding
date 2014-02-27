require.config({
  baseUrl: "../js"
});

require(['jquery', 'socket.io', 'datatables'], function($, io, dataTable){
  var groupCounter = 0;
  var coursesTotal;
  var courses = []; 
  var choices = [];
  var createGroup = function(){

    var group = groupCounter
    groupCounter++;
    courses.push(coursesTotal);
    choices.push([]);



    $('#main').append("<div class='row' group='"+ group + "'><div class='panel panel-primary'><div class='panel-heading'>Group: " + (group + 1) + "</div><div class='panel-body'><div class='col-md-6'><div class='form-group'>Minimum Credits: <input type='number' name='Credits' min='0' max='0' required id='credits" + group+ "''></div><table cellpadding='0' cellspacing='0' border='0' class='display dataTable' id='choices" + group + "' group='"+ group + "'></table></div><div class='col-md-6'><table cellpadding='0' cellspacing='0' border='0' class='display dataTable' group='"+ group + "' id='courses" + group + "'></table></div></div></div>");
    $('#choices'+group).dataTable( {
      "bFilter": false,
      "bInfo": false,
      "bPaginate": false,
      "bAutoWidth": false,
      "sScrollY": "300px",
      "aaData": choices[group],
      "sStripeOdd":true,
      "aoColumns": [
        {
        "mData": function (data, type, val) {
          return "<button type='button' group=" + group + " class='btn btn-default' id='remove'>Remove</button>"
        },
        "fnCreatedCell": function(Td, sData, oData, iRow, iCol){
          var btn = $(Td)['context']['firstChild']; //Terrible coding.. cannot get anything else to work so this will be OK for demonstration purposes.
          var button = $(btn);
          var table = $('#choices' + group);
          button.click(function(){
            var aPos = table.dataTable().fnGetPosition(Td);
            var row = table.dataTable().fnGetData(aPos[0]);
            var credits = row.Credit;
            $('#courses' + group).dataTable().fnAddData([row]);
            var max = $('#credits' + group)[0]['attributes']['max'].value
            $('#credits' + group)[0]['attributes']['max'].value = parseInt(max) - parseInt(credits); 
            console.log(choices[group][aPos[0]]);
            choices[group].splice(aPos[0],1);
            table.dataTable().fnDeleteRow(aPos[0]);
          });
          }, "sTitle": "Remove", "sWidth": 25
        },
        {"mData":"CourseId", "sTitle": "Course ID", "sWidth": 10 },
        {"mData": "Name", "sTitle": "Course Name", "sWidth": 30 },
        {"mData": "Credit", "sTitle": "Credits", "sWidth": 20},
        ]
    } );
    $('#courses'+group).dataTable( {
      "aaData": courses[group],
      "bInfo": false,
      "bPaginate": false,
      "bScrollCollapse": true,
      "sScrollY": "300px",
      "bAutoWidth": false,
      "aoColumns": [
        {
          "mData": function (data, type, val) {
            return "<button type='button' group=" + group + " class='btn btn-default' id='select'>Select</button>"
          },
          "fnCreatedCell": function(Td, sData, oData, iRow, iCol){
            var btn = $(Td)['context']['firstChild']; //Terrible coding.. cannot get anything else to work so this will be OK for demonstration purposes.
            var button = $(btn);
            var table = $('#courses' + group);
            button.click(function(){
              var aPos = table.dataTable().fnGetPosition(Td);
              var row = table.dataTable().fnGetData(aPos[0]);
              choices[group].push(row);
              $('#choices' + group).dataTable().fnAddData([row]);
              var tr = table[0]['tBodies'][0]['childNodes'][aPos[0]];
              table.dataTable().fnDeleteRow(aPos[0]);
              var credits = row.Credit;
              var max = $('#credits' + group)[0]['attributes']['max'].value
              $('#credits' + group)[0]['attributes']['max'].value = parseInt(max) + parseInt(credits); 
            });
          },
          "sTitle": "Select", "sWidth":50 },
        {"mData":"CourseId", "sTitle": "Course ID", "sWidth":40 },
        {"mData": "Name", "sTitle": "Course Name", "sWidth":40 },
        {"mData": "Credit", "sTitle": "Credits", "sWidth":20 },
        {"mData": "Level", "sTitle": "Level", "sWidth":20 },  
      ]
    } );
  }
  var socket = io.connect('http://localhost');
  socket.emit('coursesPlease', "Engineering");
  socket.on('courses', function (data) {
    coursesTotal = data;
    createGroup();
  });
    
  $('#addGroup').click(function(){

    createGroup();
    getSubmitValues();
  });
  
  var getSubmitValues = function(){
    var details = {
      "groups": [],
      "listName": $('#CourseListName')[0].value,
      "school": "Engineering",
      "level":3,
    }
    var data = [];
    for (var i = 0; i<groupCounter; i++){
      var group = {};
      var credits = $('#credits' + i)[0].valueAsNumber;

      group.credits = credits;
      group.courses = choices[i];
      details.groups.push(group);
     }
    return details;
  }
  //$('#submit').click(getSubmitValues);
  $('#courselist').submit(function () {
    socket.emit('courseList', getSubmitValues());
    return true;
  });
});