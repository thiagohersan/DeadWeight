#pragma once

#include "Page.h"

class Scroll {
  private:
    int PAGE_SIZE = sizeof(PAGE_VALUES);
    float A_DEC = 1.0;
    float A_INC_MIN = 12;
    float A_INC_MAX = 72;
    float V_MIN = 4.0;
    float V_DAMP = 0.93;

  private:
    int y0 = 0;
    int height = 0;
    float v0 = 0;
    float a0 = 0;

    long long lastUpdate = 0;

  public:
    Scroll() {}

    void loop() {
      if (millis() - lastUpdate < 33) return;

      if (a0 >= A_DEC) {
        a0 -= A_DEC;
        v0 += A_DEC;
      } else {
        a0 = 0;
      }

      if (v0 < random(V_MIN)) {
        a0 += random(A_INC_MIN, A_INC_MAX);
      }

      v0 *= V_DAMP;
      y0 = int(y0 + v0) % PAGE_SIZE;

      lastUpdate = millis();
    }

    const int &getY() const {
      return y0;
    }
};
