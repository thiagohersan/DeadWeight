#pragma once

#include "Page.h"

class Screen {
  private:
    int PAGE_SIZE = sizeof(PAGE_VALUES);
    int SCREEN_SIZE = 256;
    int numOutputs = 14;
    int pixPerOut = SCREEN_SIZE / numOutputs;
    std::vector<byte> pixelValues;

    inline byte PAGE_VALUES_EQUAL_BLACK_WHITE(int i) {
      return ((i / 128) % 2) * 255;
    }

    inline byte PAGE_VALUES_NOISE(int i) {
      return PAGE_VALUES[i];
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
          sum += PAGE_VALUES_EQUAL_BLACK_WHITE(pixelY) & 0xff;
        }
        pixelValues[i] = (sum / pixPerOut);
      }
    }

    const std::vector<byte> &values() const {
      return pixelValues;
    }
};
