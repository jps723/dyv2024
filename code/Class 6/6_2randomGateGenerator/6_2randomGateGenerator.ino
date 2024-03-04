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
  int randomInt = random(500) + 100;
  digitalWrite(13, HIGH); 
  delay(10);                  
  digitalWrite(13, LOW);  
  delay(randomInt);              
}
