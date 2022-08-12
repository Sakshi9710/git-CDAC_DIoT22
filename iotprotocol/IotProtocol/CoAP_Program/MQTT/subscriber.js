const mqtt = require('mqtt')
const client = mqtt.connect('mqtt://localhost:1883', { 
  username : "diot",
  password : "diot"
});

const TOPIC="diot";

client.on('connect', function(){
  
  client.subscribe(TOPIC, function (err) {
      if(!err) {
        console.log(`Successfully subscribe to ${TOPIC}`);
      }
    })
    
  })


client.on('message',function (topic,message) {0
  
  console.log(message.toString())
  client.end()
})