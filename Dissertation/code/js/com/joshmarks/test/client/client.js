(function()
{
define(['jquery','socket.io', 'underscore', 'backbone'], function($,io, _, bb)
{
	var msg = "cunt";
	var socket = io.connect('http://localhost:8888');
	// socket.on('message', function(data){
	// 	console.log(data);
	// 	socket.emit('message', msg)
	// });
	var PersonVO = function(first, last)
	{
		return {
			firstName: first,
			lastName: last,
			getPrettyName: function()
			{
				return lastName + "," + firstName;
			}
		};
	};
	return PersonVO;
});
}
)();