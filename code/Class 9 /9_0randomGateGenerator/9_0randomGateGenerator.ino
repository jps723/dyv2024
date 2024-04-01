/*
This is basically the blink sketch :)

A random value is used to determine the time between triggers
which is then used to trigger external microcontrollers/hardware.

*/

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(13, OUTPUT);
}

void loop() {
  int knobValue = map(analogRead(A16), 0, 1023, 0, 2500);
  int randomInt = random(100) + knobValue;
  digitalWrite(13, HIGH); 
  delay(10);                  
  digitalWrite(13, LOW);  
  delay(randomInt);              
}
