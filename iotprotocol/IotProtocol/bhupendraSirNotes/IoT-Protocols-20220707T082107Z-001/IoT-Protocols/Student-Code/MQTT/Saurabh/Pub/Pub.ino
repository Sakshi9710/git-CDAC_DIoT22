#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid="Saurabh";
const char* password="Saurabh@95";
const char* mqtt_server="192.168.0.5";
int BUILTIN_LED=2;
WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(BUILTIN_LED,HIGH);
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  digitalWrite(BUILTIN_LED,LOW);
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void reconnect () {
  while (!client.connected() ) {
    Serial.println("Attempting to connect");
 
    String clientId = "iot";
    
    if (client.connect(clientId.c_str())) {
      Serial.println("Connected");
      client.publish("test", "Message");  
      Serial.println("PUBLISH SUCCESSFUL");
    }else {
      Serial.print("Falied, rc=");
      Serial.print(client.state());
      Serial.println("Trying again in 5 seconds");
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
