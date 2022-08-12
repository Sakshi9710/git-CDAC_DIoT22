import requests
import json


URL = 'https://sleepy-island-07017.herokuapp.com/sensor'
data = open('app.env','r')
lines = list(data)
data.close()

line1 = lines[0].split('=')
line2 = lines[1].split('=')

API_KEY = line1[1].replace('\n',' ')
TOKEN= line2[1].replace('\n',' ')

def sendRequest(body):
        body['API_KEY']=API_KEY
        payload=json.dumps(body)
        auth={ 'Content-Type' : 'application/json','Authorization':'Bearer' + TOKEN}
        result=requests.post(URL,data=payload,headers=auth)
        print(result)


if __name__ == "__main__" :
    body ={
            "API_KEY" :" API_KEY",
            "type" : "Kitchen",
                "tag" : "Aurdino",
                "value" : 100.2,
                "unit" : "C"  
            },
    sendRequest(body)