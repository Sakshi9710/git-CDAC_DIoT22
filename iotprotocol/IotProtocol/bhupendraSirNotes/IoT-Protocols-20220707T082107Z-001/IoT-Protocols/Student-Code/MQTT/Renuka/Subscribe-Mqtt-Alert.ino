#include <WiFi.h>
#include <PubSubClient.h>
#include "ESP32_MailClient.h"

const char* ssid = "";
const char* pass = "";
const char* mqtt_server = "192.138.190.63";

#define emailSenderAccount    "emailSenderAccount@gmail.com"    
#define emailSenderPassword   "emailSenderPassword"
#define emailRecipient        "emailRecipient@gmail.com"
#define smtpServer            "smtp.gmail.com"
#define smtpServerPort        465
#define emailSubject          "ESP32 Test"

SMTPData smtpData;

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
    if (!MailClient.sendMail(smtpData)){
      Serial.println("Error sending Email, " + MailClient.smtpErrorReason());}
  smtpData.empty();
  }else if((char)payload[0] == '0') {
    digitalWrite(2, LOW);
    Serial.println("Recieved 0");
  }else {
    Serial.println("Invalid input send 0 or 1");
  }
  
}

void sendCallback(SendStatus info);

void setup() {
  pinMode(2, OUTPUT);
  Serial.begin(115200);
  wifi_setup();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  smtpData.setLogin(smtpServer, smtpServerPort, emailSenderAccount, emailSenderPassword);
  smtpData.setSender("ESP32", emailSenderAccount);
  smtpData.setPriority("High");
  smtpData.setSubject(emailSubject);
  smtpData.setMessage("Hello", false);
  smtpData.addRecipient(emailRecipient);
  smtpData.setSendCallback(sendCallback);
}
void sendCallback(SendStatus msg) {
  Serial.println(msg.info());
  if (msg.success()) {
    Serial.println("----------------");
  }
  }
void loop() {
  if(!client.connected()) {
    reconnect ();
  }
  client.loop();
  
}
