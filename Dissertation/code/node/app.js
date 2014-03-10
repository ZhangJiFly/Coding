var mysql = require('mysql'),

connection = mysql.createConnection({
    host     : '127.0.0.1',
    user     : 'root',
    password : '',
    database : 'mydb'
}),
query = require('QueryFunctions')(connection),
auth = require('Authentication')(query),
server = require('routes')(auth, query),
io = require('socket.io').listen(server);


var createYear = function(num){
  return "<div class='row'><div class='panel panel-primary'><div class='panel-heading'>"+ num + "Year Course List</div><div class='panel-body'><div class='w2ui-label'> List:</div><div class='w2ui-field'><input type='list' style='width: 200px; box-sizing: border-box; padding-right: 14px;' placeholder=' class='w2field'/><div style='color: rgb(0, 0, 0); font-size: 14px; padding: 3px; margin-top: 1px; margin-bottom: 1px; margin-left: -16px'; class='w2ui-field-helper'></div><span class='legend'></span><div style='height: 30px;'></div></div></div></div></div>";
}

var createYears = function(){
  for(var i= 0; i<4;i++){
    var string = createYear(i);
    $('#years').append(string);
  }
}

query.updateStart(pass);

io.sockets.on('connection', function (socket) { 
  socket.on('courseList', function (data) {
    
  });
});

server.listen(8080);