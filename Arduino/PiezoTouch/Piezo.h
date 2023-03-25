class Piezo {
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

    static const int BASE_SAMPLES = 64;
    static const int BASE_PERIOD = 100;

    int pin = 0;

    Vals<AVG_SAMPLES> avg;
    Vals<BASE_SAMPLES> base;

    int raw = 0;
    int norm = 0;
    int cap = 0;

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

    const int &getCap() const {
      return cap;
    }

  public:
    Piezo(int _pin) : pin(_pin) {
      for (int i = 0; i < base.length; i++) {
        updateVals(base, 0);
      }
      for (int i = 0; i < avg.length; i++) {
        updateVals(avg, 0);
      }
    }

    void loop() {
      raw = analogRead(pin);
      delay(1);

      updateVals(avg, raw);

      if ((millis() - base.last) > BASE_PERIOD) {
        updateVals(base, raw);
        base.last = millis();
      }

      norm = abs(avg.avg - base.avg);

      if (norm > 8) {
        cap = min(1023, cap + norm);
      } else {
        cap = max(0, cap - 16);
      }
    }

    const int &getValue() const {
      return getNorm();
    }
};
