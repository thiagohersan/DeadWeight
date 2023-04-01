#include "Piezo.h"

class Scroll {
  private:
    Piezo p0;
    Piezo p1;
    int v[3] = {0, 0, 0};

  public:
    Scroll(int _pin0, int _pin1): p0(_pin0), p1(_pin1) {}

    void setup() {
      p0.setup();
      p1.setup();
    }

    void loop() {
      p0.loop();
      p1.loop();

      v[0] = p0.getValue();
      v[1] = p1.getValue();
      v[2] = 512 + ((v[0] - v[1]) / 2);

      for (int i = 0; i < 3; i++) {
        int key = (0xA8 | i);

        Serial.write(0xFF & 0xA5);
        Serial.write(0xFF & key);
        Serial.write((v[i] >> 8) & 0xFF);
        Serial.write((v[i] >> 0) & 0xFF);
      }
    }
};
