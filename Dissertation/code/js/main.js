console.log("cunt");
require(['socket.io'], function(io){
	var socket = io.connect('http://localhost');
	socket.on('news', function (data) {
   		console.log(data);
   		socket.emit('my other event', { my: 'data' });
	});
});
