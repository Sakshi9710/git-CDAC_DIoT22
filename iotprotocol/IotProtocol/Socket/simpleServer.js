const http = require("http");
const { WebSocketServer } = require('ws');

const server = http.createServer();

const wss = new WebSocketServer({ server});

var client1 , client2;

wss.on('connection', function (ws) {
    if(!client1) {
      client1=client;
    }
    else {
      client2=client;
    }

    client1.on('message',function message(data) {
      console.log(data.toString())
      client1.send('User1 : ' + data.toString())
    });

    client2.on('message',function message(data) {
      console.log(data.toString())
      client2.send('User2 : ' + data.toString())
    });
});

server.listen(8080);