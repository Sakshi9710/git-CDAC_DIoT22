"""
https://github.com/eclipse/paho.mqtt.python/blob/master/src/paho/mqtt/subscribe.py
Source code package:

def simple(topics, qos=0, msg_count=1, retained=True, hostname="localhost",
           port=1883, client_id="", keepalive=60, will=None, auth=None,
           tls=None, protocol=paho.MQTTv311, transport="tcp",
           clean_session=True, proxy_args=None):

"""
import paho.mqtt.subscribe as subscribe

topics = ['cdac/diot/temp','cdac/diot-room/humidity','cdac/#']   
#topics = 'cdac/test/iot'
#msg_count=10
"""
topic could be either list or string

list - miltiple topic
"""
"""
qos = 1
hostname = "localhost"
port = 5010
client_id = "iot1234"
keepalive = 60
clean_session = False   #persistant session

mqttsub = subscribe.simple(topics,qos,msg_count,hostname, port, client_id, keepalive, clean_session)
print(mqttsub)
"""

m = subscribe.simple(topics, hostname="localhost",port=5010, retained=False, msg_count=2)
#message = str(m.payload).replace('b','',1)
#message = message.replace("'",'');
for a in m:
    print(a.topic)
    print(a.payload)


#for details in mqttsub:
    #print(details.topics)
    #print(details.payload)
