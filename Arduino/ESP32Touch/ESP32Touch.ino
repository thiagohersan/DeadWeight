#include "Scroll.h"

Scroll mScroll;

void setup() {
  Serial.begin(115200);
  delay(100);
}

void loop() {
  mScroll.loop();

  if (mScroll.scrollUp()) {
    Serial.println("Scroll Up");
  } else if (mScroll.scrollDown()) {
    Serial.println("Scroll Down");
  }
}
