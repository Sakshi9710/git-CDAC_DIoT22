#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Shinde";
const char* password = "30@nikit";
const char* mqtt_server = "192.168.0.108";
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

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(led, HIGH);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else {
    digitalWrite(led, LOW);  // Turn the LED off by making the voltage HIGH
  }

}

void reconnect(){
  while (!client.connected()){
    Serial.print("Attempting MQTT connection...");
    
    String clientId = "iot";
    if(client.connect("iot")){
      Serial.println("Connected");
      client.publish("abc","First PubSub demo");
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
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  pinMode(led,OUTPUT);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  delay(2000);

}
