#include <ArduinoJson.h>
#include <WiFiUdp.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"
#include <NTPClient.h>


/*
 * mosquitto_sub -t coldRoom/dht11/#  -u shruti -P shruti  -h 192.168.31.62  -p 1883 
 * $mosquitto_sub -t <topic> -u <username> -P <password>  -h <ip address>  -p 1883 
 * 1= led will turn ON
 * 0= led will turn off
*/

#define LED2 2
#define DHTPIN 4 


#define DHTTYPE DHT11   // DHT 11 
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "ssid";
const char* password = "password";
const char* mqtt_server = "192.168.31.62";
WiFiClient espClient;
PubSubClient client(espClient);


// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

String formattedDate;

char  mqttRequestData[256];

float h,t;

void setup_wifi() {

      delay(10);
      Serial.println();
      Serial.print("Connecting to ");
      Serial.println(ssid);
      
      WiFi.mode(WIFI_STA);
      WiFi.begin(ssid, password);

      while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            digitalWrite(LED2, HIGH); 
            delay(500);
            digitalWrite(LED2, LOW);   
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
          
          String clientId = "ESPClient-23";
          String username = "shruti";
          String password = "shruti";
          clientId += String(random(0xffff), HEX);

          if (client.connect(clientId.c_str(), username.c_str(),password.c_str())) 
          {
                Serial.println("connected");               
          } else {
                Serial.print("failed, rc=");
                Serial.print(client.state());
                Serial.println(" try again in 5 seconds");
                delay(5000);
          }

          digitalWrite(LED2, LOW); //led bliking stop once mqtt connected succefully
      }
}



void callback(char* topic, byte* payload, unsigned int length) {
      
      Serial.print("Message arrived [");
      Serial.print(topic);
      Serial.print("] ");
      
      for (int i = 0; i < length; i++) {
          Serial.print((char)payload[i]);
      }
      Serial.println();

}

void setup(){
      Serial.begin(115200);
      Serial.println();
      
      pinMode(LED2, OUTPUT);  
      setup_wifi();
      
      client.setServer(mqtt_server, 1883);
      
      Serial.print("Connecting");
    
      WiFi.begin(ssid, password);
            while (WiFi.status() != WL_CONNECTED) {
            delay(500);
            digitalWrite(LED2,HIGH);
            delay(500);
            digitalWrite(LED2,LOW);
      }

      Serial.println();
      Serial.println("WiFi connected.");
      Serial.println();


      // Initialize a NTPClient to get time
      timeClient.begin();
      // Set offset time in seconds to adjust for your timezone, for example:
      // GMT +1 = 3600
      // GMT +8 = 28800
      // GMT -1 = -3600
      // GMT 0 = 0
      timeClient.setTimeOffset(3600);


  
      dht.begin();
}

void read_dht11(){
      delay(2000);
      
      h = dht.readHumidity();
      t = dht.readTemperature();
      
      if (isnan(h) || isnan(t)) {
          Serial.println("Failed to read from DHT sensor!");
          return;
      }

      Serial.print("Humidity: "); 
      Serial.print(h);
      Serial.print(" %\t");
      Serial.print("Temperature: "); 
      Serial.print(t);
      Serial.print(" *C ");
}

void dateStamp_update(){
  
    timeClient.forceUpdate();
    formattedDate=timeClient.getFormattedTime();
  
}
 
void loop() {     

      read_dht11();
      dateStamp_update();

      //****converting object to json

      DynamicJsonDocument doc(2048);
      doc["sensor"] = "dht11";
      doc["time"]= formattedDate;
      doc["Temperature"]= t;
      doc["Humidity"]=h;

      serializeJson(doc,mqttRequestData);
      serializeJsonPretty(doc, Serial);

      client.publish("coldRoom/dht11/temperature",mqttRequestData);
      client.publish("coldRoom/dht11/humidity",mqttRequestData);

      
      if (!client.connected()) {
          reconnect();
      }
      client.loop();
}
