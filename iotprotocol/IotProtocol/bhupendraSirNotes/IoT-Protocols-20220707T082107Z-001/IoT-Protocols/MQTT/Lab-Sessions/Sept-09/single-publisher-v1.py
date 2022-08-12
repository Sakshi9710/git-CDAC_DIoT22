"""
first step is : check python version
The code supports python version 3
pip3 install paho-mqtt (paho mqtt client)
Ref : https://github.com/eclipse/paho.mqtt.python/blob/master/examples/publish_single.py

Test this code : by ruuning mosquitto_sub in bash shell

Problem Statement:
Publish a continous messages
Take message as input : input/raw_input
topic-name: test/mqtt/message
broker : running on your hostmahine
retain : False
clientid = test123
keepalive = 60
qos = 1

"""

import paho.mqtt.publish as publish

topic = "test/mqtt/message"
hostname = "localhost"
port = 5010
qos = 1
retain = False
clientid = "test123"
keepalive = 60
while True:
	payload = input("Enter the message to be published : ")
	publish.single(topic, payload, qos, retain, hostname, port, clientid, keepalive)

