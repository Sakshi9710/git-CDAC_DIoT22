import paho.mqtt.client as mqtt
import json
import csv

topics = "coldRoom/dht11/#"

def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    client.subscribe(topics,1) #(topics, qos)
    
def on_message(client, userdata, msg):
    print(msg.topic + " "+str(msg.payload))
    print("payload received %s " % (msg.payload.decode()))

    sensor_data = json.loads(msg.payload.decode())
    data_file = open('sensor_dht11_log.csv','a+')
    write_csv = csv.writer(data_file)
    write_csv.writerow(sensor_data.values())
    data_file.close()


    
client = mqtt.Client() #constructor

while True:
    client.on_connect = on_connect
    client.username_pw_set("shruti","shruti")
    client.message_callback_add(topics, on_message)
    client.connect("192.168.31.62", 1883, 60)
    client.loop_forever()