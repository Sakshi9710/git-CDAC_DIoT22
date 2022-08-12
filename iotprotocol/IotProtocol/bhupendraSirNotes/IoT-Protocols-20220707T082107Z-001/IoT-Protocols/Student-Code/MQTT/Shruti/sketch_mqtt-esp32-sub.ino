
#include <WiFi.h>
#include <PubSubClient.h>

/*
$mosquitto_pub -t <topic> -u <username> -P <password>  -h <ip address>  -p 1883 -l
1
0
1= led will turn ON
0= led will turn off
*/

#define BUILTIN_LED 2

const char* ssid = "ssid";
const char* password = "password";
const char* mqtt_server = "192.168.43.13";

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
            Serial.println("connected");
            client.subscribe("test/mqtt");
            Serial.println("connected auth based mqtt subscriber");
            digitalWrite(BUILTIN_LED, HIGH);
    } else {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
    }
    digitalWrite(BUILTIN_LED, LOW); //led bliking stop once mqtt connected succefully
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

        // Switch on the LED if an 1 was received as first character
        if ((char)payload[0] == '1') 
        {
              digitalWrite(BUILTIN_LED, HIGH);   
              Serial.print("LED turn ON");
        }
        else if((char)payload[0] == '0'){
              digitalWrite(BUILTIN_LED, LOW);  
              Serial.print("LED turn OFF");
        } else {
             Serial.print("invalide input.... please send 1 or 0...");
        }
}

void setup() {
      pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
      Serial.begin(115200);
      setup_wifi();
      client.setServer(mqtt_server, 1883);
      client.setCallback(callback); 
}

void loop() {

      if (!client.connected()) {
         reconnect();
      }
      client.loop(); 
}
