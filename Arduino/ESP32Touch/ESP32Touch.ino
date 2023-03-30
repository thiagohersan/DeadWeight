#include "Scroll.h"

Scroll mScroll;
int lastScroll;

void setup() {
  Serial.begin(115200);
  delay(100);
  mScroll.setup();
  lastScroll = 0;
}

void loop() {
  mScroll.loop();

  int thisScroll = mScroll.getScroll();

  if(thisScroll != lastScroll) {
    lastScroll = thisScroll;
    if (thisScroll > 0) {
      Serial.println("Scroll Up");
    } else if (thisScroll < 0) {
      Serial.println("Scroll Down");
    } else {
      Serial.println("Scroll Done");
    }
  }
}
