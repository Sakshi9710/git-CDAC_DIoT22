#include "ESP32_MailClient.h"
#define LED2 2

const char* ssid = "ssid";
const char* password = "ssidpwd";

#define emailSenderAccount    "sender@gmail.com"    
#define emailSenderPassword   "senderpwd"
#define emailRecipient        "receiver@gmail.com"
#define smtpServer            "smtp.gmail.com"
#define smtpServerPort        465
#define emailSubject          "ESP32 mqtt email Test"


SMTPData smtpData;
void sendCallback(SendStatus info);

void setup(){
      Serial.begin(115200);
      Serial.println();
      
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
      smtpData.setMessage("<div style=\"color:#2f4468;\"><h1>Hello World!</h1><p>- Sent from ESP32 board by PRN_23</p></div>", true);
      // Set the email message in text format (raw)
      //smtpData.setMessage("Hello World! - Sent from ESP32 board", false);

      smtpData.addRecipient(emailRecipient);
      smtpData.setSendCallback(sendCallback);

 
      if (!MailClient.sendMail(smtpData)){
            Serial.println("Error sending Email, " + MailClient.smtpErrorReason());
      }

      smtpData.empty();
}

void loop() {
  
}

void sendCallback(SendStatus msg) {
      Serial.println(msg.info());
      
      if (msg.success()) {
            Serial.println("----------------");
      }
}
