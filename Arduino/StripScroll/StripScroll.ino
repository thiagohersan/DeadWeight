#include <FastLED.h>
#include "Screen.h"
#include "Scroll.h"

#define LEDS_PER_SIDE 14
#define NUM_LEDS (2 * LEDS_PER_SIDE)

const int DATA_PIN = 2;
const int BRIGHTNESS = 8;

CRGB leds[NUM_LEDS];
Screen mScreen(LEDS_PER_SIDE);
Scroll mScroll;

long long cnt = 0;

void setup() {
  delay(10);
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
  mScroll.loop();
  mScreen.update(mScroll.getY());
  std::vector<byte> f = mScreen.values();

  for (int i = 0; i < LEDS_PER_SIDE; i++) {
    byte pVal = (BRIGHTNESS * int(f[i]) / 255) & 0xff;
    leds[LEDS_PER_SIDE - i] = CRGB(pVal, pVal, pVal);
    leds[NUM_LEDS - (LEDS_PER_SIDE - i) - 1] = CRGB(pVal, pVal, pVal);
  }
  FastLED.show();
}
