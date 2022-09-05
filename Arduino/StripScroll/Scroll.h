#pragma once

#include "Page.h"

class Scroll {
  private:
    int PAGE_SIZE = sizeof(PAGE_VALUES);

  private:
    int y0 = 0;
    int height = 0;
    float v0 = 0;
    float a0 = 0;
    float a_inc = 6.0;
    float a_dec = 1.0;
    float v_dec = 0.93;
    float v_min = 4.0;

    long long lastUpdate = 0;

    void bump(int n) {
      a0 += n * a_inc;
    }

  public:
    Scroll() {}

    void loop() {
      if (millis() - lastUpdate < 33) return;

      if (a0 >= a_dec) {
        float ta_dec = max(a0 / 10, a_dec);
        a0 -= ta_dec;
        v0 += ta_dec;
      } else {
        a0 = 0;
      }

      if (v0 < random(v_min)) {
        bump(random(2, 12));
      }

      v0 *= v_dec;
      y0 = int(y0 + v0) % PAGE_SIZE;

      lastUpdate = millis();
    }

    const int &getY() const {
      return y0;
    }
};
