
const int X_PIN = 0;    // X analog in pin
const int Y_PIN = 1;    // Y analog in pin

void setup() {
  Serial.begin(115200);   // Computer communication
}

void loop() {

  // X joystick position
  Serial.print("X: ");
  Serial.print(analogRead(X_PIN));
  Serial.print("\n");

  // Delay
  delay(100);

  // Y joystick position
  Serial.print("Y: ");
  Serial.print(analogRead(Y_PIN));
  Serial.print("\n\n");

  // Delay
  delay(1000);

}
