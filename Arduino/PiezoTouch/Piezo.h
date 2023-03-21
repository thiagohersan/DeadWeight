class Piezo {
  private:
    static const int BASE_SAMPLES = 64;
    static const int BASE_PERIOD = 100;

    int pin = 0;

    int base_vals[BASE_SAMPLES];
    int base_idx = 0;
    long long base_sum = 0;
    long long last_base = 0;

    int base = 0;
    int raw = 0;
    int norm = 0;

    void updateBase(int v) {
      base_sum -= base_vals[base_idx];
      base_vals[base_idx] = v;
      base_sum += base_vals[base_idx];
      base_idx = (base_idx + 1) % BASE_SAMPLES;
      base = base_sum / BASE_SAMPLES;
    }

  public:
    Piezo(int _pin) : pin(_pin) {
      for (int i = 0; i < BASE_SAMPLES; i++) {
        base_vals[i] = 0;
      }
    }

    void loop() {
      raw = analogRead(pin);
      delay(1);

      if ((millis() - last_base) > BASE_PERIOD) {
        updateBase(raw);
        last_base = millis();
      }

      norm = abs(raw - base);
    }

    const int &getValue() const {
      return norm;
    }

    const int &getRaw() const {
      return raw;
    }
};
