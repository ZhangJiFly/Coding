var app = require('express')(),
	server = require('http').createServer(app),
	io = require('socket.io').listen(server),
	mysql = require('mysql');
	
var connection = mysql.createConnection({
    host     : '127.0.0.1',
    user     : 'root',
    password : '',
    database : 'mydb'
});

connection.query('SELECT * FROM Student;', function(error, rows, file){
	console.log(rows);
});


server.listen(8080);

app.get('/:file', function (req, res) {
  var file = req.params.file;
  res.sendfile("/Users/Crippled.Josh/Coding/Dissertation/code/" + file);

});

app.get('/js/libs/:lib/:file', function (req, res) {
  var file = req.params.file,
  lib = req.params.lib;
 res.sendfile("/Users/Crippled.Josh/Coding/Dissertation/code/js/libs/" + lib + '/' + file);
});

app.get('/:folder/:file', function (req, res) {
  var file = req.params.file,
  	folder = req.params.folder;
    res.sendfile("/Users/Crippled.Josh/Coding/Dissertation/code/" + folder + '/' + file);
});

io.sockets.on('connection', function (socket) {
  socket.emit('news', { hello: 'world' });
  socket.on('my other event', function (data) {
    console.log(data);
  });
});