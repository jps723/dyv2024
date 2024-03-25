#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S            i2s1;           //xy=429,324
AudioEffectDelay         delay1;         //xy=573,523
AudioMixer4              mixer1;         //xy=579,337
AudioOutputI2S           i2s2;           //xy=769,470
AudioConnection          patchCord1(i2s1, 0, mixer1, 0);
AudioConnection          patchCord2(delay1, 0, i2s2, 0);
AudioConnection          patchCord3(delay1, 0, i2s2, 1);
AudioConnection          patchCord4(delay1, 0, mixer1, 3);
AudioConnection          patchCord5(mixer1, delay1);
AudioControlSGTL5000     sgtl5000_1;     //xy=821,534
// GUItool: end automatically generated code

#include <Bounce.h>

Bounce button0 = Bounce(36, 5);

void setup() {
  Serial.begin(9600);
  pinMode(36, INPUT);
  AudioMemory(160);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.55);
  sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);
  sgtl5000_1.micGain(36);
  mixer1.gain(0, 0.5);
  mixer1.gain(3, 0.7);
  delay1.delay(0, 400);
  delay(1000);
}

void loop() {
  int feedbackPot = analogRead(A14);
  float feedbackAmount = (float)feedbackPot / 1050.0;
  mixer1.gain(3, feedbackAmount);
  
}




