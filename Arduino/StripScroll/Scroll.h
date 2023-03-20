#pragma once

#include "Page.h"

class Scroll {
  private:
    int PAGE_SIZE = sizeof(PAGE_VALUES);
    float A_DEC = 1.0;
    float A_INC_MIN = 12;
    float A_INC_MAX = 72;
    float V_MIN = 5.0;
    float V_DAMP = 0.93;

  private:
    int y0 = 0;
    float y_dir = -1.0;
    int height = 0;
    float v0 = 0;
    float a0 = 0;

    long long lastUpdate = 0;

  public:
    Scroll() {}

    void update() {
      if (millis() - lastUpdate < 33) return;

      if (a0 >= A_DEC) {
        a0 -= A_DEC;
        v0 += A_DEC;
      } else {
        a0 = 0;
      }

      // slowing down
      if (v0 < random(V_MIN)) {
        // very slowed down
        if (a0 < A_DEC) {
          // scrolling up with p() = 0.5 or scrolling down with p() = 0.125
          if ((y_dir < 0 && !random(0, 2)) || (y_dir > 0 && !random(0, 8))) {
            v0 = 0;
            y_dir *= -1.0;
          }
        }
        // bump a
        a0 += random(A_INC_MIN, A_INC_MAX);
      }

      v0 *= V_DAMP;
      y0 = int(PAGE_SIZE + y0 + int(y_dir * v0)) % PAGE_SIZE;

      lastUpdate = millis();
    }

    const int &getY() const {
      return y0;
    }
};
