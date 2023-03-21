#include "TouchSensor.h"

const int NUM_SENSORS = 7;

TouchSensor sensor[] = {
  TouchSensor(T0),
  TouchSensor(T4),
  TouchSensor(T5),
  TouchSensor(T6),
  TouchSensor(T7),
  TouchSensor(T8),
  TouchSensor(T9)
};

void setup() {
  Serial.begin(115200);
  delay(100);
}

void loop() {
  long pressedCount = 0;

  for (int i = 0; i < NUM_SENSORS; i++) {
    sensor[i].loop();
  }

  for (int i = 0; i < NUM_SENSORS; i++) {
    if (sensor[i].isPressed()) {
      Serial.print(i);
      Serial.print(" ");
      pressedCount++;
    }
  }

  if (pressedCount) {
    Serial.print("\n");
  }
}
