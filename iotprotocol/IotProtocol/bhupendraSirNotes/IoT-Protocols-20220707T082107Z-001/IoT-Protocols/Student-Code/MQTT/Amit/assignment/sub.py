import paho.mqtt.subscribe as subscribe

topics = ['dht11/#']

m = subscribe.simple(topics, hostname="192.168.29.23", port=1883, msg_count=4)

for a in m:
    print(a.topic)
    print(a.payload)
    
    f = open("dht.txt", "a")
    f.write("\n" + a.topic  + "\n")
    f.close()
    
    f = open("dht.txt", "ab")
    f.write(a.payload)
    f.close()
