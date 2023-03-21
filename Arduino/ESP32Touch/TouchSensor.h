#pragma once

template <int len>
struct Vals {
  int length = len;
  int idx = 0;
  int avg = 0;
  long long sum = 0;
  long long last = 0;
  int vals[len];
};

class TouchSensor {
  private:
    static const int AVG_SAMPLES = 1;
    static const int BASE_SAMPLES = 8;
    static const int BASE_PERIOD = 100;

    int pin = 0;

    Vals<BASE_SAMPLES> avg;
    Vals<AVG_SAMPLES> base;

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
      }
      for (int i = 0; i < avg.length; i++) {
        updateVals(avg, 0);
      }
    }

    void loop() {
      raw = touchRead(pin);

      updateVals(avg, raw);

      if ((millis() - base.last) > BASE_PERIOD) {
        updateVals(base, raw);
        base.last = millis();
      }

      norm = abs(avg.avg - base.avg);
      pressed = norm > 6;
    }

    const bool &isPressed() const {
      return pressed;
    }
};
