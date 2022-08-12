/*-----------------------------------------------------------------------------------
 * MQTT over Websockets Pb/Sub program
 * Date: 14 Jun 2022
 * Description: MQTT Broker with websocket support running on 8080 port
 * ---------------------------------------------------------------------------------*/ 
const mqtt = require('mqtt')

// Note: ws protocol is used instead of mqtt
const host = 'ws://192.168.77.45:8080'

const options = {
  protocolVersion: 4,
  retain : true
}

const TOPIC = "diot"
const sensorValue = {
  value: 24.5,
  unit: "celsius",
  tag: "Temperature"
}

console.log('/*--------------------------------')
console.log(" MQTT over Websockets using Nodejs")
console.log("*--------------------------------*/\n")
const client = mqtt.connect(host, options)

// Event to handle if some error comes in the connection
client.on('error', function (err) {
  console.log(err)
  client.end()
})


// Event to Handle the successful connection with Broker
client.on('connect', function () {
  console.log('Broker connected')
  client.subscribe(TOPIC, { qos: 0 })
  client.publish(TOPIC, JSON.stringify(sensorValue) , { qos: 0, retain: false })
})

// Event to Handle Subscribed messages
client.on('message', function (topic, message, packet) {
  console.log('Topic: ' +topic +" || Message: "+ message.toString())
})
