#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <UrlEncode.h>
#include "SendMessage.h"

unsigned long test_sensor(unsigned long wait_parameter, unsigned long last_time_value, bool whatsapp_flag, float moisture_in_percent, char* phone_number, char* api_key){

  unsigned long general_time = millis();
  char* test_message = "Bodenfeuchtigkeit in %: ";// + String(moisture_in_percent);
  // logic
  if(general_time >= last_time_value + wait_parameter){
    last_time_value = general_time;
    if(whatsapp_flag == true){
      sendMessage(test_message, phone_number, api_key);
    }
    else if(whatsapp_flag == false){
      Serial.println(test_message);
    }
    
  }
  return last_time_value;
  delay(100);

}