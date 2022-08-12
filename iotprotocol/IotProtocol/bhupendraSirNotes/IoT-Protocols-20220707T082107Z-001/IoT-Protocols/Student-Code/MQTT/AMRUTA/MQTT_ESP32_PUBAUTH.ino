#include "WiFi.h"
#include <PubSubClient.h>

const char* ssid="amruta";
const char* password="12345veer";
const char* mqtt_server="192.168.43.193";

WiFiClient espClient;
PubSubClient client(espClient);
int BUILTIN_LED=2;
void setup_wifi() {

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(BUILTIN_LED,HIGH);
    delay(10);
    Serial.print("*");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  digitalWrite(BUILTIN_LED,LOW);
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect(){
  while (!client.connected()){
    Serial.print("MQTT connection...");
    String clientId = "iot2020";
    String user = "amruta";
    String pass = "iot1234";
    if(client.connect(clientId.c_str(),user.c_str(), pass.c_str())){
      Serial.println("Connected");
      client.publish("amruta","hello!");
      
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
