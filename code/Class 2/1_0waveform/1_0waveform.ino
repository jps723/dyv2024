#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>


// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=518,264
AudioOutputI2S           i2s1;           //xy=700,266
AudioConnection          patchCord1(waveform1, 0, i2s1, 0);
AudioConnection          patchCord2(waveform1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=711,349
// GUItool: end automatically generated code


float amp = 1;
int freq = 110;

void setup() {
  Serial.begin(9600);

  //declare some space on the board for audio memory
  AudioMemory(10);

  //set up the audio board
  sgtl5000_1.enable();

  //this affects the volume of the headphone jack. It does not affect the line level outputs
  sgtl5000_1.volume(0.5);

  //setup for waveform object
  waveform1.frequency(freq);
  waveform1.amplitude(amp);
  waveform1.begin(WAVEFORM_SQUARE);
}

void loop() {
  freq = map(analogRead(A14), 0, 1023, 55, 880);
  waveform1.frequency(freq);
}
