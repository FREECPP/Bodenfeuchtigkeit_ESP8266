#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <UrlEncode.h>
#include "SendMessage.h"
#include "SensorTest.h"


#define LEDPIN 0
#define six_hours 21600000

 //  value initialization

  float moisture_in_percent;
  //float notification_border = 10.00; 
  bool moisture_flag = false;
  int moisture_counter = 0; 
  int moisture_counter_border = 30; 
  //unsigned long general_time;
  //unsigned long wait_parameter = 3600000;
  unsigned long last_time_value = 0;
  

const char* ssid = "KitchenscalledHeike";
const char* password = "72609587735722940947";

// +international_country_code + phone number
// Portugal +351, example: +351912345678
String phoneNumber = "+4915143174933";
String apiKey = "8841819";

/*
void sendMessage(String message, String phoneNumber, String apiKey){

  // Data to send with HTTP POST
  String url = "http://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey + "&text=" + urlEncode(message);
  WiFiClient client;    
  HTTPClient http;
  http.begin(client, url);

  // Specify content-type header
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  // Send HTTP POST request
  int httpResponseCode = http.POST(url);
  if (httpResponseCode == 200){
    Serial.print("Message sent successfully");
  }
  else{
    Serial.println("Error sending the message");
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
  }

  // Free resources
  http.end();
}
*/
//  Functions
float measured_value_in_percent(float bound_dry, float bound_water){
      float interval = (bound_dry - bound_water) / 100;
      // reading analog Value
      int val_moisture = analogRead(0);
      // bringing the Analog Value into percent
      float moisture_in_percent = (bound_dry - val_moisture) / interval; 
      return moisture_in_percent;
}

void sensor_messaging_logic(float moisture_in_percent, float notification_border, int moisture_counter, bool moisture_flag){
  if(moisture_in_percent <= notification_border && moisture_flag == false){
    moisture_counter++;
    Serial.print("moisture_counter: ");
    Serial.println(moisture_counter);
    if(moisture_counter >= moisture_counter_border && moisture_flag == false){
      moisture_flag = true;
      sendMessage("Die Testpflanze muss gegossen werden",phoneNumber, apiKey);
    }
  }
  else if(moisture_in_percent > notification_border){
    moisture_flag = false;
    moisture_counter = 0; 
  }

  
  if(moisture_flag == true && moisture_counter >= moisture_counter_border){
    digitalWrite(LEDPIN, HIGH);
  }
  else{
    digitalWrite(LEDPIN, LOW);
  }

  delay(100);
}
/*
unsigned long test_sensor(unsigned long wait_parameter, unsigned long last_time_value, bool whatsapp_flag, float moisture_in_percent){

  unsigned long general_time = millis();
  String test_message = "Bodenfeuchtigkeit in %: " + String(moisture_in_percent);
  // logic
  if(general_time >= last_time_value + wait_parameter){
    last_time_value = general_time;
    if(whatsapp_flag == true){
      sendMessage(test_message);
    }
    else if(whatsapp_flag == false){
      Serial.println(test_message);
    }
    
  }
  return last_time_value;
  delay(100);

}
*/
void setup() {
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());

  // Send Message to WhatsAPP
  sendMessage("ESP8266 Initialized!", phoneNumber, apiKey);

  // Pinout 
  pinMode(LEDPIN, OUTPUT);
}
 


void loop(){
  //In sensor_test()enthalten
  //general_time = millis();

  //Just Information
  // Dry == 1024 
  // Water == 600

  moisture_in_percent = measured_value_in_percent(824.00, 552.00);


  //logic function
  //sensor_messaging_logic(moisture_in_percent, 10.00, moisture_counter,moisture_flag);

  //whole working logic
/*
  Serial.print(moisture_in_percent);
  Serial.println(" %");

  //Logik
  if(moisture_in_percent <= notification_border && moisture_flag == false){
    moisture_counter++;
    Serial.print("moisture_counter: ");
    Serial.println(moisture_counter);
    if(moisture_counter >= moisture_counter_border && moisture_flag == false){
      moisture_flag = true;
      sendMessage("Die Testpflanze muss gegossen werden");
    }
  }
  else if(moisture_in_percent > notification_border){
    moisture_flag = false;
    moisture_counter = 0; 
  }

  
  if(moisture_flag == true && moisture_counter >= moisture_counter_border){
    digitalWrite(LEDPIN, HIGH);
  }
  else{
    digitalWrite(LEDPIN, LOW);
  }

  delay(100);


  */

  
  last_time_value = test_sensor(6000, last_time_value, false, moisture_in_percent, phoneNumber, apiKey);



 /*
  // Testcode um Pflanzenverhalten zu testen
  String test_message = "Bodenfeuchtigkeit in %: " + String(moisture_in_percent);
  //sendMessage(test_message);
  //Serial.println(general_time);
  // logic
  if(general_time >= last_time_value + wait_parameter){
    last_time_value = general_time;
    sendMessage(test_message);
  }

  delay(100);
  */
}

