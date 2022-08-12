#include <WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

#define DHTTYPE DHT11   // DHT 11
uint8_t DHTPin = 4; 

// Initialize DHT sensor.
DHT dht(DHTPin, DHTTYPE);   


float Temperature;
float Humidity;

const char* ssid = "";
const char* password = "";
const char* mqtt_server = "";
#define led 2

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  //Setting up WiFi mode
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  //If WiFi not connected
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    digitalWrite(led,HIGH);
  }
  digitalWrite(led,LOW);

  //Printing WiFi IP address
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
    // Loop until we're reconnected
    while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    
    String clientId = "ESP32Client-DHT11";
    String user = "";
    String pass = "";
    // Attempt to connect
    if (client.connect(clientId.c_str(),user.c_str(),pass.c_str())) {
      Serial.println("connected");
      digitalWrite(led,LOW);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      digitalWrite(led,HIGH);
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void sensor_values() {
     Temperature = dht.readTemperature(); // Gets the values of the temperature
     Humidity = dht.readHumidity(); // Gets the values of the humidity 
}

void publish_data() {
    const char* topic_temperature = "home/climate/temperature";
    const char* topic_humidity = "home/climate/humidity";
    char tempVal[10];
    char humVal[10];
    dtostrf(Temperature, 4, 4, tempVal);
    dtostrf(Humidity, 4, 4, humVal);
    Serial.println("Temperature is "+String(tempVal));
    Serial.println("Humidity is "+String(humVal));

    client.publish(topic_temperature,tempVal);
    client.publish(topic_humidity,humVal);
    Serial.println("Data Published...");
}

void setup() {
  Serial.begin(115200);
  
  pinMode(DHTPin, INPUT);
  dht.begin();
  
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  pinMode(led,OUTPUT);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  sensor_values();
  publish_data();
  
  client.loop();
  delay(2000);
}
