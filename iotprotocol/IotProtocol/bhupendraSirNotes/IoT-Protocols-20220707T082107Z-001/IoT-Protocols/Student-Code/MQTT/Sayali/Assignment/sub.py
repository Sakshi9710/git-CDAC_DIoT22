import paho.mqtt.subscribe as subscribe

topics = ['dht11/#']

#mqttsub = subscribe.simple(topics, hostname, port, client_id, keepalive, clean_session, msg_count=2)
m = subscribe.simple(topics, hostname="192.168.0.104", port=1883, msg_count=2)

for a in m:
    print(a.topic)
    print(a.payload)
    
    f = open("demofile.txt", "a")
    f.write("\n" + a.topic  + "\n")
    f.close()
    
    f = open("demofile.txt", "ab")
    f.write(a.payload)
    f.close()
