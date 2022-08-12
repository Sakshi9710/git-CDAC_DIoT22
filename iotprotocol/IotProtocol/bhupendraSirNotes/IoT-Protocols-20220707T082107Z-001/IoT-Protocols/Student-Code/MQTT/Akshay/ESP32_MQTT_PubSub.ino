
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <WiFi.h>

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME  "akshaynakoriya"
#define AIO_KEY  "aio_UkFT89xPIrx0mVnGGHF78F9F0xYL"
WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

int  i;
uint8_t LEDpin =2;
boolean MQTT_connect();

boolean MQTT_connect() {  int8_t ret; if (mqtt.connected()) {    return true; }  uint8_t retries = 3;  while ((ret = mqtt.connect()) != 0) { mqtt.disconnect(); delay(2000);  retries--;if (retries == 0) { return false; }} return true;}

Adafruit_MQTT_Publish myfeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/switch");
Adafruit_MQTT_Subscribe switch1 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/Mytext");
void setup()
{
i = 0;
pinMode(LEDpin,OUTPUT);
Serial.begin(115200);

  WiFi.disconnect();
  delay(3000);
  Serial.println("START");
  WiFi.begin("akshay","8805750422");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
    Serial.print("..");

  }
  Serial.println("Connected");
  Serial.println("Your IP is");
  Serial.println((WiFi.localIP()));
  mqtt.subscribe(&switch1);
}


void loop()
{

    i = (random(100,200));
    if (MQTT_connect()) {
      if (myfeed.publish(i)) {
        Serial.println("Random Data sent");
        Serial.println(i);

      } else {
        Serial.println("Problem to Send Random Number");

      }

    } else {
      Serial.println("Problem to Connect to site");

    }
    delay(2000);

    
    if (MQTT_connect()) {
      Serial.println("Subscribe Event");
      Adafruit_MQTT_Subscribe *customswitch;
      while ((customswitch = mqtt.readSubscription(5000))) {
        if (customswitch == &switch1) {
          Serial.println("Inside Button");
          Serial.println(((char *)switch1.lastread));

          if (!strcmp((char*) switch1.lastread, "ON"))
          {
          Serial.println("Data Received : ON ");
          digitalWrite(LEDpin,HIGH);
          
          }
          else if(!strcmp((char*) switch1.lastread, "OFF"))
          {
          Serial.println("Data Received : OFF ");
          digitalWrite(LEDpin,LOW);
          
          }
        }

      }

    }

}
