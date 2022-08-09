#include <FastLED.h>

#define NUM_LEDS 64*3
#define NUM_ROWS 8*3

#define DATA_PIN 2

CRGB leds[NUM_LEDS];

#define BRIGHTNESS 32

long long cnt = 0;

void setup() {
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  for (int i = 0; i < NUM_LEDS / 2; i++) {
    leds[i] = CRGB::Black;
    leds[NUM_LEDS - i - 1] = CRGB::Black;
  }

  for (int i = 0; i < NUM_ROWS; i++) {
    leds[i * 8] = CRGB::White;
    leds[i * 8 + 1] = CRGB::White;
    leds[i * 8 + 6] = CRGB::White;
    leds[i * 8 + 7] = CRGB::White;
  }

  int p = 4;
  int i = (cnt++ / 12) % ((NUM_ROWS) + p);

  for (int j = i - p; j <= i; j++) {
    if (j >= 0 && j < NUM_ROWS) {
      leds[j * 8] = CRGB::Black;
      leds[j * 8 + 1] = CRGB::Black;
      leds[j * 8 + 6] = CRGB::Black;
      leds[j * 8 + 7] = CRGB::Black;
    }
  }

  FastLED.show();
}
