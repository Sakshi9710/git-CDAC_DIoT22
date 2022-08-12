import requests
import json

URL = 'https://sleepy-island-07017.herokuapp.com/sensor'
data = open("app.env","r")
lines = list(data)
data.close()

line1 = lines[0].split('=')
line2 = lines[1].split('=')

API_KEY = line[1].replace('\n','')
TOKEN= line[2].replace('\n','')


body ={
          "API_KEY" : "d8Ur6UUXdr7ZdUd",
           "type" : "Kitchen",
            "tag" : "Aurdino",
            "value" : 100.2,
            "unit" : "C"  
        },


def sendRequest(body)
    body['API_KEY'] =" d8Ur6UUXdr7ZdUd"
    payload = json.dumps(body)
    auth ={ 'Content-Type' : 'application/json','Authorization':'Bearer' + "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJfaWQiOiI2Mjk4Y2RkNTg0NGFhZTAwMTdhOTBmMmUiLCJpYXQiOjE2NTQxODEzMzR9.sWQ0K8YIfOSP8b4H_TuhN7jPzG09iZrtdC94CP1GG68" }
    result = requests.post(URL,data=payload,headers=auth)
    print(result)