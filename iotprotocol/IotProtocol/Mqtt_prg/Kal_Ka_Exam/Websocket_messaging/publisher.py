# Python 3 : Program to use MQTT over Websockets
# Date: 14 Jun 2022
# Description: Mosquitto Broker is tested with websockets connection. Broker is running at 8080
import paho.mqtt.client as mqtt

print("/*-------------------------------------")
print("  MQTT over Websockets: Publisher client")
print("*--------------------------------------*/")

TOPIC = "diot"

# Method to check if Broker is connected
def on_connect(client, userdata, flags, rc):
 if rc ==0:
  print("connected to the Broker!")

client = mqtt.Client(transport="websockets")

# Setting the message handlers
client.on_connect = on_connect

# Request Broker for connection on Port 8080
client.connect("localhost", 8080)

try:
 while True:
  msg = input("Enter message to publish: ")
  (rc,mid) = client.publish(TOPIC, msg)
  if rc == 0:
   print("--message sent!--")
except KeyboardInterrupt:
 client.disconnect();
 client.loop_end()
