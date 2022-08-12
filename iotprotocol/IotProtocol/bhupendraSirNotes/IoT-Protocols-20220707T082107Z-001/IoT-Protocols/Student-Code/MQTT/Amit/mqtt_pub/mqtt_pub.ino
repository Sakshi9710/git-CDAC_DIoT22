#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "amit";
const char* password = "amit@12";
const char* mqtt_server = "192.168.29.23";
WiFiClient espClient;
PubSubClient client(espClient);
void wifi_setup() {
  delay(10);
  Serial.println("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
  }
randomSeed(micros());
Serial.println("");
Serial.println("WiFi connected");
Serial.println("IP address:");
Serial.println(WiFi.localIP());
}


void reconnect () {
  while (!client.connected() ) {
    Serial.println("Connecting");
 
    String clientId = "ESPclient -";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {
      Serial.println("Connected");
      client.publish("cdac/diot", "Hello World");  
      Serial.println("PUBLISH SUCCESSFUL");
      digitalWrite(LED_BUILTIN, HIGH);
    }else {
      Serial.print("Falied, rc=");
      Serial.print(client.state());
      Serial.println("Trying again in 10 seconds");
      delay(10000);
    }
  }
}
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  wifi_setup();
  client.setServer(mqtt_server, 1883);
}
void loop() {
  if(!client.connected()) {
    reconnect ();
  }
  client.loop();
}
