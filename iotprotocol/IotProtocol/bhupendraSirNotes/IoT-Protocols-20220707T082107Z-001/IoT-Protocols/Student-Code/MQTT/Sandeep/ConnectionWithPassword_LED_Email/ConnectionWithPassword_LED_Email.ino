#include <WiFi.h>
#include <PubSubClient.h>
#include "ESP32_MailClient.h"

const char* ssid = "";
const char* password = "";
const char* mqtt_server = "";
#define led 2

// To send Email using Gmail use port 465 (SSL) and SMTP Server smtp.gmail.com
// YOU MUST ENABLE less secure app option https://myaccount.google.com/lesssecureapps?pli=1
#define emailSenderAccount    ""    
#define emailSenderPassword   ""
#define emailRecipient        ""
#define smtpServer            "smtp.gmail.com"
#define smtpServerPort        465
#define emailSubject          "ESP32 Notification"

// The Email Sending data object contains config and data to send
SMTPData smtpData;

// Callback function to get the Email sending status
void sendCallback(SendStatus info);

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

  //Printing WiFi IP address
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
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
    digitalWrite(led, HIGH);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else if ((char)payload[0] == '0') {
    digitalWrite(led, LOW);  // Turn the LED off by making the voltage HIGH
  }
  else {
      Serial.println();
      Serial.println("Preparing to send email");
      Serial.println();
      
      // Set the SMTP Server Email host, port, account and password
      smtpData.setLogin(smtpServer, smtpServerPort, emailSenderAccount, emailSenderPassword);
    
      // For library version 1.2.0 and later which STARTTLS protocol was supported,the STARTTLS will be 
      // enabled automatically when port 587 was used, or enable it manually using setSTARTTLS function.
      //smtpData.setSTARTTLS(true);
    
      // Set the sender name and Email
      smtpData.setSender("Sandeep_ESP32", emailSenderAccount);
    
      // Set Email priority or importance High, Normal, Low or 1 to 5 (1 is highest)
      smtpData.setPriority("High");
    
      // Set the subject
      smtpData.setSubject(emailSubject);
    
      // Set the message with HTML format
      smtpData.setMessage("<div style=\"color:#2f4468;\"><h1>Warning!</h1><p>Wrong data recieved on topic esp32/led. Please Check!!</p><p>- Sent from ESP32 board</p></div>", true);
      // Set the email message in text format (raw)
      //smtpData.setMessage("Hello World! - Sent from ESP32 board", false);
    
      // Add recipients, you can add more than one recipient
      smtpData.addRecipient(emailRecipient);
      //smtpData.addRecipient("YOUR_OTHER_RECIPIENT_EMAIL_ADDRESS@EXAMPLE.com");
    
      smtpData.setSendCallback(sendCallback);
    
      //Start sending Email, can be set callback function to track the status
      if (!MailClient.sendMail(smtpData))
        Serial.println("Error sending Email, " + MailClient.smtpErrorReason());
    
      //Clear all data from Email object to free memory
      smtpData.empty();
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    
    String clientId = "ESP32Client-1";
    String user = "sandeep";
    String pass = "9890518335";
    // Attempt to connect
    if (client.connect(clientId.c_str(),user.c_str(),pass.c_str())) {
      Serial.println("connected");
      digitalWrite(led,LOW);
      //subscribing to topic esp32/topic
      client.subscribe("esp32/led");
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

void sendCallback(SendStatus msg) {
  // Print the current status
  Serial.println(msg.info());

  // Do something when complete
  if (msg.success()) {
    Serial.println("----------------");
    Serial.println("Message sent sucessfully!!");
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  pinMode(led,OUTPUT);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  delay(2000);
}
