#include "Scroll.h"

Scroll mScroll(A0, A4);

void setup() {
  Serial.begin(115200);
  mScroll.setup();
}

void loop() {
  mScroll.loop();
}
