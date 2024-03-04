#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <UrlEncode.h>
#include <string.h>

#define String char*

void sendMessage(String message, String phoneNumber, String apiKey){

  // Data to send with HTTP POST
  String url_start = "http://api.callmebot.com/whatsapp.php?phone=";
  String api_key = "&apikey=";
  String text = "&text=";
  const String url_encoded_message = urlEncode(message).c_str();
  String url = strcat(url_start, phoneNumber);
  strcat(url, api_key);
  strcat(url, apiKey);
  strcat(url, text);
  strcat(url, url_encoded_message);

    //url = "http://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey + "&text=" + urlEncode(message);
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