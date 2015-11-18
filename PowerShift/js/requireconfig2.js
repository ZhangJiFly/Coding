require.config({
		baseUrl: "/",
		waitSeconds: 10,
		packages: [{
			name: "jquery",
			location: "libs/jquery",
			main: "jquery"
		},
		{
			name: "json2",
			location: "libs/json2",
			main: "json2"
		},
		{
			name: "underscore",
			location: "libs/underscore",
			main: "underscore"
		},
		{
			name: "backbone",
			location: "libs/backbone",
			main: "backbone"
		},
		{
			name: "socket.io",
			location: "../socket.io",
			main: "socket.io"
		}]
	});