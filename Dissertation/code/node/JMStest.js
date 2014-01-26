var express = require('express'),
app = express(),
server = require('http').createServer(app),
io = require('socket.io').listen(server);

app.get('/:file',  function (req, res) {
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


server.listen(8080);