#include <ArduinoJson.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <PubSubClient.h>

const char* ssid       = "SatishFTTH24";
const char* password   = "Scorpio@";
const char* mqtt_server="192.168.29.152";
char buffer[256];

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
String formattedDate;

StaticJsonDocument<200> doc;

WiFiClient espClient;
PubSubClient client(espClient);


void reconnect(){
  while (!client.connected()){
    Serial.print("Attempting MQTT connection...");
    String clientId = "iot";
    if(client.connect(clientId.c_str())){
      Serial.println("Connected");
      client.publish("iot/temp","PublishDemo");
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
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println(" CONNECTED");
  
  timeClient.begin();
  timeClient.setTimeOffset(19080);
  client.setServer(mqtt_server,1883);
  
  
}

void loop() {
  
    
   timeClient.forceUpdate();

   formattedDate = timeClient.getFormattedDate();
   if(formattedDate == NULL){
    timeClient.forceUpdate();
    formattedDate = timeClient.getFormattedDate();
   }
   
   if (!client.connected()) {
    reconnect();
  }
  client.loop();

  doc["sensor"] = "temp";
  doc["time"] = formattedDate;
  doc["value"] = random(10,50);
  
  serializeJsonPretty(doc, Serial);
  serializeJson(doc, buffer);
  client.publish("iot/temp", buffer);
 
  delay(5000);
}
