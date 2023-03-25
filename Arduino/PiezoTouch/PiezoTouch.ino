#include "Scroll.h"

Scroll mScroll(A1, A5);

void setup() {
  Serial.begin(57600);
}

void loop() {
  mScroll.loop();
}
