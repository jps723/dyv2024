#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Bounce.h>

// GUItool: begin automatically generated code
AudioInputI2S i2s2;       //xy=383,452
AudioEffectDelay delay2;  //xy=545,612
AudioMixer4 mixer2;       //xy=549,498
AudioMixer4 mixer1;       //xy=712,464
AudioOutputI2S i2s1;      //xy=857,459
AudioConnection patchCord1(i2s2, 0, mixer2, 0);
AudioConnection patchCord2(i2s2, 0, mixer1, 0);
AudioConnection patchCord3(delay2, 0, mixer2, 1);
AudioConnection patchCord4(mixer2, delay2);
AudioConnection patchCord5(mixer2, 0, mixer1, 1);
AudioConnection patchCord6(mixer1, 0, i2s1, 0);
AudioConnection patchCord7(mixer1, 0, i2s1, 1);
AudioControlSGTL5000 sgtl5000_1;  //xy=839,555
// GUItool: end automatically generated code

// Bounce button0 = Bounce(36, 15);
// Bounce button1 = Bounce(37, 15);
// Bounce button2 = Bounce(29, 15);

const int lineInput = AUDIO_INPUT_LINEIN;
//const int myInput = AUDIO_INPUT_MIC;

void setup() {
  // put your setup code here, to run once:
  AudioMemory(400);
  //change to INPUT_PULLUP if not using external resistor

  pinMode(36, INPUT);
  pinMode(37, INPUT);
  pinMode(29, INPUT);

  // Enable the audio shield, select input, and enable output
  sgtl5000_1.enable();
  sgtl5000_1.inputSelect(lineInput);
  sgtl5000_1.volume(0.5);
  //sgtl5000_1.adcHighPassFilterDisable();

  delay2.delay(0, 300);

  mixer1.gain(0, 1);
  mixer1.gain(1, 1);

  mixer2.gain(0, 1);
  mixer2.gain(1, 1);
}

void loop() {

  //divide by 1023 to get values between 0.0 and 1.0
  float unaffectedSignal = (float)analogRead(A14) / 1023;
  float delayedSignal = (float)analogRead(A16) / 1023;
  float feedbackLevel = (float)analogRead(A17) / 1023;
  int delayTime = map(analogRead(A15), 0, 1023, 0, 700);

  mixer1.gain(0, unaffectedSignal);
  mixer1.gain(1, delayedSignal);
  mixer2.gain(0, 1);
  mixer2.gain(1, feedbackLevel);
  delay2.delay(0, delayTime);

  Serial.print("Unaffected Signal: ");
  Serial.println(unaffectedSignal);
  Serial.print("Delay Time: ");
  Serial.println(delayTime);
  Serial.print("Affected Level: ");
  Serial.println(delayedSignal);
  Serial.print("Feedback Level: ");
  Serial.println(feedbackLevel);
}
