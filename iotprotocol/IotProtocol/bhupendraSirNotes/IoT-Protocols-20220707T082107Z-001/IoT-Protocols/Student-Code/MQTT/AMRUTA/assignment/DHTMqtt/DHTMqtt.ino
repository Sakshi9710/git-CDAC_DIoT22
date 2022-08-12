#include "WiFi.h"
#include <PubSubClient.h>
#include "DHT.h"

#define DHTPIN 15
#define DHTTYPE DHT11
const char* ssid="amruta";
const char* password="12345veer";
const char* mqtt_server="192.168.43.193";
int BUILTIN_LED=2;
WiFiClient espClient;
PubSubClient client(espClient);

String nt;
String nh;
float h;
float t;
const char* topic1="dht/temp";
const char* topic2="dht/humi";

DHT dht(DHTPIN, DHTTYPE);

void setup_wifi() {

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect(){
  while (!client.connected()){
    Serial.print("Attempting MQTT connection...");
    String clientId = "iot123";
    if(client.connect(clientId.c_str())){
      Serial.println("Connected");
      
    }
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  dht.begin();
  //pinMode(BUILTIN_LED, OUTPUT); 
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server,1883);

}

void loop() {
  delay(2000);
  
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
  h = dht.readHumidity();
  t = dht.readTemperature();
  
  if (isnan(h) || isnan(t) ) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

 
  nt=(String) t;
  nh=(String) h;
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.println("");

  client.publish(topic1, nt.c_str());
  client.publish(topic2, nh.c_str());

  
  }
  
  
