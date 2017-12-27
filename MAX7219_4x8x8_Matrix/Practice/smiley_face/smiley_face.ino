/*
 * Practice with the MAX7219 4 8x8 Matrices with ELegoo Uno
 * @Author: Jake Lepere
 * @Date: 12/27/2017
 */

#include "LedControl.h"

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);

  int intensity = 8;
  int i;
  for(i = 0; i < 4; i ++) {
    lc.shutdown(i,false);
    lc.setIntensity(i,intensity);
    lc.clearDisplay(i);
  }

}

void loop() {

  builtin_blink(5);

  smiley_face(0);
  smiley_face(1);
  smiley_face(2);
  smiley_face(3);
  delay(1000);
  lc.clearDisplayAll();
  
}

/**
 * Blinks the build in LED
 * @param c the number of times to blink the LED
 */
void builtin_blink(int c) {
  int i;
  for (i = 0; i < c; i ++) {
    delay(50);
    digitalWrite(LED_BUILTIN,LOW);
    delay(100);
    digitalWrite(LED_BUILTIN,HIGH);
    delay(50);
  }
}

/*
 * Draws a smiley face on matrix m.
 * @param m the matrix number.
 */
void smiley_face(int m) {
  
  // eyes
  lc.setLed(m,5,5,true);
  lc.setLed(m,5,2,true);
  
  // mouth
  int i;
  for(i = 6; i > 0; i --) {
    lc.setLed(m,1,i,true); 
  }
  lc.setLed(m,2,6,true);
  lc.setLed(m,2,1,true);
  
}

