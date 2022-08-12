import paho.mqtt.client as mqtt
print("starting subscriber")
def on_connect(Client,userdata,flags,rc):
    if rc == 0:
            print("connnected to broker")
            client.subscribe(topic,"hello",Qos)

topic = input("Enter the topic to subscribe : ")
Qos=0

client=mqtt.Client()

client.on_connect = on_connect

client.connect("127.0.0.1",1883)

