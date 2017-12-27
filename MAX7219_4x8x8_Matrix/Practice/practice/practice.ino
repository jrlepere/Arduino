/*
 * Practice with MAX7219 4 8x8 Matrices with Elegoo Uno
 * @Author: Jake Lepere
 * @Date: 12/25/2017
 */

#include "LedControl.h"

LedControl lc = LedControl(12,11,10,4);

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);

  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);

  lc.shutdown(1,false);
  lc.setIntensity(1,8);
  lc.clearDisplay(1);

  lc.shutdown(2,false);
  lc.setIntensity(2,8);
  lc.clearDisplay(2);

  lc.shutdown(3,false);
  lc.setIntensity(3,8);
  lc.clearDisplay(3);

}

int num_mat = 4;      // Number of matrices
int num_row_mat = 8;  // Number of rows per matrix
int num_col_mat = 8;  // Number of cols per matrix
int tot_row = num_row_mat;             // Total rows
int tot_col = num_mat * num_col_mat;   // Total cols

void loop() {

  builtin_blink(5);
  
  one();
  two();
  three();

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

/**
 * First function.
 * Sets LEDs from right to left for each row bottom to top across each matrix.
 */
void one() {
  int row;  // The current row
  int col;  // The current col
  int mat;  // The current matrix
  int mat_switch; // Var to check if switching matrices
  
  for (row = 0; row < tot_row; row ++) {
    mat = num_mat - 1;
    for (col = tot_col - 1; col >= 0; col --) {
      mat_switch = col % num_col_mat;
      lc.setLed(mat,row,num_col_mat - (mat_switch + 1),true);
      if (mat_switch == 0) {
        mat -= 1;
      }
      delay(25);
    }
  }

  lc.clearDisplayAll();
  
}

/*
 * Second function.
 * Spirals around each matrix at the same time starting form the bottom right corner.
 */
void two() {

  // Left, Up Right, Down
  // 8, 2*7 + 6 = 28
  // 6, 2*5 + 4 = 20
  // 4, 2*3 + 2= 12
  // 2, 2*1 = 4
  
  int state = 0;
  int row = 0;
  int col = -1;
  int var = 8;
  int i;
  while (var > 0) {
    // LEFT
    for (i = 0; i < var; i ++) {
      col += 1;
      lc.setLedAll(row,col,true);
      delay(50);
    }
    // UP
    for (i = 0; i < (var-1); i ++) {
      row += 1;
      lc.setLedAll(row,col,true);
      delay(50);
    }
    // RIGHT
    for (i = 0; i < (var-1); i ++) {
      col -= 1;
      lc.setLedAll(row,col,true);
      delay(50);
    }
    // DOWN
    for (i = 0; i < (var-2); i ++) {
      row -= 1;
      lc.setLedAll(row,col,true);
      delay(50);
    }
    var -= 2;
  }

  lc.clearDisplayAll();
  
}

/*
 * Third function.
 * Spirals across all matrices starting from the bottom right corner.
 */
void three() {
  // Left, Up Right, Down
  // 32, 7, 31, 6
  // 30, 5, 29, 4
  // 28, 3, 27, 2
  // 26 , 1,  25, 0

  int row = 0;
  int col = -1;
  int var = 8;
  int i;
  while (var > 0) {
    // LEFT
    for (i = 0; i < (8*4-(8-var)); i ++) {
      col += 1;
      lc.setLedFull(row,col,true);
      delay(50);
    }
    // UP
    for (i = 0; i < (var-1); i ++) {
      row += 1;
      lc.setLedFull(row,col,true);
      delay(50);
    }
    // RIGHT
    for (i = 0; i < (8*4-(8-var+1)); i ++) {
      col -= 1;
      lc.setLedFull(row,col,true);
      delay(50);
    }
    // DOWN
    for (i = 0; i < (var-2); i ++) {
      row -= 1;
      lc.setLedFull(row,col,true);
      delay(50);
    }
    var -= 2;
  }

  lc.clearDisplayAll();
  
}


