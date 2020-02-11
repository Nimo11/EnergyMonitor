#include <api.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "Global.h"
#include "ArduinoJson.h"

void sendAPIRequest() {
 
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status

    HTTPClient http;
    http.begin(endpoint+query); //Specify the URL
    int httpCode = http.GET();  //Make the request
 
    if (httpCode > 0) { 
        deserialize(http.getString());
      } 
    else {
      Serial.println("Error on HTTP request");
    }
 
    http.end();
  }
}

void deserialize(String json){
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, json);

  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.c_str());
    return;
  }

  gene = doc["values"][PowerProbe];
  sol = doc["values"][SolarProbe];
  
  Serial.print("General:");
  Serial.println(gene);
  Serial.print("Solaire:");
  Serial.println(sol);
}
