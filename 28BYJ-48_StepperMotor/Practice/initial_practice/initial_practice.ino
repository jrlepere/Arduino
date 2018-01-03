#include <Stepper.h>

#define IN1 8
#define IN2 10
#define IN3 9
#define IN4 11

const int stepPerRev = 2048;
const int maxStepSpeed = 16;

Stepper s = Stepper(stepPerRev,IN1,IN2,IN3,IN4);

void setup() {
  int stepSpeed = maxStepSpeed - 0;
  s.setSpeed(stepSpeed);
  Serial.begin(9600);
}

void loop() {
  s.step(stepPerRev/4);
  delay(10);
  s.step(-stepPerRev/4);
  delay(10);
}
