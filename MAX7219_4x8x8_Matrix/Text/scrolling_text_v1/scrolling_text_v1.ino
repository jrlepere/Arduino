/*
 * Scrolling text on MAX7219 4 8x8 Matrices with Elegoo Uno
 * @Author: Jake Lepere
 * @Date: 12/25/2017
 */

#include "LedControl.h"

int NUM_MAT = 4;

LedControl lc = LedControl(12,11,10,NUM_MAT);

int blank[] = {0};

int A[] = {5,
           0,0,0,0,0,
           1,1,1,1,1,
           1,0,0,0,1,
           1,0,0,0,1,
           1,1,1,1,1,
           1,0,0,0,1,
           1,0,0,0,1,
           1,0,0,0,1};

int C[] = {5,
           0,0,0,0,0,
           1,1,1,1,1,
           1,0,0,0,0,
           1,0,0,0,0,
           1,0,0,0,0,
           1,0,0,0,0,
           1,0,0,0,0,
           1,1,1,1,1};

int E[] = {5,
           0,0,0,0,0,
           1,1,1,1,1,
           1,0,0,0,0,
           1,0,0,0,0,
           1,1,1,1,1,
           1,0,0,0,0,
           1,0,0,0,0,
           1,1,1,1,1,};

int H[] = {5,
           0,0,0,0,0,
           1,0,0,0,1,
           1,0,0,0,1,
           1,0,0,0,1,
           1,1,1,1,1,
           1,0,0,0,1,
           1,0,0,0,1,
           1,0,0,0,1,};

int I[] = {5,
           0,0,0,0,0,
           1,1,1,1,1,
           0,0,1,0,0,
           0,0,1,0,0,
           0,0,1,0,0,
           0,0,1,0,0,
           0,0,1,0,0,
           1,1,1,1,1,};

int K[] = {5,
           0,0,0,0,0,
           1,0,0,0,1,
           1,0,0,1,0,
           1,0,1,0,0,
           1,1,0,0,0,
           1,0,1,0,0,
           1,0,0,1,0,
           1,0,0,0,1};

int L[] = {5,
           0,0,0,0,0,
           1,0,0,0,0,
           1,0,0,0,0,
           1,0,0,0,0,
           1,0,0,0,0,
           1,0,0,0,0,
           1,0,0,0,0,
           1,1,1,1,1};

int N[] = {5,
           0,0,0,0,0,
           1,0,0,0,1,
           1,1,0,0,1,
           1,0,1,0,1,
           1,0,1,0,1,
           1,0,0,1,1,
           1,0,0,0,1,
           1,0,0,0,1};

int R[] = {5,
           0,0,0,0,0,
           1,1,1,1,1,
           1,0,0,0,1,
           1,0,0,0,1,
           1,1,1,1,1,
           1,0,1,0,0,
           1,0,0,1,0,
           1,0,0,0,1,};

int U[] = {5,
           0,0,0,0,0,
           1,0,0,0,1,
           1,0,0,0,1,
           1,0,0,0,1,
           1,0,0,0,1,
           1,0,0,0,1,
           1,0,0,0,1,
           1,1,1,1,1,};

int Y[] = {5,
           0,0,0,0,0,
           1,0,0,0,1,
           0,1,0,1,0,
           0,0,1,0,0,
           0,0,1,0,0,
           0,0,1,0,0,
           0,0,1,0,0,
           0,0,1,0,0,};

int exp_mark[] = {1,
                  0,
                  1,
                  1,
                  1,
                  1,
                  1,
                  0,
                  1};

int three_exp_mark[] = {5,
                        0,0,0,0,0,
                        1,0,1,0,1,
                        1,0,1,0,1,
                        1,0,1,0,1,
                        1,0,1,0,1,
                        1,0,1,0,1,
                        0,0,0,0,0,
                        1,0,1,0,1};


void setup()
{
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

void loop()
{
  
  // digitalWrite(LED_BUILTIN, HIGH)
  // lc.setLed(num,col,row,true)

  digitalWrite(LED_BUILTIN, HIGH);

  int name_size = 12;
  int* name[] = {blank,blank,blank,H,E,Y,blank,A,L,L,I,exp_mark};

  draw_word(name,name_size);
  
}

/**
 * Draws a word as scrolling text on the matrices.
 * @param w the word.
 * @param s the size of the word.
 */
void draw_word(int** w, int s) {

  // var definitions
  int i;
  int j;
  int k;
  int m;

  // draw characters
  for (i = 0; i < s; i ++) {
    for (j = 0; j < 4; j ++) {
      m = i + j;
      if (m >= s) {
        draw_char(blank,j,true);
      } else {
        draw_char(w[m],j,true);
      }
    }
    
    delay(325);

    lc.clearDisplay(0);
    lc.clearDisplay(1);
    lc.clearDisplay(2);
    lc.clearDisplay(3);
  }
}

/**
 * Draws a character on a matrix.
 * @param c the character.
 * @param m the matrix number.
 * @param on true to set the leds on, false to set off.
 */
void draw_char(int* c, int m, bool on)
{
  int i;
  int row = 0;
  int col = 0;
  int num_rows = 8;
  int num_cols = c[0];
  for (i = 1; i < num_rows * num_cols + 1; i ++) {
    if (c[i] == 1) {
      lc.setLed(m,7 - col,7 - row,on);
    }
    row = row + 1;
    if (row == num_cols) {
      row = 0;
      col = col + 1;
    }
  }
}



