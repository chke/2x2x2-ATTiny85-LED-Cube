#include <Charlieplex.h>


byte pins[4] = {0, 4, 3, 1}; // AtTiny85 Pins
//byte pins[4] = {10, 11, 12, 13}; // Arduino Pins
int leds[] = {0, 2, 4, 11, 1, 3, 5, 10};
Charlieplex charlie(pins, sizeof(pins));
int _updateInterval = 500;
unsigned long _lastTime;
int mode = 3;
int submode = 0;
int countsub = 0;
unsigned long countMS = 0;
int updateInterval = 400;
unsigned long lastTime;
void setup() {
  _lastTime = millis();
  for (int i = 0; i < 12; i++) {
    charlie.setLed(i, false);
  }
}

void loop() {
  
  if ((millis() - lastTime) >= updateInterval) {
    clearLEDs();
    if (mode == 0) {
      // Rotate one light of the cube
      showLEDs(leds[submode]);
      submode++;
      if (submode > 7) {
        submode = 0;
        countsub++;
      }
      if (countsub > 2) {
        mode = 1;
        countsub = 0;
      }
    } else if (mode == 1) {
	  // Lighten top and bottom
      if (submode == 0) {
        showLEDs(0);
        showLEDs(2);
        showLEDs(4);
        showLEDs(11);
        submode = 1;
      } else if (submode == 1) {
        showLEDs(1);
        showLEDs(3);
        showLEDs(5);
        showLEDs(10);
        submode = 0;
      }
      countsub++;
      if (countsub > 8) {
        countsub = 0;
        mode = 2;
      }
    } else if (mode == 2) {
	  // Lighten left and right
      if (submode == 0) {
        showLEDs(4);
        showLEDs(2);
        showLEDs(3);
        showLEDs(5);
        submode = 1;
      } else if (submode == 1) {
        showLEDs(0);
        showLEDs(10);
        showLEDs(1);
        showLEDs(11);
        submode = 0;
      }
      countsub++;
      if (countsub > 8) {
        countsub = 0;
        mode = 3;
      }
    } else if (mode == 3) {
	  // Lighten front and back
      if (submode == 0) {
        showLEDs(0);
        showLEDs(2);
        showLEDs(1);
        showLEDs(3);
        submode = 1;
      } else if (submode == 1) {
        showLEDs(10);
        showLEDs(5);
        showLEDs(4);
        showLEDs(11);
        submode = 0;
      }
      countsub++;
      if (countsub > 8) {
        countsub = 0;
        mode = 4;
      }
    } else if (mode == 4) {
	  // Rotate one top and one bottom pixel
      if (submode == 0) {
        showLEDs(0);
        showLEDs(1);
      } else if (submode == 1) {
        showLEDs(2);
        showLEDs(3);
      } else if (submode == 2) {
        showLEDs(4);
        showLEDs(5);
      } else if (submode == 3) {
        showLEDs(11);
        showLEDs(10);
      }
      submode++;
      if (submode > 3) {
        submode=0;
        countsub++;
        if (countsub > 4) {
          mode = 0;
          countsub = 0;
        }
      }
    }
    lastTime += updateInterval;
  }
  
  charlie.loop();
}

void showLED(int ledNr) {
  charlie.setPwmLed(ledNr, 200);
  charlie.loop();
  delay(500);
  clearLEDs();
}

void clearLEDs() {
  for (int i = 0; i < 12; i++) {
    charlie.setLed(i, false);
  }
}

void showLEDs(int ledNr) {
  charlie.setPwmLed(ledNr, 200);
}
