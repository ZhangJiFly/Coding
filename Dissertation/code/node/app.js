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


//connection.connect();
query.updateStart(pass);



io.sockets.on('connection', function (socket) { 
  socket.on('courseList', function (data) {
    
  });
});

server.listen(8080);