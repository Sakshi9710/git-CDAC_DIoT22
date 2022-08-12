
#include <WiFi.h>
#include <PubSubClient.h>
#include "ESP32_MailClient.h"
#include "DHT.h"
/*
 * mosquitto_pub -t coldRoom/dht11/#  -u shruti -P shruti  -h 192.168.31.62  -p 1883 -l
 * $mosquitto_pub -t <topic> -u <username> -P <password>  -h <ip address>  -p 1883 -l
 * 
 * 1
 * 0
 * 
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

//------------email settings
#define emailSenderAccount    "senderemailid"    
#define emailSenderPassword   "password"
#define emailRecipient        "receiveremailid"
#define smtpServer            "smtp.gmail.com"
#define smtpServerPort        465
#define emailSubject          "ESP32 mqtt email Test"

SMTPData smtpData;
void sendCallback(SendStatus info);
//-------------email settings end

WiFiClient espClient;
PubSubClient client(espClient);


float h,t,f;

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
          
          String clientId = "ESPClient-";
          String username = "shruti";
          String password = "shruti";
          clientId += String(random(0xffff), HEX);

          if (client.connect(clientId.c_str(), username.c_str(),password.c_str())) {
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


void sendCallback(SendStatus msg) {
      Serial.println(msg.info());
      
      if (msg.success()) {
            Serial.println("----------------");
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


void send_email_notify(){
  
      float set_temp = 36;
      float set_humidity = 80;
  
      if (h > set_humidity) {
         // digitalWrite(LED2, HIGH);//turning some de-humidifire   
          Serial.print("dehumidifier turn ON");

          smtpData.setMessage("<div style=\"color:#2f4468;\"><h1>High HUmidity Alert ...!</h1><p>- Sent from ESP32_PRN23 board</p></div>", true);
          smtpData.setSendCallback(sendCallback);         
          
          if (!MailClient.sendMail(smtpData)){
                 Serial.println("Error sending Email, " + MailClient.smtpErrorReason());
          }
      }
      
      if(t > set_temp){
          //digitalWrite(LED2, HIGH);// set some AC on  
          Serial.print("AC turn ON");
          smtpData.setMessage("High Temperature Alert ! - Sent from ESP32_PRN23 board", false);
          smtpData.setSendCallback(sendCallback);           
          
          if (!MailClient.sendMail(smtpData)){
                 Serial.println("Error sending Email, " + MailClient.smtpErrorReason());
          }          
      }
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
            //Serial.print(".");
            delay(500);
            digitalWrite(LED2,HIGH);
            delay(500);
            digitalWrite(LED2,LOW);
      }

      Serial.println();
      Serial.println("WiFi connected.");
      Serial.println();
      Serial.println("Preparing to send email");
      Serial.println();
  
      dht.begin();
      smtpData.setLogin(smtpServer, smtpServerPort, emailSenderAccount, emailSenderPassword);
      smtpData.setSender("ESP32", emailSenderAccount);  
      smtpData.setPriority("High");    
      smtpData.setSubject(emailSubject);
  
      smtpData.setMessage("<div style=\"color:#2f4468;\"><h1>Hello World ...!</h1><p>- Sent from ESP32_PRN23 board</p></div>", true);
   
      smtpData.addRecipient(emailRecipient);      
}

void read_dht11(){
      delay(2000);
      
      h = dht.readHumidity();
      t = dht.readTemperature();
      f = dht.readTemperature(true);
      
      if (isnan(h) || isnan(t) || isnan(f)) {
          Serial.println("Failed to read from DHT sensor!");
          return;
      }
      
      float hi = dht.computeHeatIndex(f, h);

      Serial.print("Humidity: "); 
      Serial.print(h);
      Serial.print(" %\t");
      Serial.print("Temperature: "); 
      Serial.print(t);
      Serial.print(" *C ");
      Serial.print(f);
      Serial.print(" *F\t");
      Serial.print("Heat index: ");
      Serial.print(hi);
      Serial.println(" *F");
}

void loop() {     

      read_dht11();
      client.publish("coldRoom/dht11/temperature", (String(t)+"T").c_str());
      client.publish("coldRoom/dht11/humidity", (String(h)+"H").c_str());
      Serial.println("connected auth based mqtt publisher");
      Serial.println("temperature: "+ String(t)+"   " +"humidity: "+ String(h));
      
      if (!client.connected()) {
          reconnect();
      }
      client.loop();
      send_email_notify();
}
