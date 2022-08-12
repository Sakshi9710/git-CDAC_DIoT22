
#include <WiFi.h>
#include <PubSubClient.h>

/*
 * $mosquitto_sub -t <topic> -u <username> -P <password>  -h <ip>  -p 1883 
 */
 
#define BUILTIN_LED 2

const char* ssid = "nomadic";
const char* password = "nomadic";
const char* mqtt_server = "192.168.43.57";

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
//    Serial.print(".");//turn on led2
    digitalWrite(BUILTIN_LED, HIGH); 
    delay(500);
    digitalWrite(BUILTIN_LED, LOW);   
    
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
   while (!client.connected()) {
    Serial.print("PRN_23......Attempting MQTT connection...");
 
    String clientId = "ESPClient-";
    String username = "shruti";
    String password = "shruti";
    clientId += String(random(0xffff), HEX);
   
    if (client.connect(clientId.c_str(), username.c_str(),password.c_str())) {
 //   if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("test/mqtt", "prn_23 mqtt publisher connected");
      Serial.println("connected auth based mqtt publisher");
      digitalWrite(BUILTIN_LED, HIGH); 
      // ... and resubscribe
  //    client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }

    digitalWrite(BUILTIN_LED, LOW); //led bliking stop once mqtt connected succefully
  }
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
 // client.setCallback(callback);

  
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop(); 
}
