#pragma once

class TouchSensor {
  private:
    template <int len>
    struct Vals {
      int length = len;
      int idx = 0;
      int avg = 0;
      long long sum = 0;
      long long last = 0;
      int vals[len];
    };

  private:
    static const int AVG_SAMPLES = 1;

    static const int BASE_SAMPLES = 32;
    static const int BASE_PERIOD = 1000;

    static const int PRESS_THRESHOLD = 8;

    int pin = 0;

    Vals<AVG_SAMPLES> avg;
    Vals<BASE_SAMPLES> base;

    int raw = 0;
    int norm = 0;
    bool pressed = false;

    template <int len>
    void updateVals(Vals<len> &vs, int new_val) {
      vs.sum -= vs.vals[vs.idx];
      vs.vals[vs.idx] = new_val;
      vs.sum += vs.vals[vs.idx];
      vs.idx = (vs.idx + 1) % vs.length;
      vs.avg = vs.sum / vs.length;
    }

  public:
    TouchSensor(int _pin) : pin(_pin) {
      for (int i = 0; i < base.length; i++) {
        updateVals(base, 0);
        updateVals(avg, 0);
      }
    }

    void setup() {
      for (int i = 0; i < base.length; i++) {
        raw = touchRead(pin);
        updateVals(base, raw);
        updateVals(avg, raw);
      }
    }

    void loop() {
      delayMicroseconds(500);
      raw = touchRead(pin);

      updateVals(avg, raw);

      if ((millis() - base.last) > BASE_PERIOD) {
        for (int i = 0; i < base.length; i++) {
          delayMicroseconds(14);
          raw = touchRead(pin);
          updateVals(base, raw);
        }
        base.last = millis();
      }

      norm = abs(avg.avg - base.avg);
      pressed = norm > PRESS_THRESHOLD;
    }

    const bool &isPressed() const {
      return pressed;
    }
};
