"""
Added feature:

Topic based callback:

on_temp

The message are routed to new call back in case it is regsiterd with 
message_callback_add and the same wiill not be routed to
on_message call back
"""
import paho.mqtt.client as mqtt
topic_name = "cdac/diot/temp"
topic_name_1 = "cdac/diot/humi"
temp1_topic = "city/temp"
temp_topic = "sensorvalues/temperature"
humi_topic = "sensorvalues/humidity"
pressure_topic = "sensorvalues/pressure"
qos = 1
username = "iot"
password = "iot1234"
# The callback for when the client receives a CONNACK response from the server.
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))

    # Subscribing in on_connect() means that if we lose the connection and
    # reconnect then subscriptions will be renewed.
    
    client.subscribe(topic_name,qos)
    client.subscribe(topic_name_1,qos)
    client.subscribe(temp1_topic,qos)     #subscribe to on_temp callback
    client.subscribe(temp_topic , qos)
    client.subscribe(humi_topic, qos)
    client.subscribe(pressure_topic, qos)

# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    print("Subscibed to topic %s " % (msg.topic))
    print("Msg received %s" % (msg.payload.decode()))
 
"""
Topic based callback function
"""
def on_temp(client, userdata, msg):
   print("received msg from on_temp1 callback: %s " %(msg.payload.decode()))

def on_temperaturedata(client, userdata, msg):
   print("Subscibed to topic %s " % (msg.topic))
   print("received msg from on_temp callback: %s " %(msg.payload.decode()))
def on_humiditydata(client, userdata, msg):
   print("Subscibed to topic %s " % (msg.topic)) 
   print("received msg from on_humidity callback: %s " %(msg.payload.decode()))
def on_pressuredata(client, userdata, msg):
   print("Subscibed to topic %s " % (msg.topic))
   print("received msg from on_pressure callback: %s " %(msg.payload.decode()))


client = mqtt.Client()   #constructor
client.on_connect = on_connect
client.on_message = on_message

"""
Adding a topic based call back
"""
client.message_callback_add(temp1_topic, on_temp)
client.message_callback_add(temp_topic, on_temperaturedata)
client.message_callback_add(humi_topic, on_humiditydata)
client.message_callback_add(pressure_topic, on_pressuredata)
client.username_pw_set(username, password)
client.connect("localhost", 5010, 60)

# Blocking call that processes network traffic, dispatches callbacks and
# handles reconnecting.
# Other loop*() functions are available that give a threaded interface and a
# manual interface.
client.loop_forever()



