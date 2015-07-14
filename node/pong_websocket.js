// Beispiel für die Erstellung einen TCP-Empfängers

var WebSocketServer = require('ws').Server
var DataGetter = new WebSocketServer({host: '0.0.0.0',port:8000});
var Clients = [ false, false];
DataGetter.on('connection',function(ws){
	if(Clients[0] == false){
		var ClientNumber = 0;
		Clients[0] = true;
		DataSender.clients.forEach(function each(client,index) {
		client.send("[-2," + ClientNumber + "]");
	});
	}
	else if(Clients[1] == false){
		var ClientNumber = 1;
		DataSender.clients.forEach(function each(client,index) {
		client.send("[-2," + ClientNumber + "]");
		Clients[1] = true;
	});
	} else {
		ws.close();
	}
	console.log("Client(DataGetter) mit Websocket verbunden");

	ws.on('message',function(message){ //(empfängt nachrichten)
		//console.log('Von Websocket-Client empfangen: ' + message);

		DataSender.clients.forEach(function each(client,index) {
		client.send(message.replace("]",",") + ClientNumber + "]");
		//console.log(message.replace("]",",") + ClientNumber + "]");
		});
	});

	ws.on('close',function(){ //Client is "free"
		Clients[ClientNumber] = false;
		DataSender.clients.forEach(function each(client,index) {
		client.send("[-1," + ClientNumber + "]"); //Disconnect message

	});

});


});

var DataSender = new WebSocketServer({host: '0.0.0.0',port:1337});

DataSender.on('connection',function(ws){
	console.log("Client(DataSender) mit Websocket verbunden")

});


//Auslieferung der Webfiles
var connect = require('connect'),
    serveStatic = require('serve-static');

var app = connect();

app.use(serveStatic("webfiles/"));
app.listen(80);

var net = require('net');
