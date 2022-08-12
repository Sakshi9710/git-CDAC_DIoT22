# Python 3 : Program to use MQTT over Websockets
# Date: 14 Jun 2022
# Description: Mosquitto Broker is tested with websockets connection. Broker is running at 8080
import paho.mqtt.client as mqtt

print("/*-------------------------------------")
print("  MQTT over Websockets: Subscriber client")
print("*--------------------------------------*/")

TOPIC = "diot"

# Method for handling Subscriber messages
def on_message(client, userdata,message):
 print("Topic: " + message.topic +" || Message: "+ message.payload.decode('utf-8'))

# Method to check if Broker is connected
def on_connect(client, userdata, flags, rc):
 if rc ==0:
  print("connected to the Broker!")
  client.subscribe(TOPIC)
  client.publish(TOPIC,"hare ram hare krishna...")

client = mqtt.Client(transport="websockets")

# Setting the message handlers
client.on_connect = on_connect
client.on_message = on_message

# Request Broker for connection on Port 8080
client.connect("192.168.77.45", 8080)

# To maintain the connection loop
client.loop_forever()
