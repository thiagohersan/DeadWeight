#pragma once

#include <CapacitiveSensor.h>

template <int LEN>
struct Vals {
  int length = LEN;
  int idx = 0;
  int avg = 0;
  long long sum = 0;
  long long last = 0;
  int vals[LEN];
};

class Averager {
  private:
    static const int AVG_SAMPLES = 4;

    static const int BASE_SAMPLES = 32;
    static const int BASE_PERIOD = 125;

    static const int PRESS_THRESHOLD = 4;

    static const int CAP_SEND_PIN = 4;
    static const int CAP_SAMPLES = 8;


    int pin = 0;

    Vals<AVG_SAMPLES> avg;
    Vals<BASE_SAMPLES> base;

    long long raw = 0;
    int norm = 0;
    bool pressed = false;

    CapacitiveSensor mSensor;

    template <int LEN>
    void updateVals(Vals<LEN> &vs, int new_val) {
      vs.sum -= vs.vals[vs.idx];
      vs.vals[vs.idx] = new_val;
      vs.sum += vs.vals[vs.idx];
      vs.idx = (vs.idx + 1) % vs.length;
      vs.avg = vs.sum / vs.length;
    }

  public:
    Averager(int _pin) : pin(_pin), mSensor(CAP_SEND_PIN, _pin) {}

    void setup() {
      for (int i = 0; i < base.length; i++) {
        //        raw = mSensor.capacitiveSensorRaw(CAP_SAMPLES);
        raw = mSensor.capacitiveSensor(CAP_SAMPLES);
        updateVals(base, raw);
        updateVals(avg, raw);
      }
    }

    void loop() {
      delayMicroseconds(100);
      //      raw = mSensor.capacitiveSensorRaw(CAP_SAMPLES);
      raw = mSensor.capacitiveSensor(CAP_SAMPLES);

      updateVals(avg, raw);

      if ((millis() - base.last) > BASE_PERIOD) {
        updateVals(base, raw);
        base.last = millis();
      }

      norm = abs(avg.avg - base.avg);
      pressed = norm > PRESS_THRESHOLD;
    }

    const bool &isPressed() const {
      return pressed;
    }

    const int &getNorm() const {
      return norm;
    }

    const int &getAverage() const {
      return avg.avg;
    }

    const int &getBase() const {
      return base.avg;
    }

    const int &getValue() const {
      //      return getBase();
      return getAverage();
      //      return getNorm();
    }
};
