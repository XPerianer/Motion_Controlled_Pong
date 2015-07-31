//Motion_Controlled_Pong to play Pong with your Smartphone and a Raspberry Pi.
//Copyright (C) 2015  Dominik Meier (XPerianer) <hiscore.pressthebutton@hotmail.de>

//This program is free software: you can redistribute it and/or modify
//the Free Software Foundation, either version 3 of the License, or
//it under the terms of the GNU General Public License as published by
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program.  If not, see <http://www.gnu.org/licenses/>.

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
	console.log("Client(DataGetter) connected to Websocket");

	ws.on('message',function(message){ //(recieves messages)
		//console.log('Reveived by Client: ' + message); //Debug

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
	console.log("Client(DataSender) connected to Websocket")

});


//Auslieferung der Webfiles
var connect = require('connect'),
    serveStatic = require('serve-static');

var app = connect();

app.use(serveStatic("webfiles/"));
app.listen(80);

var net = require('net');
