var app = require('express')(),
	server = require('http').createServer(app),
	io = require('socket.io').listen(server);

var requirejs = require('requirejs');
requirejs.config({
    //Pass the top-level main.js/index.js require
    //function to requirejs so that node modules
    //are loaded relative to the top-level JS file.
    nodeRequire: require
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
 //res.send("/Users/Crippled.Josh/Coding/Dissertation/code/js/libs/" + lib + '/' + file)
});

io.sockets.on('connection', function (socket) {
  socket.emit('news', { hello: 'world' });
  socket.on('my other event', function (data) {
    console.log(data);
  });
});