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
AudioInputI2S i2s1;                 //xy=382,401
AudioEffectBitcrusher bitcrusher1;  //xy=535,396
AudioOutputI2S i2s2;                //xy=699,400
AudioConnection patchCord1(i2s1, 0, bitcrusher1, 0);
AudioConnection patchCord2(bitcrusher1, 0, i2s2, 0);
AudioConnection patchCord3(bitcrusher1, 0, i2s2, 1);
AudioControlSGTL5000 sgtl5000_1;  //xy=697,460
// GUItool: end automatically generated code

const int lineInput = AUDIO_INPUT_LINEIN;
//const int myInput = AUDIO_INPUT_MIC;

void setup() {
  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(40);

  // Enable the audio shield, select input, and enable output
  sgtl5000_1.enable();
  sgtl5000_1.inputSelect(lineInput);
  sgtl5000_1.volume(0.5);

  //these settings allow the signal to pass through without any effect
  bitcrusher1.bits(16);
  bitcrusher1.sampleRate(44100);
}

void loop() {
  //read the input sensor and make it a float
  int bits = map(analogRead(A14), 0, 1023, 0, 16);
   int sampleRate = map(analogRead(A15), 0, 1023, 1, 44100);

  //multiply the 0-1 value by 20 to give it an
  //effective range of 0 to 20 seconds
  bitcrusher1.bits(bits);
  bitcrusher1.sampleRate(sampleRate);

  Serial.print("Bits: ");
  Serial.println(bits);
  Serial.print("Sample Rate: ");
  Serial.println(sampleRate);
}
