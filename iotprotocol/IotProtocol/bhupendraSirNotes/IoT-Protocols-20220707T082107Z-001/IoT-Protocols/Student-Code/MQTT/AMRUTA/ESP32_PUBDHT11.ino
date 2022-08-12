#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11   
float h, t;
String hum, temp;
const char* ssid = "amruta";
const char* password = "12345veer";
const char* mqtt_server = "192.168.43.193";
DHT dht(DHTPIN, DHTTYPE);
WiFiClient espClient;
PubSubClient client(espClient);
const char* tempTopic = "dht11/temp";
const char* humTopic = "dht11/hum";
int BUILTIN_LED=2;

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(10);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void reconnect() {
      while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32Client-";
     if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      
      hum = (String) h;
      temp = (String) t;
      client.publish("tempTopic", hum.c_str());
      client.publish("humTopic", temp.c_str());
      
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


 void setup() {
  dht.begin();
  pinMode(BUILTIN_LED, OUTPUT);   
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}



void loop() {
  delay(2000);
  h = dht.readHumidity();
  t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  hum = (String) h;
  temp = (String) t;
  client.publish(tempTopic, temp.c_str());
  client.publish(humTopic, hum.c_str());


  if (!client.connected()) {
    reconnect();
  }
  client.loop();


}
