#include "WiFi.h"
#include <PubSubClient.h>
#include "DHT.h"
#define DHTPIN 4     
#define DHTTYPE DHT11 
float h,t;
String hum,temp;

const char* ssid="akshay";
const char* password="8805750422";
const char* mqtt_server="192.168.43.193";


DHT dht(DHTPIN,DHTTYPE);
WiFiClient espClient;
PubSubClient client(espClient);
int BUILTIN_LED=2;
const char*  temptopic="dht11/temp";
const char*  humtopic="dht11/humi";

void setup_wifi() {

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("*");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect(){
  while (!client.connected()){
    Serial.print("waiting for mqtt connection....");
    String clientId = "iot2020";
    if(client.connect(clientId.c_str())){
      Serial.println("Connected");
     
    }
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println("please try again");
      delay(5000);
    }
  }
}


void setup() {
  pinMode(BUILTIN_LED, OUTPUT); 
  Serial.begin(115200);
  dht.begin();
  setup_wifi();
  client.setServer(mqtt_server,1883);
  

}

void loop() {
   delay(2000);
   h = dht.readHumidity();
   t = dht.readTemperature();
   
   if (isnan(h) || isnan(t) ) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
   }
   
      hum=(String) h;
      temp=(String) t;
      client.publish("humtopic",hum.c_str());
      client.publish("temptopic",temp.c_str());
      

  
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

}
