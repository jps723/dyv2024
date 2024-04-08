/*
 * A simple hardware test which receives audio from the audio shield
 * Line-In pins and send it to the Line-Out pins and headphone jack.
 *
 * This example code is in the public domain.
 */

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioInputI2S i2s1;       //xy=191,318
AudioEffectDelay delay1;  //xy=375,305
AudioOutputI2S i2s2;      //xy=570,268
AudioConnection patchCord1(i2s1, 0, delay1, 0);
AudioConnection patchCord2(delay1, 0, i2s2, 0);
AudioConnection patchCord3(delay1, 0, i2s2, 1);
AudioControlSGTL5000 sgtl5000_1;  //xy=516,398
// GUItool: end automatically generated code

//const int lineInput = AUDIO_INPUT_LINEIN;
const int myInput = AUDIO_INPUT_MIC;


void setup() {
  Serial.begin(9600);
  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(120);

  // Enable the audio shield, select input, and enable output
  sgtl5000_1.enable();
  sgtl5000_1.inputSelect(myInput);
  sgtl5000_1.volume(0.5);
  sgtl5000_1.micGain(36);
  delay1.delay(1, 3000);
  delay(1000);
}

void loop() {
}
