class Piezo {
  private:
    template <int len>
    struct Vals {
      int length = len;
      int idx = 0;
      int avg = 0;
      int max = 0;
      long long sum = 0;
      long long last = 0;
      int vals[len];
    };

  private:
    static const int AVG_SAMPLES = 4;

    static const int BASE_SAMPLES = 32;
    static const int BASE_PERIOD = 100;

    static const int MAX_SAMPLES = 128;

    int pin = 0;

    Vals<AVG_SAMPLES> avg;
    Vals<BASE_SAMPLES> base;
    Vals<MAX_SAMPLES> maxVs;

    int raw = 0;
    int norm = 0;

    template <int len>
    void updateVals(Vals<len> &vs, int new_val) {
      vs.sum -= vs.vals[vs.idx];
      vs.vals[vs.idx] = new_val;
      vs.sum += vs.vals[vs.idx];
      vs.idx = (vs.idx + 1) % vs.length;
      vs.avg = vs.sum / vs.length;
    }

    const int &getNorm() const {
      return norm;
    }

    const int &getRaw() const {
      return raw;
    }

    const int &getAverage() const {
      return avg.avg;
    }

    const int &getMax() const {
      return maxVs.max;
    }

  public:
    Piezo(int _pin) : pin(_pin) {}

    void setup() {
      for (int i = 0; i < base.length; i++) {
        raw = analogRead(pin);
        updateVals(base, raw);
        updateVals(avg, raw);
      }
    }

    void loop() {
      delayMicroseconds(100);
      raw = analogRead(pin);

      updateVals(avg, raw);
      updateVals(maxVs, avg.avg);

      if ((millis() - base.last) > BASE_PERIOD) {
        updateVals(base, raw);
        base.last = millis();
      }

      norm = abs(avg.avg - base.avg);

      maxVs.max = maxVs.vals[0];
      for (int i = 1; i < maxVs.length; i++) {
        if (maxVs.vals[i] > maxVs.max) {
          maxVs.max = maxVs.vals[i];
        }
      }
    }

    const int &getValue() const {
      //      return getNorm();
      //      return getRaw();
      //      return getAverage();
      return getMax();
    }
};
