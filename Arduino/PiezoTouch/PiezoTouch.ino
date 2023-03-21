#include "Piezo.h"

Piezo p0(A1);
Piezo p1(A5);

void setup() {
  Serial.begin(57600);
}

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
