#include "TouchSensor.h"

class Scroll {
  private:
    struct TouchEvent {
      int sensor = -1;
      long long timestamp = 0;
    };

  private:
    const static int NUM_SENSORS = 5;
    const static int CLEAR_PERIOD = 500;

    TouchSensor sensor[NUM_SENSORS] = {
      TouchSensor(T4),
      TouchSensor(T5),
      TouchSensor(T6),
      TouchSensor(T7),
      TouchSensor(T8)
    };

    TouchEvent touchDown;
    TouchEvent touchLast;

  public:
    Scroll() {}

    void loop() {
      long long now = millis();

      for (int i = 0; i < NUM_SENSORS; i++) {
        sensor[i].loop();

        if (sensor[i].isPressed()) {
          touchLast.sensor = i;
          touchLast.timestamp = now;
        }
      }

      bool isStale = (now - touchLast.timestamp) > CLEAR_PERIOD;

      if (isStale) {
        touchDown.sensor = -1;
        touchLast.sensor = -1;
      }

      if ((touchLast.sensor > -1) && (touchDown.sensor < 0)) {
        touchDown.sensor = touchLast.sensor;
        touchDown.timestamp = touchLast.timestamp;
        Serial.println("touchDown: " + String(touchDown.sensor));
      }
    }

    bool isScrolling() {
      return (touchDown.sensor > -1) && (touchLast.sensor > -1) && (touchDown.sensor != touchLast.sensor);
    }

    bool scrollDown() {
      return (touchDown.sensor > -1) && (touchLast.sensor > -1) && (touchDown.sensor > touchLast.sensor);
    }

    bool scrollUp() {
      return (touchDown.sensor > -1) && (touchLast.sensor > -1) && (touchDown.sensor < touchLast.sensor);
    }
};
