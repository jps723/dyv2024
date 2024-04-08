int solenoidPins[] = { 24, 25, 26, 27, 33 };
void setup() {
  setupPins(solenoidPins, 5);
}
void loop() {

  int delayTime = map(analogRead(A14), 0, 1023, 80, 500);
  for (int i = 0; i < 5; i++) {
    digitalWrite(solenoidPins[i], HIGH);
    delay(delayTime);
    digitalWrite(solenoidPins[i], LOW);
    delay(delayTime);
  }
}
//set the pins as outputs
void setupPins(int pins[], int lengthOfArray) {
  for (int i = 0; i < lengthOfArray; i++) {
    pinMode(pins[i], OUTPUT);
  }
}