#include "ESP32_MailClient.h"
const char* ssid = "amruta";
const char* password = "12345veer";


#define emailSenderAccount    "iamruta21veer@gmail.com"    
#define emailSenderPassword   "YOUR PASSWORD"
#define emailRecipient        "iamruta21veer@gmail.com"
#define smtpServer            "smtp.gmail.com"
#define smtpServerPort        465
#define emailSubject          "ESP32 Test"


SMTPData smtpData;

void sendCallback(SendStatus info);
void setup(){
  Serial.begin(115200);
  Serial.println();
  
  Serial.print("Connecting");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(10);
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
  smtpData.setMessage("<div style=\"color:#2f4468;\"><h1>Hello World!</h1><p>- Sent from ESP32 board</p></div>", true);
  smtpData.addRecipient(emailRecipient);
  smtpData.setSendCallback(sendCallback);
   if (!MailClient.sendMail(smtpData))
    Serial.println("Error sending Email, " + MailClient.smtpErrorReason());
     smtpData.empty();
}

void loop() {
  
}


void sendCallback(SendStatus msg) {
  Serial.println(msg.info());
  if (msg.success()) {
    Serial.println("******************");
  }
}
