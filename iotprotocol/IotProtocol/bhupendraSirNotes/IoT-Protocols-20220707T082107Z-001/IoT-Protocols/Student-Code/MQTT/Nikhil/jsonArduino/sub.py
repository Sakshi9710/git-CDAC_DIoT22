import datetime
import time
import paho.mqtt.client as mqtt
import json
import csv

topic_data = "iot/temp"

qos = 1
def on_connect(client, userdata, flags, rc):
    print("connected with result code "+str(rc))
    client.subscribe(topic_data, qos)

def on_temperature (client, userdata, msg):
    print("subscribed topic: %s" % (msg.topic))
    print("Payload received: %s" % (msg.payload.decode()))
    employee_data = json.loads(msg.payload.decode())
    data_file = open('data_file.csv', 'a+')
    csv_writer = csv.writer(data_file) 
    csv_writer.writerow(employee_data.values()) 
    data_file.close() 

client = mqtt.Client()
while True:
    client.on_connect = on_connect
    client.message_callback_add(topic_data, on_temperature)
   # client.message_callback_add(topic_humi, on_humidity)
    client.connect("localhost", 1883, 60)
    client.loop_forever()
