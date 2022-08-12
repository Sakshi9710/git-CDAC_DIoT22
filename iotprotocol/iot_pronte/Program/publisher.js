const mqtt = require('mqtt')
const client = mqtt.connect('mqtt://localhost:1883');

const TOPIC = "diot";

const OPTIONS = { qos : 0, retain: true};

client.on('connect',function () {
  console.log("Broker Connected");
  client.publish(TOPIC, '{temp:24.5 C }',OPTIONS , function(err){
    if(!err) {
      console.log("Published Sucess");
    }
  }
  );
});

client.on('disconnect',()=> {
  console.log("Publisher disconnected!!!!!");
  
});
