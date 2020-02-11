#include <neopixel.h>
#include <Global.h>

void animate()
{
  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(30, 144, 255));
    pixels.show();
    delay(100);
  }

  for(int i=NUMPIXELS; i>0; i--) {
    pixels.setPixelColor(i, pixels.Color(0,0,0));
    pixels.show();
    delay(100);
  }
}
