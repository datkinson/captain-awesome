var io = require('socket.io').listen(1337);
var SerialPort = require("serialport").SerialPort;

var connect = require('connect');
connect().use(connect.static(__dirname)).listen(8080);
//Connect to serialport (where the arduino is)
//var serialPort = new SerialPort("/dev/ttyACM0", {
//  baudrate: 9600
//});

io.sockets.on('connection', function (socket) {
  socket.emit('news', { hello: 'world' });
  socket.on('my other event', function (data) {
    console.log(data);
  });
});
