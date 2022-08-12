
#include <WiFi.h>
#include <PubSubClient.h>
#include "ESP32_MailClient.h"
/*
 * mosquitto_pub -t test/mqtt -u shruti -P shruti  -h 192.168.31.62  -p 1883 -l
 * $mosquitto_pub -t <topic> -u <username> -P <password>  -h <ip address>  -p 1883 -l
 * 
 * 1
 * 0
 * 
 * 1= led will turn ON
 * 0= led will turn off
*/

#define LED2 2

const char* ssid = "ssid";
const char* password = "ssid";
const char* mqtt_server = "192.168.31.62";

//------------email settings
#define emailSenderAccount    "sender@gmail.com"    
#define emailSenderPassword   "senderpwd"
#define emailRecipient        "receiver@gmail.com"
#define smtpServer            "smtp.gmail.com"
#define smtpServerPort        465
#define emailSubject          "ESP32 mqtt email Test"

SMTPData smtpData;
void sendCallback(SendStatus info);
//-------------email settings end

WiFiClient espClient;
PubSubClient client(espClient);

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
                client.subscribe("test/mqtt");
                Serial.println("connected auth based mqtt subscriber");
                digitalWrite(LED2, HIGH); 
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

  
      if ((char)payload[0] == '1') {
          digitalWrite(LED2, HIGH);   
          Serial.print("LED turn ON");

          smtpData.setSendCallback(sendCallback);
          
          
          if (!MailClient.sendMail(smtpData)){
                 Serial.println("Error sending Email, " + MailClient.smtpErrorReason());
          }
          
        //  smtpData.empty();//comment out else when u request alert 2nd time it will show error
      }
      else if((char)payload[0] == '0'){
          digitalWrite(LED2, LOW);  
          Serial.print("LED turn OFF");
      } else {
          Serial.print("invalide input.... please send 1 or 0...");
      }
}

void setup(){
      Serial.begin(115200);
      Serial.println();
      
      pinMode(LED2, OUTPUT);  
      setup_wifi();
      
      client.setServer(mqtt_server, 1883);
      client.setCallback(callback);  
      
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
  
  
      smtpData.setLogin(smtpServer, smtpServerPort, emailSenderAccount, emailSenderPassword);
      smtpData.setSender("ESP32", emailSenderAccount);  
      smtpData.setPriority("High");    
      smtpData.setSubject(emailSubject);

      // Set the message with HTML format
      smtpData.setMessage("<div style=\"color:#2f4468;\"><h1>Pump Motor ON Alert ...!</h1><p>- Sent from ESP32 board</p></div>", true);
      // Set the email message in text format (raw)
      //smtpData.setMessage("Hello World! - Sent from ESP32 board", false);

      smtpData.addRecipient(emailRecipient);
      
}



void loop() {
      if (!client.connected()) {
          reconnect();
      }
      client.loop(); 
}
