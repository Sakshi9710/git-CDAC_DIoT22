#include "WiFi.h"
#include <PubSubClient.h>

const char* ssid="ROGPHONE2";
const char* password="Nikhil555";
const char* mqtt_server="192.168.43.176";
int BUILTIN_LED=2;
WiFiClient espClient;
PubSubClient client(espClient);

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
    String clientId = "iot";
    if(client.connect(clientId.c_str())){
      Serial.println("Connected");
      client.publish("test","FirstPubSubdemo");
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
  pinMode(BUILTIN_LED, OUTPUT); 
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server,1883);

}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

}
