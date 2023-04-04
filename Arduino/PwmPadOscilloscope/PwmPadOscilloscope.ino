#include "Averager.h"

const int NUM_SENSORS = 4;

Averager sensor[NUM_SENSORS] = {
  Averager(A0),
  Averager(A1),
  Averager(A2),
  Averager(A3)
};

int sensorValue[NUM_SENSORS];

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < NUM_SENSORS; i++) {
    sensor[i].setup();
  }
  analogWrite(3, 127);
}

void loop() {
  for (int i = 0; i < NUM_SENSORS; i++) {
    sensor[i].loop();
  }

  for (int i = 0; i < NUM_SENSORS; i++) {
    sensorValue[i] = sensor[i].getValue();
  }

  for (int i = 0; i < NUM_SENSORS; i++) {
    int key = (0xA8 | i);

    Serial.write(0xFF & 0xA5);
    Serial.write(0xFF & key);
    Serial.write((sensorValue[i] >> 8) & 0xFF);
    Serial.write((sensorValue[i] >> 0) & 0xFF);
  }
}
