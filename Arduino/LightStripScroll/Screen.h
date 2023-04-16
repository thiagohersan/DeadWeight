#pragma once

#include "Page.h"

class Screen {
  private:
    int PAGE_SIZE = sizeof(PAGE_VALUES);
    int SCREEN_SIZE = 256;
    int numOutputs = 14;
    int pixPerOut = SCREEN_SIZE / numOutputs;
    std::vector<byte> pixelValues;

    // outputs a whole page of black or white
    inline byte PAGE_VALUES_BLACK_OR_WHITE(int i) {
      return ((i / int(SCREEN_SIZE / 1.8)) % 2) * 255;
    }

    // outputs values based on pre-determined pattern
    inline byte PAGE_VALUES_PATTERN(int i) {
      return PAGE_VALUES[i];
    }

    inline byte getPageValue(int i) {
      return PAGE_VALUES_BLACK_OR_WHITE(i);
    }

  public:
    Screen(int _numOuts) {
      numOutputs = _numOuts;
      pixPerOut = SCREEN_SIZE / numOutputs;
      for (int i = 0; i < numOutputs; i++) {
        pixelValues.push_back(0);
      }
    }

    void update(int y0) {
      for (int i = 0; i < numOutputs; i++) {
        int screenTop = (i * pixPerOut + y0);

        int sum = 0;
        for (int p = 0; p < pixPerOut; p++) {
          int pixelY = (screenTop + p) % PAGE_SIZE;
          sum += getPageValue(pixelY) & 0xff;
        }
        pixelValues[i] = (sum / pixPerOut);
      }
    }

    const std::vector<byte> &values() const {
      return pixelValues;
    }
};
