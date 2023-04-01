#include "Averager.h"

const int NUM_SENSORS = 5;

Averager sensor[NUM_SENSORS] = {
  Averager(T4),
  Averager(T5),
  Averager(T6),
  Averager(T7),
  Averager(T8)
};

int sensorValue[NUM_SENSORS];

const int PWM1_GPIO = 26;
const int PWM1_CH = 0;
const int PWM1_RES = 10;
const int PWM1_FREQ = 1;
const int PWM1_DUTY_CYCLE = 127;


void setup() {
  Serial.begin(115200);
  for (int i = 0; i < NUM_SENSORS; i++) {
    sensor[i].setup();
  }

  ledcAttachPin(PWM1_GPIO, PWM1_CH);
  ledcSetup(PWM1_CH, PWM1_FREQ, PWM1_RES);
  ledcWrite(PWM1_CH, PWM1_DUTY_CYCLE);
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
