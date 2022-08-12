"""
Enabled with username and password based authentication
"""
import paho.mqtt.client as mqtt
topic_name = "cdac/diot/temp"
topic_name_1 = "cdac/diot/humi"
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
# The callback for when a PUBLISH message is received from the server.
def on_message(client, userdata, msg):
    if(msg.topic == topic_name):
        print("Subscibed to topic %s " % (msg.topic))
        print("Msg received %s" % (msg.payload.decode()))
    else:
       print("topic based filtering is applied");

client = mqtt.Client()   #constructor
client.on_connect = on_connect
client.on_message = on_message
client.username_pw_set(username, password)
client.connect("localhost", 5010, 60)

# Blocking call that processes network traffic, dispatches callbacks and
# handles reconnecting.
# Other loop*() functions are available that give a threaded interface and a
# manual interface.
client.loop_forever()



