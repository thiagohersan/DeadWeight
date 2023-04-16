#pragma once

#include "Page.h"

struct SpeedParams {
  float V_INC_MULT;
  float V_DAMP;
};

class Scroll {
  private:
    SpeedParams SLOW = { 0.6, 0.93 };
    SpeedParams FAST = { 10.0, 0.87 };
    SpeedParams mParams = SLOW;

  private:
    int PAGE_SIZE = sizeof(PAGE_VALUES);
    float A_DEC = 1.0;
    float A_INC_MIN = 12;
    float A_INC_MAX = 72;
    float V_MIN = 5.0;
    float V_INC = mParams.V_INC_MULT * A_DEC;
    float V_DAMP = mParams.V_DAMP;

  private:
    int y0 = 0;
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
        v0 += V_INC;
      } else {
        a0 = 0;
      }

      // slowing down
      if (v0 < random(V_MIN)) {
        // very slowed down
        if (a0 < A_DEC) {
          v0 = 0;
        }
        // bump a
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
