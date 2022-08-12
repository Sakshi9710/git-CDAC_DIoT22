#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Airtel_7768980244";
const char* pass = "air29097";
const char* mqtt_server = "192.168.1.7";

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
    Serial.println("Pls wait ...");
 
    String clientId = "ESPclient -";
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {
      Serial.println("Connected");
      client.subscribe("test/pub");  
      Serial.println("SUBSCIRBE SUCCESSFUL");
    }else {
      Serial.print("Falied, rc=");
      Serial.print(client.state());
      Serial.println("Trying again in 5 seconds");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Payload is:");
  for (int i = 0; i < length; i++){
    Serial.print((char)payload[i]);
  }
  Serial.println();

  if ((char)payload[0] == '1'){
    digitalWrite(2, HIGH);
    Serial.println("Recived 1");
  }else if((char)payload[0] == '0') {
    digitalWrite(2, LOW);
    Serial.println("Recieved 0");
  }else {
    Serial.println("Invalid input send 0 or 1");
  }
  
}

void setup() {
  pinMode(2, OUTPUT);
  Serial.begin(115200);
  wifi_setup();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}
void loop() {
  if(!client.connected()) {
    reconnect ();
  }
  client.loop();
}
