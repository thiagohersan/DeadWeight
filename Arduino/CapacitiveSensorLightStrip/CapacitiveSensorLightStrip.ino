#include <FastLED.h>
#include "Phone.h"

const int SENSORS_PER_PHONE = 2;

const int IPHONE_4_DATA_PIN = 2;
const int IPHONE_4_LEDS_PER_SIDE = 14;
Phone<IPHONE_4_LEDS_PER_SIDE, SENSORS_PER_PHONE> iPhone4({10, 11});

const int IPHONE_G_DATA_PIN = 4;
const int IPHONE_G_LEDS_PER_SIDE = 16;
// Phone<IPHONE_G_LEDS_PER_SIDE, SENSORS_PER_PHONE> iPhoneG({9, 8});

const int HTC_OLD_DATA_PIN = 6;
const int HTC_OLD_LEDS_PER_SIDE = 12;
// Phone<HTC_OLD_LEDS_PER_SIDE, SENSORS_PER_PHONE> htcOld({11, 8});

void setup() {
  Serial.begin(115200);

  iPhone4.setup();
  // iPhoneG.setup();
  // htcOld.setup();

  FastLED.addLeds<WS2812, IPHONE_4_DATA_PIN, GRB>(iPhone4.leds, iPhone4.getNumLeds());
  // FastLED.addLeds<WS2812, IPHONE_G_DATA_PIN, GRB>(iPhoneG.leds, iPhoneG.getNumLeds());
  // FastLED.addLeds<WS2812, HTC_OLD_DATA_PIN, GRB>(htcOld.leds, htcOld.getNumLeds());
}

void loop() {
  iPhone4.loop();
  // iPhoneG.loop();
  // htcOld.loop();
  FastLED.show();
}
