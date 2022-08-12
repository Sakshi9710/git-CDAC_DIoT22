import paho.mqtt.client as mqtt

topic_name = "cdac/acts/diot"
oneMin_topic = "os/loadavg/1"
fiveMin_topic = "os/loadavg/5"
fifteenMin_topic = "os/loadavg/15"
qos = 1
username = "diot"
password = "diot1234"

def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    
    client.subscribe(topic_name,qos)
    client.subscribe(oneMin_topic , qos)
    client.subscribe(fiveMin_topic, qos)
    client.subscribe(fifteenMin_topic, qos)

def on_message(client, userdata, msg):
    print("Subscibed to topic %s " % (msg.topic))
    print("Msg received %s" % (msg.payload.decode()))
 

def on_temp(client, userdata, msg):
   print("received msg from on_temp1 callback: %s " %(msg.payload.decode()))

def on_oneMinCpudata(client, userdata, msg):
   print("Subscibed to topic %s " % (msg.topic))
   print("received msg from on_temp callback: %s " %(msg.payload.decode()))
def on_fiveMinCpudata(client, userdata, msg):
   print("Subscibed to topic %s " % (msg.topic)) 
   print("received msg from on_humidity callback: %s " %(msg.payload.decode()))
def on_fifteenMinCpudata(client, userdata, msg):
   print("Subscibed to topic %s " % (msg.topic))
   print("received msg from on_pressure callback: %s " %(msg.payload.decode()))


client = mqtt.Client()   
client.on_connect = on_connect
client.on_message = on_message

client.message_callback_add(oneMin_topic, on_oneMinCpudata)
client.message_callback_add(fiveMin_topic, on_fiveMinCpudata)
client.message_callback_add(fifteenMin_topic, on_fifteenMinCpudata)
client.username_pw_set(username, password)
client.connect("localhost", 1883, 60)

client.loop_forever()


