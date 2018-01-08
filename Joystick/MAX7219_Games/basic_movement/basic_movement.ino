/*
 * Practice controlling a pixel on MAX7219 with Joystick.
 * @Author: Jake Lepere
 * @Date 01/08/2018
 */

// LED MATRIX CONTROLS
#include "LedControl.h"
const int NUM_MAT = 4;  // Number of matrices
LedControl lc = LedControl(12,11,10,NUM_MAT);

// JOYSTICK CONTROLS
const int X_PIN = 0;    // X analog pin
const int Y_PIN = 1;    // Y analog pin
const int MIN_XY_VALUE = 0;      // Min x and y value
const int MAX_XY_VALUE = 1023;   // Max x and y value 
const int MID_XY_VALUE = 511;    // Mid x and y value
int x_value;    // Value from x_pin
int y_value;    // Value from y_pin

// PROGRAM CONTROL VARIABLES
int x_coord;    // Current x coordinate
int y_coord;    // Current y coordinate
const int SENSITIVITY = 50;   // Delay, set lower to r/w faster.

void setup() {

  // Matrix Setup
  int intensity = 5;
  int i;
  for(i = 0; i < NUM_MAT; i ++) {
    lc.shutdown(i,false);
    lc.setIntensity(i,intensity);
    lc.clearDisplay(i);
  }

  // Initialize coordinates
  x_coord = 0;
  y_coord = 0;

  // Computer communiation
  Serial.begin(115200);
  
}

void loop() {

  lc.setLedFull(y_coord,x_coord,true);

  delay(SENSITIVITY);

  /*
  Serial.print("X: ");
  x_value = analogRead(X_PIN);
  Serial.print(x_value);
  Serial.print("\n");
  delay(10);
  Serial.print("Y: ");
  y_value = analogRead(Y_PIN);
  Serial.print(y_value);
  Serial.print("\n");
  delay(10);
  Serial.print("D: ");
  Serial.print(getDirection(x_value,y_value));
  Serial.print("\n\n");
  */

  x_value = analogRead(X_PIN);
  delay(10);
  y_value = analogRead(Y_PIN);
  movePoint(getDirection(x_value,y_value));
  
}

/*
 * Gets the direction of the joystick defined as:
 *    0 -> N/A
 *    1 -> Right
 *    2 -> Down
 *    3 -> Left
 *    4 -> Up
 * @param x the x value from the joystick
 * @param y the y value from the joystick
 * @return the direction of the joystick
 */
int getDirection(int x, int y) {
  /*
   * Can improve by using coordinate system.
   * Get the angle of the point with respect to the origin (512x512)
   * If distance is greater than some threshold, return 1/2/3/4 depending on the angle.
   */
  int error = 75;
  if ((abs(MAX_XY_VALUE - x) < error) and (abs(MID_XY_VALUE - y) < error)) {
    return 1;
  } else if ((abs(MAX_XY_VALUE - y) < error) and (abs(MID_XY_VALUE - x) < error)) {
    return 2;
  } else if ((abs(MIN_XY_VALUE - x) < error) and (abs(MID_XY_VALUE - y) < error)) {
    return 3;
  } else if ((abs(MIN_XY_VALUE - y) < error) and (abs(MID_XY_VALUE - x) < error)) {
    return 4;
  } else {
    return 0;
  }
}

/*
 * Moves the point from a direction.
 * @param d the direction defined as:
 *    0 -> N/A
 *    1 -> Right
 *    2 -> Down
 *    3 -> Left
 *    4 -> Up
 */
void movePoint(int d) {
  bool moved = false;
  if (d == 1) {
    if (x_coord > 0) {
      x_coord -= 1;
      moved = true;
    }
  } else if (d == 2) {
    if (y_coord > 0) {
      y_coord -= 1;
      moved = true;
    }
  } else if (d == 3) {
    if (x_coord < 31) {
      x_coord += 1;
      moved = true;
    }
  } else if (d == 4) {
    if (y_coord < 7) {
      y_coord += 1;
      moved = true;
    }
  }
  if (moved) lc.clearDisplayAll();
}

