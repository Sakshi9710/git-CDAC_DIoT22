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
    delay(10);
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
      client.publish("amruta","hello amruta!");
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
  setup_wifi();
  client.setServer(mqtt_server,1883);

}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

}
