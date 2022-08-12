#include "WiFi.h"
#include <PubSubClient.h>

const char* ssid="sayali";
const char* password="sayali1234";
const char* mqtt_server="192.168.43.227";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_BUILTIN,HIGH);
    delay(10);
    Serial.print("*");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  digitalWrite(LED_BUILTIN,LOW);
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect(){
  while (!client.connected()){
    Serial.print("MQTT connection...");
    String clientId = "cdac123";
    String user = "iot";
    String pass = "iot1234";
    if(client.connect(clientId.c_str(),user.c_str(), pass.c_str())){
      Serial.println("Connected");
      client.publish("sayali","hello world!");
      
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
  pinMode(LED_BUILTIN, OUTPUT); 
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
