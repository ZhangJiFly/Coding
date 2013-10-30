var //url = require("url"),
    //path = require("path"),
    //fs = require("fs"),
    express = require('express'),
    app = express(),
    server = require("http").createServer(app),
    io = require('socket.io').listen(server);

app.get('./../', function(req, res){
  console.log(req);
  console.log(res);
  res.sendfile(prcoess.cwd(),'/index.html');

});

app.listen(8888)
// server = http.createServer(function(request, response) {
//   var uri = url.parse(request.url).pathname,
//     filename = path.join(process.cwd(), "../" + uri);
//   path.exists(filename, function(exists) {
    
//     if(!exists) {
//       response.writeHead(404, {"Content-Type": "text/plain"});
//       response.write("404 Not Found\n");
//       response.end();
//       return;
//     }
//     if (fs.statSync(filename).isDirectory()) filename += '/index.html';
 
//     fs.readFile(filename, "binary", function(err, file) {
//       if(err) {        
//         response.writeHead(500, {"Content-Type": "text/plain"});
//         response.write(err + "\n");
//         response.end();
//         return;
//       }
 
//       response.writeHead(200);
//       response.write(file, "binary");
//       response.end();
//     });
//   });
// });



io.sockets.on('connection', function (client){ 
 
  io.sockets.emit('message', "Huzzah", function(){
  		  
  });

  client.on('message', function () {
  }) ;

  client.on('disconnect', function () {
  });
});


