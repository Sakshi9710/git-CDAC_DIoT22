const mqtt = require("mqtt")

const Topic = "diot";

const client = mqtt.connect("mqtt://localhost:1883", {
    username : "diot",
    password : "diot1234"
})

client.on("connect",function() {

    console.log("Broker Connected")
    client.publish(Topic,'{temp:24.5}', function(err) {

        if(!err) {
            console.log("published sucess");
        }
    })
})

client.on("disconnect",()=>{
    console.log("Publisher disconnected!!!!!")
})