#pragma once

#include <CapacitiveSensor.h>

template <int LEN>
struct Vals {
  int length = LEN;
  int idx = 0;
  int avg = 0;
  int min = 0;
  int max = 1;
  long long sum = 0;
  long long last = 0;
  int vals[LEN] = {0};
};

class Averager {
  private:
    static const int AVG_SAMPLES = 4;

    static const int CAP_SEND_PIN = 4;
    static const int CAP_SAMPLES = 8;

    int pin = 0;

    Vals<AVG_SAMPLES> avg;

    long long raw = 0;
    int byteLimited = 0;

    CapacitiveSensor mSensor;

    template <int LEN>
    void updateVals(Vals<LEN> &vs, int new_val) {
      vs.sum -= vs.vals[vs.idx];
      vs.vals[vs.idx] = new_val;
      vs.sum += vs.vals[vs.idx];
      vs.idx = (vs.idx + 1) % vs.length;
      vs.avg = vs.sum / vs.length;
      if (vs.avg < vs.min) vs.min = vs.avg;
      if (vs.avg > vs.max) vs.max = vs.avg;
    }

  public:
    Averager(int _pin=0) : pin(_pin), mSensor(CAP_SEND_PIN, _pin) {}

    void setup() {
      for (int i = 0; i < 2*avg.length; i++) {
        // raw = mSensor.capacitiveSensorRaw(CAP_SAMPLES);
        raw = mSensor.capacitiveSensor(CAP_SAMPLES);
        updateVals(avg, raw);
      }
    }

    void loop() {
      delayMicroseconds(100);
      // raw = mSensor.capacitiveSensorRaw(CAP_SAMPLES);
      raw = mSensor.capacitiveSensor(CAP_SAMPLES);

      updateVals(avg, raw);
      byteLimited = map(avg.avg, avg.min, avg.max, 0, 255);
    }

    const int &getAverage() const {
      return avg.avg;
    }

    const int &getAverageByteLimited() const {
      return byteLimited;
    }

    const int &getValue() const {
      // return getAverage();
      return getAverageByteLimited();
    }
};
