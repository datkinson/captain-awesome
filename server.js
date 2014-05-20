var io = require('socket.io').listen(1337);
var SerialPort = require("serialport").SerialPort;

//Connect to serialport (where the arduino is)
var serialPort = new SerialPort("/dev/ttyACM0", {
  baudrate: 9600
});

//Only register the listeners when it's okay to do so.
//serialPort.on("open", function () {
	//Web sockets lolwot
	io.sockets.on('connection', function (socket) {
 		socket.on('cmd', function (data) {
 			console.log(data);
			serialPort.write(data);
  		});
	});
//});
