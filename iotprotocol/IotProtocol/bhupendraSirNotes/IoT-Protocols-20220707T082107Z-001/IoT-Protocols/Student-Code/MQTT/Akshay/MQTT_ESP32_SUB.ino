#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid="akshay";
const char* password="8805750422";
const char* mqtt_server="192.168.43.193 ";

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
    digitalWrite(BUILTIN_LED, HIGH);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else if((char)payload[0] == '0') {
    digitalWrite(BUILTIN_LED, LOW);  // Turn the LED off by making the voltage HIGH
  }
  else {
    Serial.println("sorry!unavailable");
  }

}

//reconnecting loop
void reconnect(){
  while (!client.connected()){
    Serial.print("Wait for MQTT connection...");
    String clientId = "iot2020";
    if(client.connect(clientId.c_str())){
      Serial.println("Connected");
      client.publish("akshay","hello singh!");
      client.subscribe("amruta");
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
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

}
