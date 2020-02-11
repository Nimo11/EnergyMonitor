#include <Arduino.h>

#include <Global.h>
#include <ota.h>
#include <neopixel.h>
#include <ED_wifimanager.h>
#include <api.h>
#include "ArduinoOTA.h"

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println("");
  
  pixelValue=(double)MAXVALUE/(double)NUMPIXELS;
  pixels.begin();
  pixels.setBrightness(20);

  animate();

  std::vector<const char *> menu = {"wifi", "info", "param","test", "sep", "restart"};
  wm.setMenu(menu);
  wm.setDebugOutput(true);
  //wm.setSaveParamsCallback(saveParam);
  wm.setConfigPortalBlocking(true);

  if (wm.autoConnect("Energy_Display"))
  {
    Log.print(LogObject::DebugLevels::Normal,"IP Address ");
    Log.println(LogObject::DebugLevels::Normal,WiFi.localIP().toString());
    WiFi.mode(WIFI_STA);
    WiFi.hostname("Energy_Display");
    
    setOTA();
    
    wm.startWebPortal();

    //wm.server->onNotFound(handleWebRequests);

  }
  else
  {
    Log.println(LogObject::DebugLevels::Normal,F("Config portal running!"));
  }
}

void loop() {
  wm.process();
  ArduinoOTA.handle();
      
  //set value from request
  sendAPIRequest();

  //progressive display 
  for(int i=0; i<100; i++) {
    tmpSol=calcTmpValue(tmpSol,sol);
    tmpGene=calcTmpValue(tmpGene,gene);

    for(int i=0; i<NUMPIXELS; i++) {
      double currentPixelValue=(i+1)*pixelValue;
    
      int red=calculateColor(tmpGene,currentPixelValue);
      int green=calculateColor(tmpSol,currentPixelValue);

      pixels.setPixelColor(i, pixels.Color(red, green, 0));
      pixels.show();
      
      wm.process();
      ArduinoOTA.handle();
    }
    delay(40);
  }

  Serial.println(gene-tmpGene);
  Serial.println(sol-tmpSol);
  Serial.println(tmpSol);
}

double calcTmpValue(double current,double obj)
{
  if (current==obj) return obj;

  double dec=(obj-current)/15;

  return current+dec; 
}

double calculateColor(double v,double currentPixelValue)
{
  return ((currentPixelValue-pixelValue)<v)?
    (currentPixelValue<v?
      255:
      255*((v-(currentPixelValue-pixelValue))/pixelValue)):
    0;
}

void colorize()
{  
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(255, 50, 210)); 
  }
  pixels.show();
}
