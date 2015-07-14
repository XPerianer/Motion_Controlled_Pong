// Beispiel für die Erstellung einen TCP-Empfängers

var WebSocketServer = require('ws').Server
var DataGetter = new WebSocketServer({host: '0.0.0.0',port:8000});
var Clients = [ false, false];
DataGetter.on('connection',function(ws){
	if(Clients[0] == false){
		var ClientNumber = 0;
		Clients[0] = true;
		tcp_clients.forEach(function each(client,index) {
		client.write("[-2," + ClientNumber + "]");
	});
	}
	else if(Clients[1] == false){
		var ClientNumber = 1;
		tcp_clients.forEach(function each(client,index) {
		client.write("[-2," + ClientNumber + "]");
		Clients[1] = true;
	});
	} else {
		ws.close();
	}
	console.log("Client(DataGetter) mit Websocket verbunden");

	ws.on('message',function(message){ //(empfängt nachrichten)
		//console.log('Von Websocket-Client empfangen: ' + message);

		tcp_clients.forEach(function each(client,index) {
		client.write(message.replace("]",",") + ClientNumber + "]");
		//console.log(message.replace("]",",") + ClientNumber + "]");
		});
	});

	ws.on('close',function(){ //Client is "free"
		Clients[ClientNumber] = false;
		tcp_clients.forEach(function each(client,index) {
		client.write("[-1," + ClientNumber + "]"); //Disconnect message

	});

});


});

var net = require('net');

var tcp_clients = [];

var DataSender = net.createServer(function (socket){
		tcp_clients.push(socket);
		console.log("Client(DataSender) mit Websocket verbunden")
});
DataSender.listen(1337,'0.0.0.0');


//Auslieferung der Webfiles
var connect = require('connect'),
    serveStatic = require('serve-static');

var app = connect();

app.use(serveStatic("webfiles/"));
app.listen(80);
