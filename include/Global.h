#ifndef GLOBAL_h
#define GLOBAL_h

#include <Adafruit_NeoPixel.h>
#include <ED_wifimanager.h>
#include <Wifimanager.h>
#include <LogObject.h>

#define PIN        2
#define NUMPIXELS 16
#define MAXVALUE 50
#define PowerProbe 0
#define SolarProbe 1

extern Adafruit_NeoPixel pixels;


const String endpoint = "http://192.168.0.12";
const String query = "/probesvalues";
double gene=0;
double tmpGene=50;
double sol=0;
double tmpSol=50;
double pixelValue;
WiFiManager wm;

LogObject Log;

#endif