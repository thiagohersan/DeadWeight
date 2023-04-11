#include <FastLED.h>
#include "Phone.h"

const int HTC_G2_DATA_PIN = 2;
Phone<14> htcG2;

const int IPHONE_G_DATA_PIN = 4;
Phone<16> iPhoneG;

const int HTC_OLD_DATA_PIN = 6;
Phone<12> htcOld;

void setup() {
  delay(10);
  FastLED.addLeds<WS2812, HTC_G2_DATA_PIN, GRB>(htcG2.leds, htcG2.getNumLeds());
  FastLED.addLeds<WS2812, IPHONE_G_DATA_PIN, GRB>(iPhoneG.leds, iPhoneG.getNumLeds());
  FastLED.addLeds<WS2812, HTC_OLD_DATA_PIN, GRB>(htcOld.leds, htcOld.getNumLeds());
}

void loop() {
  htcG2.update();
  iPhoneG.update();
  htcOld.update();
  FastLED.show();
}
