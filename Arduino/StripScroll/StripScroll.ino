#include <FastLED.h>
#include "Phone.h"

const int IPHONE_DATA_PIN = 2;
Phone<14> iPhone;

const int SONY_DATA_PIN = 4;
Phone<16> sonyPhone;

void setup() {
  delay(10);
  FastLED.addLeds<WS2812, IPHONE_DATA_PIN, GRB>(iPhone.leds, iPhone.getNumLeds());
  FastLED.addLeds<WS2812, SONY_DATA_PIN, GRB>(sonyPhone.leds, sonyPhone.getNumLeds());
}

void loop() {
  iPhone.update();
  sonyPhone.update();
  FastLED.show();
}
