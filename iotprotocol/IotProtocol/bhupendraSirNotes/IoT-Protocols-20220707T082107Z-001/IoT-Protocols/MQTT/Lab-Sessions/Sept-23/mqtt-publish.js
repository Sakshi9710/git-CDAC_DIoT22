/*

MQTT- Publisher Client in Node.JS environment

*/

const mqtt = require('mqtt')

var client = mqtt.connect("mqtt://localhost:1883", options = 
{    
    keepalive: 60,
    clientId : "iottest-123",
    clean: true,
});

/*
callback to publish a message /when there is an successful connection of publisher with broker
*/
const topic = "iot/mqtt"
var payload = "MQTT- Publish Application"
client.on("connect", function()
{
    console.log("Client is connected to broker");
    client.publish(topic,payload)
    console.log("Message Published to the broker")
    client.end()
})

