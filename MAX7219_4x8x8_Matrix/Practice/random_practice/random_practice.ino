/*
 * Practice with MAX7219 4 8x8 Matrices with Elegoo Uno
 * @Author: Jake Lepere
 * @Date: 12/25/2017
 */

#include "LedControl.h"

int NUM_MAT = 4;
int NUM_ROW = 8;
int NUM_COL = 8;
LedControl lc = LedControl(12,11,10,NUM_MAT);

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);

  int intensity = 8;
  int i;
  for (i = 0; i < NUM_MAT; i ++) {
    lc.shutdown(i,false);
    lc.setIntensity(i,intensity);
    lc.clearDisplay(i);
  }

  randomSeed(analogRead(0));

}

void loop() {
  delay (1);
  lc.setLed(random(NUM_MAT),random(NUM_ROW),random(NUM_COL),true);
  delay(2);
  lc.setLed(random(NUM_MAT),random(NUM_ROW),random(NUM_COL),false);
  delay(1);
}

