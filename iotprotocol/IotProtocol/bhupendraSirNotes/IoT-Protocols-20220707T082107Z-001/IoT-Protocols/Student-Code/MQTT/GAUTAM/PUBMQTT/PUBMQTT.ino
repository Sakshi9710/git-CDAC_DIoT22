#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Bhavya gupta";
const char* password = "8511175888@";
const char* mqtt_server = "172.128.0.1";

WiFiClient esp;
PubSubClient client (esp);

void wifi_setup() {
  delay(10);
  Serial.println("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    digitalWrite(2, HIGH);
    delay(500);
    digitalWrite(2, LOW);
  }
randomSeed(micros());
Serial.println("");
Serial.println("Congrats WiFi connected");
Serial.println("IP address:");
Serial.println(WiFi.localIP());
}


void reconnect () {
  while (!client.connected() ) {
    Serial.println("Pls wait We are Attempting to connect");
 
    String clientId = "ESPclient -";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {
      Serial.println("Connected");
      client.publish("test/pub", "hiiiii");  
      Serial.println("PUBLISH SUCCESSFUL");
      digitalWrite(2, HIGH);
    }else {
      Serial.print("Falied, rc=");
      Serial.print(client.state());
      Serial.println("Trying again in 5 seconds");
      delay(5000);
    }
  }
}
void setup() {
  pinMode(2, OUTPUT);
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
