var io = require('socket.io').listen(1337);
var SerialPort = require("serialport").SerialPort;
var portName = 'ttyACM0';

var sp = new SerialPort("COM3", {baudRate: 9600, dataBits: 8, parity: 'none', stopBits: 1, flowControl: false}); // instantiate the serial port.
console.log("Started");

io.sockets.on('connection', function (socket) {
    console.log("Socket Connection");
    // If socket.io receives message from the client browser then
    // this call back will be executed.
    socket.on('message', function (msg) {
        console.log(msg);
    });
    // If a web browser disconnects from Socket.IO then this callback is called.
    socket.on('disconnect', function () {
        console.log('disconnected');
    });
});

var cleanData = ''; // this stores the clean data
var readData = '';  // this stores the buffer
var compiledData = '';
sp.on('data', function (data) { // call back when data is received    
    readData = data.toString(); // append data to buffer
    
    if(readData.indexOf('|') >= 0){
        compiledData = readData;
    } else{
        compiledData += readData;
    }
    
    if(compiledData.indexOf('~') >= 0){
        // Start parsing data
        if (compiledData.indexOf('|') >= 0 && compiledData.indexOf('~') >= 0) {
            cleanData = compiledData.substring(compiledData.indexOf('|') + 1, compiledData.indexOf('~'));
            compiledData = '';
            if(cleanData.length > 4){
                console.log(cleanData);
                io.sockets.emit('serialEvent', cleanData);
            }
        }
    }
    readData = '';
});

