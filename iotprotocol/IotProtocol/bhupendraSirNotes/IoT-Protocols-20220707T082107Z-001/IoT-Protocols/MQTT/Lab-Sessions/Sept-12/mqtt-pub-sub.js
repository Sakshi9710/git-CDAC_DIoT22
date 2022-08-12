/*
install mqtt package on your hostmachine
npm install mqtt --save
Publish and subscribe application
Refer : https://github.com/mqttjs/MQTT.js

*/

var mqtt = require('mqtt')
var hostname = 'mqtt://localhost:5010'
var topic_name = "cdac/diot/temp"
var payload = "MQTT Test Message"
var client  = mqtt.connect(hostname)
client.on('connect', function () {
  client.subscribe(topic_name, function (err) {
    if (!err) {
      client.publish(topic_name, payload)
    }
  })
})

client.on('message', function (topic, message) {
  // message is Buffer
  console.log(message.toString())
  console.log(topic.toString())
  client.end()
})
