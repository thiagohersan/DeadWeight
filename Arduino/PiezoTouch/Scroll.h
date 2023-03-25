#include "Piezo.h"

class Scroll {
  private:
    Piezo p0;
    Piezo p1;

  public:
    Scroll(int _pin0, int _pin1): p0(_pin0), p1(_pin1) {}

    void loop() {
      p0.loop();
      p1.loop();

      int v0 = p0.getValue();
      int v1 = p1.getValue();

      Serial.write(0xFF & 0xBE);
      Serial.write(0xFF & 0xEF);
      Serial.write((v0 >> 8) & 0xFF);
      Serial.write(v0 & 0xFF);

      Serial.write(0xFF & 0xBE);
      Serial.write(0xFF & 0xAD);
      Serial.write((v1 >> 8) & 0xFF);
      Serial.write(v1 & 0xFF);
    }
};
