/*-----------------------------------------------------------------------------------
 * MQTT publisher program
 * Date: 14 Jun 2022
 * Description: Simple MQTT subscriber program to connect local Broker on Port 1883
 * ---------------------------------------------------------------------------------*/ 
const mqtt = require('mqtt');

console.log("/*---------------------------")
console.log("* MQTT v5.0 Publisher Program.")
console.log("*--------------------------*/")

const TOPIC = "diot";
let sensorValue = {temp:24.5, unit: "celsius", timestamp: new Date().now};

// Set the MQTT options in second params; Here protocolVersion is used v5.0. Try different options
const client = mqtt.connect("mqtt://192.168.77.45:1883",{
    protocolVersion: 5
});


// Event to Handle connection with Broker
client.on("connect",()=>{   
    console.log("Broker connected!");
    
    client.publish(TOPIC, JSON.stringify(sensorValue), {
            qos:0
        },(err)=>{
            if(!err){
                console.log("--msg sent--")
            }
        });
})

// Event to handle Broker disconnectino
client.on("disconnect",()=>{
    console.log("Disconnected from server")
    client.end();
})