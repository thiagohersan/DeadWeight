#include <FastLED.h>
#include "Phone.h"

const int SENSORS_PER_PHONE = 2;

const int HTC_G2_DATA_PIN = 2;
const int HTC_G2_LEDS_PER_SIDE = 12;
Phone<HTC_G2_LEDS_PER_SIDE, SENSORS_PER_PHONE> htcG2({10, 11});

const int IPHONE_G_DATA_PIN = 4;
const int IPHONE_G_LEDS_PER_SIDE = 16;
// Phone<IPHONE_G_LEDS_PER_SIDE, SENSORS_PER_PHONE> iPhoneG({9, 8});

void setup() {
  Serial.begin(115200);

  htcG2.setup();
  // iPhoneG.setup();

  FastLED.addLeds<WS2812, HTC_G2_DATA_PIN, GRB>(htcG2.leds, htcG2.getNumLeds());
  // FastLED.addLeds<WS2812, IPHONE_G_DATA_PIN, GRB>(iPhoneG.leds, iPhoneG.getNumLeds());
}

void loop() {
  htcG2.loop();
  // iPhoneG.loop();
  FastLED.show();
}
