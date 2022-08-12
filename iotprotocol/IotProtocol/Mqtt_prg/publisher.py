import paho.mqtt.client as mqtt
import time
print("starting publisher...")

topic = input("Enter the topic to publish:")
Qos=0
client=mqtt.Client()
def on_connect(client,userdata,flags,rc):
    time.sleep(6)
    if rc==0:
        print("connected to broker")
        client.publish(topic,"hello",Qos)

client.on_connect = on_connect(client,None,1,0)


client.connect("localhost",1883)
