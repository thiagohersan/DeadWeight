#pragma once

#include <FastLED.h>
#include "Averager.h"

template<int LEDS_PER_SIDE, int NUM_SENSORS>
class Phone {
  private:
    const int BRIGHTNESS_MAX = 32;
    const int BRIGHTNESS_DELTA = 8;
    const int BRIGHTNESS_DELTA_THRESHOLD = BRIGHTNESS_DELTA;
    const int numLeds = 2 * LEDS_PER_SIDE;

    int maxSensorValue = 0;
    int cBrightness = 0;
    unsigned char cPixelValue = 0;

  public:
    CRGB leds[2 * LEDS_PER_SIDE];
    Averager sensor[NUM_SENSORS];

    Phone(const int (&_pins)[NUM_SENSORS]) {
      for (int i = 0; i < NUM_SENSORS; i++) {
        sensor[i] = Averager(_pins[i]);
      }
    }

    const int &getNumLeds() const {
      return numLeds;
    }

    void setup() {
      for (int i = 0; i < NUM_SENSORS; i++) {
        sensor[i].setup();
      }
    }

    void loop() {
      for (int i = 0; i < NUM_SENSORS; i++) {
        sensor[i].loop();
      }

      maxSensorValue = sensor[0].getValue();
      for (int i = 1; i < NUM_SENSORS; i++) {
        if (sensor[i].getValue() > maxSensorValue) {
          maxSensorValue = sensor[i].getValue();
        }
      }

      if ((maxSensorValue - cBrightness) > BRIGHTNESS_DELTA_THRESHOLD) {
        cBrightness = min(255, cBrightness + BRIGHTNESS_DELTA);
      } else {
        cBrightness = max(0, cBrightness - BRIGHTNESS_DELTA);
      }

      cPixelValue = int(BRIGHTNESS_MAX * int(cBrightness) / 255) & 0xFF;

      for (int pi = LEDS_PER_SIDE - 1; pi >= 0; pi--) {
        leds[pi] = CRGB(cPixelValue, cPixelValue, cPixelValue);
        leds[numLeds - pi - 1] = CRGB(cPixelValue, cPixelValue, cPixelValue);
      }

      for (int i = 0; i < NUM_SENSORS; i++) {
        int key = (0xA8 | i);

        Serial.write(0xFF & 0xA5);
        Serial.write(0xFF & key);
        Serial.write((sensor[i].getValue() >> 8) & 0xFF);
        Serial.write((sensor[i].getValue() >> 0) & 0xFF);
      }
    }
};
