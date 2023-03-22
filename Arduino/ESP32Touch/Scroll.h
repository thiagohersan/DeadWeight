#include "TouchSensor.h"

class Scroll {
  private:
    const static int NUM_SENSORS = 7;
    const static int CLEAR_PERIOD = 512;
    const static int DEBOUNCE_PERIOD = 32;

    TouchSensor sensor[NUM_SENSORS] = {
      TouchSensor(T0),
      TouchSensor(T4),
      TouchSensor(T5),
      TouchSensor(T6),
      TouchSensor(T7),
      TouchSensor(T8),
      TouchSensor(T9)
    };

    int touchDown = -1;
    long long lastTouchDown = 0;

    int touchUp = -1;
    long long lastTouchUp = 0;

    int lastTouch = -1;
    long long lastLastTouch = 0;

  public:
    Scroll() {}

    void loop() {
      int pressedCount = 0;
      long long now = millis();

      for (int i = 0; i < NUM_SENSORS; i++) {
        sensor[i].loop();

        if (sensor[i].isPressed()) {
          pressedCount++;
          lastTouch = i;
          lastLastTouch = now;
        }
      }

      if ((now - lastTouchDown) > CLEAR_PERIOD &&
          (now - lastTouchUp) > CLEAR_PERIOD &&
          (now - lastLastTouch) > CLEAR_PERIOD) {
        touchDown = -1;
        touchUp = -1;
        lastTouch = -1;
      }

      bool debounced = (now - lastTouchDown) > DEBOUNCE_PERIOD &&
                       (now - lastTouchUp) > DEBOUNCE_PERIOD &&
                       (now - lastLastTouch) > DEBOUNCE_PERIOD;

      if (pressedCount > 0) {
        if (touchDown < 0) {
          touchDown = lastTouch;
          lastTouchDown = lastLastTouch;
          touchUp = -1;
          Serial.println("touchDown: " + String(touchDown));
        }
      } else {
        if ((touchDown > -1) && (touchUp < 0) && (lastTouch != touchDown) && debounced) {
          touchUp = lastTouch;
          lastTouchUp = lastLastTouch;
          Serial.println("touchUp: " + String(touchUp));
        }
      }
    }

    bool scrollDown() {
      return (touchDown > -1) && (touchUp > -1) && (touchUp < touchDown);
    }

    bool scrollUp() {
      return (touchDown > -1) && (touchUp > -1) && (touchUp > touchDown);
    }
};
