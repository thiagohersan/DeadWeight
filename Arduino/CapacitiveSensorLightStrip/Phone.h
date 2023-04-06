#pragma once

#include <FastLED.h>
#include "Averager.h"

template<int LEDS_PER_SIDE, int NUM_SENSORS>
class Phone {
  private:
    const int BRIGHTNESS = 32;
    const int numLeds = 2 * LEDS_PER_SIDE;

    int maxSensorValue = 0;

  public:
    CRGB leds[2 * LEDS_PER_SIDE];
    Averager sensor[NUM_SENSORS];

    Phone(const int (&_pins)[NUM_SENSORS]) {
      for (int i = 0; i < NUM_SENSORS; i++) {
        sensor[i] = Averager(_pins[i]);
      }
    }

    void setup() {
      for (int i = 0; i < NUM_SENSORS; i++) {
        sensor[i].setup();
      }
    }

    const int &getNumLeds() const {
      return numLeds;
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

      for (int pi = LEDS_PER_SIDE - 1, vi = 0; pi >= 0; pi--, vi++) {
        unsigned char pVal = int(BRIGHTNESS * maxSensorValue / 255) & 0xFF;
        leds[pi] = CRGB(pVal, pVal, pVal);
        leds[numLeds - pi - 1] = CRGB(pVal, pVal, pVal);
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
