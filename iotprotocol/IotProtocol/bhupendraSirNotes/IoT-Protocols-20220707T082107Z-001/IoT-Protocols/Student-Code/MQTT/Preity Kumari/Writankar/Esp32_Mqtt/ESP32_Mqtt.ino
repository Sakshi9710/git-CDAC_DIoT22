#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "";
const char* password = "";
const char* mqtt_server = "";
#define led 2

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  //Setting up WiFi mode
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  //If WiFi not connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    digitalWrite(led,HIGH);
  }

  //Printing WiFi IP address
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    
    String clientId = "ESP32Client";
    String user = "";
    String pass = "";
    // Attempt to connect
    if (client.connect(clientId.c_str(),user.c_str(),pass.c_str())) {
      Serial.println("connected");
      digitalWrite(led,LOW);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      digitalWrite(led,HIGH);
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  pinMode(led,OUTPUT);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  delay(2000);
}
