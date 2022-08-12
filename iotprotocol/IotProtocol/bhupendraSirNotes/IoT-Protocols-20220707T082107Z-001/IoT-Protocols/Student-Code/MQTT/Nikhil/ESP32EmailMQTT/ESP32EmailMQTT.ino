#include <WiFi.h>
#include <PubSubClient.h>
#include "ESP32_MailClient.h"

SMTPData smtpData;
const char* ssid="ROGPHONE2";
const char* password="Nikhil555";
const char* mqtt_server="192.168.43.176";
int BUILTIN_LED=2;
WiFiClient espClient;
PubSubClient client(espClient);

#define emailSenderAccount    "cdaciot2020@gmail.com"    
#define emailSenderPassword   "cdac@123"
#define emailRecipient        "nikhil.shriwastav@gmail.com"
#define smtpServer            "smtp.gmail.com"
#define smtpServerPort        465
#define emailSubject          "ESP32 Test"


void setup_wifi() {

  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect(){
  while (!client.connected()){
    Serial.print("Attempting MQTT connection...");
    String clientId = "iot";
    if(client.connect(clientId.c_str())){
      Serial.println("Connected");
      client.subscribe("test");
    }
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
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
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, HIGH);   // Turn the LED on 
  } else if((char)payload[0] == '0') {
    digitalWrite(BUILTIN_LED, LOW);  // Turn the LED off
  }
  else {
    if (!MailClient.sendMail(smtpData))
    Serial.println("Error sending Email, " + MailClient.smtpErrorReason());
    smtpData.empty();
    //Serial.println("Unauthorize person trying to connect");
  }

}

void sendCallback(SendStatus info);

void setup() {
  pinMode(BUILTIN_LED, OUTPUT); 
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server,1883);
  client.setCallback(callback);
  smtpData.setLogin(smtpServer, smtpServerPort, emailSenderAccount, emailSenderPassword);
    smtpData.setSender("ESP32", emailSenderAccount);
    smtpData.setPriority("High");
    smtpData.setSubject(emailSubject);
    smtpData.setMessage("<div style=\"color:#2f4468;\"><h1>Unauthorize person trying to connect</h1><p>- Sent from ESP32 board</p></div>", true);
    smtpData.addRecipient(emailRecipient);
    //smtpData.setSendCallback(sendCallback);
    
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

}
