import paho.mqtt.subscribe as subscribe

topics = ['dht/#']   

m = subscribe.simple(topics, hostname="localhost",port=1883, retained=False, msg_count=2)

for a in m:
    print(a.topic)
    print(a.payload)
    f=open("demo.txt","ab")
    f.write(a.payload)
    f.close()
