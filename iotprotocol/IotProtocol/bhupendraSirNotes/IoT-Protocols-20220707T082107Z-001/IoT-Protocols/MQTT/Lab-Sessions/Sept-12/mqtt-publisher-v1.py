#install paho-mqtt module
#pip3 install paho-mqtt
"""
Added features in v1.0

Username and password based authentication at broker

"""


import time

#import client class as mqtt
import paho.mqtt.client as mqtt
#constructor
"""
mqttc = mqtt.Client()  -- can be created like this as well
"""
broker_addr = "localhost"
port = 5010
keepalive = 60
'''
client = mqtt.Client(client_id="", clean_session=True, userdata=None, protocol="MQTTv311", transport="tcp")
'''
client = mqtt.Client(client_id="test123", clean_session=True, transport="tcp")
topic="sensor/issues"
payload = "Sensor stops sending the data"
username = "iot"
password = "iot1234"
#username and password based authentication
client.username_pw_set(username, password)

client.will_set(topic, payload, qos=1, retain=False)

#connect to Broker
client.connect(broker_addr,port,keepalive)
while True:
   payload = input("Enter the payload : ")
   topic_name = "cdac/acts/diot"
   client.publish(topic_name,payload)
   

