#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "";
const char* pass = "";
const char* mqtt_server = "128.218.154.190";

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
    Serial.println("Hello Renuka.....We are Attempting to connect");
 
    String clientId = "ESPclient -";
    String username = "Renuka";
    String password = "Password";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str(), username.c_str(), password.c_str())) {
      Serial.println("Connected");
      client.publish("test/pub", "welcome to mqtt publisher...!");  
      Serial.println("AUTHENTICATION BASED PUBLISH SUCCESSFUL");
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
