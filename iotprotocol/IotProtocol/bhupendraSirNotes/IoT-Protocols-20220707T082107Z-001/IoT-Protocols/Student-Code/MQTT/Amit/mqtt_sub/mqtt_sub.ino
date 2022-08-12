#include "WiFi.h"
#include <PubSubClient.h>

const char* ssid = "amit";
const char* password = "amit@12";
const char* mqtt_server = "192.168.29.23";
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
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
  client.setServer(mqtt_server,1883);
  client.setCallback(callback);
}

void reconnect(){
  while (!client.connected()){
    Serial.print("Attempting MQTT connection...");
    String clientId = "iot1234";
    if(client.connect(clientId.c_str())){
      Serial.println("Connected");
      client.subscribe("test");
    }
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  if ((char)payload[0] == '1') {
    digitalWrite(LED_BUILTIN, HIGH); 
  } else if((char)payload[0] == '0') {
    digitalWrite(LED_BUILTIN, LOW);
  }
  else {
    Serial.println("Enter 1 or 0");
  }

}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

}
