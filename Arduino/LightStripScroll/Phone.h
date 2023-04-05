#pragma once

#include <FastLED.h>

#include "Screen.h"
#include "Scroll.h"

template<int ledsPerSide>
class Phone {
  private:
    const int BRIGHTNESS = 8;
    const int numLeds = 2 * ledsPerSide;

    Screen mScreen;
    Scroll mScroll;

  public:
    CRGB leds[2 * ledsPerSide];

    Phone() : mScreen(ledsPerSide) {}

    const int getNumLeds() const {
      return numLeds;
    }

    void update() {
      mScroll.update();
      mScreen.update(mScroll.getY());
      std::vector<byte> vs = mScreen.values();

      for (int pi = ledsPerSide - 1, vi = 0; pi >= 0; pi--, vi++) {
        byte pVal = (BRIGHTNESS * int(vs[vi]) / 255) & 0xff;
        leds[pi] = CRGB(pVal, pVal, pVal);
        leds[numLeds - pi - 1] = CRGB(pVal, pVal, pVal);
      }
    }
};
