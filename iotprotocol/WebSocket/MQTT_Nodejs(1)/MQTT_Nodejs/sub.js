/*-----------------------------------------------------------------------------------
 * MQTT subscriber program
 * Date: 14 Jun 2022
 * Description: Simple MQTT subscriber program to connect local Broker on Port 1883
 * ---------------------------------------------------------------------------------*/ 
const mqtt = require('mqtt');

console.log("/*---------------------------")
console.log("* MQTT v5.0 Subscriber Program.  ")
console.log("*--------------------------*/")

// Set the MQTT options in second params; Here protocolVersion is used v5.0. Try different options
const client = mqtt.connect("mqtt://localhost:1883",{
    protocolVersion: 5
});

const TOPIC = "diot";

// Event for handling connection state; Get called when client connects to Broker
client.on("connect",()=>{

        // Immediately subscribe to TOPIC
        client.subscribe(TOPIC,function(error){
            if(!error) {
                console.log(`Subscribed to ${TOPIC}`)
            } else {
                console.log(error)
            }
        })
})


// Event to handle the Subscribed TOPIC messages; Messages comes in buffer format; String conversion done
client.on("message",(top,message)=>{
    console.log(`Topic: ${top}, Message: ${message.toString()}`);
})