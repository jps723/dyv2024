#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform1;      //xy=110,75
AudioOutputPT8211        pt8211_1;          //xy=303,78
AudioConnection          patchCord1(waveform1, 0, pt8211_1, 0);
AudioConnection          patchCord2(waveform1, 0, pt8211_1, 1);
// GUItool: end automatically generated code

float lfoRate = 0;

void setup() {
  Serial.begin(9600); 
  AudioMemory(15);
  waveform1.begin(WAVEFORM_SINE);
  waveform1.frequency(8);
  waveform1.amplitude(0.99);
  Serial.write("code has been uploaded");
  
}

void loop() {
  lfoRate = map(analogRead(A15), 0, 1023, 0, 40);
    waveform1.frequency(lfoRate);
  
}
