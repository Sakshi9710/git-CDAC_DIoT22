const mqtt = require('mqtt');
var count = 1;
const topic = "iot/mqtt"
var client = mqtt.connect("mqtt://localhost:1883",
options = 
{    
    keepalive: 60,
    clientId : "iottest-231",
    username : "iot"          //username allowed to connect with broker
    password : "iot1234"        //password for that user
    clean: true,
});
console.log("connected flag : " +client.connected);

/*

callback to handle incoming messages
*/

client.on('message', function(topic, message, packet)
{
    console.log("received msg is : "+message.toString()) 
    console.log("Publisher Topic is :  "+topic)
    console.log("msg count : " +count);
    count = count  + 1;
})

/*

call back when subscriber get connected to broker
*/

client.on("connect", function()
{
    console.log("Connected  : " +client.connected)    
})

/*
Handling erros (callback)

*/

client.on("error", function(error)
{
    console.log("can't connect " +error)
    process.exit(1);
});

console.log("topic name for subscription : "+topic);
client.subscribe(topic);
console.log("Done!!")











