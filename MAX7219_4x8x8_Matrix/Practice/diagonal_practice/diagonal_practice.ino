/*
 * Practice with the MAX7219 4 8x8 Matrices with Elegoo Uno
 * @Author: Jake Lepere
 * @Date: 12/29/2017
 */

#include "LedControl.h"
LedControl lc = LedControl(12,11,10,4);

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

  int d = 2; // delay
  int i;
  for (i = 3; i >= 0; i --) {
    diagonal(i,true,d);
  }
  for (i = 3; i >= 0; i --) {
    diagonal(i,false,d);
  }
  diagonalAll(true,d);
  diagonalAll(false,d);
  diagonalFull(true,d);
  diagonalFull(false,d);
  for (i = 3; i >= 0; i --) {
    diagonal_compete(i,true,d);
  }
  for (i = 3; i >= 0; i --) {
    diagonal_compete(i,false,d);
  }
  lc.clearDisplayAll();

}

/**
 * Sets the LEDS on/off matrix m with consequtive diagonals starting at 0,0.
 * @param m the matrix
 * @param on true to set on, false to set off
 * @param d the delay between led switching
 */
void diagonal(int m, bool on, int d) {
  // 0,0
  // 1,0 -> 0,1
  // 2,0 -> 1,1 -> 0,2
  // 3,0 -> 2,1 -> 1,2 -> 0,3
  // ...
  // 7,5 -> 6,6 -> 7,5
  // 7,6 -> 6,7
  // 7,7

  int num_rows = 8;
  int num_cols = 8;
  int i;
  int row;
  int col;
  for (i = 0; i < num_rows; i ++) {
    col = 0;
    for (row = i; row >= 0; row --) {
      lc.setLed(m,row,col,on);
      col += 1;
      delay(d);
    }
  }
  for (i = 1; i < num_cols; i ++) {
    row = 7;
    for (col = i; col < num_cols; col ++) {
      lc.setLed(m,row,col,on);
      row -= 1;
      delay(d);
    }
  }
}

/**
 * Sets the LEDS on/off all matrices with consequtive diagonals starting at 0,0.
 * @param on true to set on, false to set off
 * @param d the delay between led switching
 */
void diagonalAll(bool on, int d) {

  int num_rows = 8;
  int num_cols = 8;
  int num_mat = 4;
  int i;
  int m;
  int row;
  int col;
  for (i = 0; i < num_rows; i ++) {
    col = 0;
    for (row = i; row >= 0; row --) {
      for (m = 0; m < num_mat; m ++) {
        lc.setLed(m,row,col,on);
      }
      col += 1;
      delay(d);
    }
  }
  for (i = 1; i < num_cols; i ++) {
    row = 7;
    for (col = i; col < num_cols; col ++) {
      for (m = 0; m < num_mat; m ++) {
        lc.setLed(m,row,col,on);
      }
      row -= 1;
      delay(d);
    }
  }
}

/**
 * Sets the LEDS on/off on a full scalre matrix m size [8x32].
 * @param on true to set on, false to set off
 * @param d the delay between led switching
 */
void diagonalFull(bool on, int d) {

  int num_rows = 8;
  int num_cols = 32;
  int i;
  int row;
  int col;
  for (i = 0; i < num_rows; i ++) {
    col = 0;
    for (row = i; row >= 0; row --) {
      lc.setLedFull(row,col,on);
      col += 1;
      delay(d);
    }
  }
  for (i = 1; i < num_cols; i ++) {
    row = 7;
    for (col = i; col < min(i+8,num_cols); col ++) {
      lc.setLedFull(row,col,on);
      row -= 1;
      delay(d);
    }
  }
}

/**
 * Sets the LEDS on/off matrix m with opposite diagonals.
 * @param m the matrix
 * @param on true to set on, false to set off
 * @param d the delay between led switching
 */
void diagonal_compete(int m, bool on, int d) {

  int num_rows = 8;
  int num_cols = 8;
  int i;
  int row;
  int col;
  for (i = 0; i < num_rows; i ++) {
    col = 0;
    for (row = i; row >= 0; row --) {
      lc.setLed(m,row,col,on);
      lc.setLed(m,col,7-row,on);
      lc.setLed(m,7-col,row,on);
      lc.setLed(m,7-row,7-col,on);
      col += 1;
      delay(d);
    }
  }
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
