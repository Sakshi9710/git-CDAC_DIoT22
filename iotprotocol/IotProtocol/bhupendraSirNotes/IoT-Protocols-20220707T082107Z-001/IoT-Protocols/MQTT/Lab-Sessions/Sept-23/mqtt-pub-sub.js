const mqtt = require('mqtt')
/*
Connect with the MQTT broker/server
*/

var client  = mqtt.connect([{ host: 'localhost', port: 1883 }])
var payload = "My First MQTT Application in Node.JS environment"
const topic = "iot/mqtt"
client.on('connect', 
function () 
{
  client.subscribe(topic, 
        function (err) 
        {
            if (!err) 
            {
                  client.publish(topic, payload)
            }
            else
            {
                console.log("Failed to publish message")
            }
        })
})

/*

Callbakc for Handling incoming messages

*/

client.on('message', function (topic, message) 
{
  // message is in Buffer format
  console.log(message.toString())
  client.end()
})
