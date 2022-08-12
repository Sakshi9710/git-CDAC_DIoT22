const mqtt = require('mqtt')
const client = mqtt.connect('mqtt://localhost:1883', { 
  protocolVersion: 5,
  username : "diot",
  password : "diot",
  
});

const TOPIC = "diot";

const OPTIONS = { qos : 2};

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