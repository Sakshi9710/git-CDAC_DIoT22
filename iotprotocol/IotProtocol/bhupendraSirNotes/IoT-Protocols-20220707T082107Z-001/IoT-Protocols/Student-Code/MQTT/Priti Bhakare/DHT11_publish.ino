//Publisher

#include "WiFi.h"
#include <PubSubClient.h>
#include "DHT.h"

#define DHTPIN 4
#define DHTTYPE DHT11

const char* ssid="priti";
const char* password="123456789";
const char* mqtt_server="192.168.43.38";

WiFiClient espClient;
PubSubClient client(espClient);

float h;
float t;

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
    Serial.print("Wait......Attempting MQTT connection...");
    String clientId = "ESPClient";
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
  String str_t = (String) t;
  String str_h = (String) h;
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.println("");

  client.publish("test/temp",str_t.c_str());
  client.publish("test/humi", str_h.c_str());
  Serial.println("Data has been PUBLISHED");
  }
  
