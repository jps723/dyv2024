#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       basicWave;      //xy=374,459
AudioOutputI2S           output;           //xy=557,459
AudioConnection          patchCord1(basicWave, 0, output, 0);
AudioConnection          patchCord2(basicWave, 0, output, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=572,580
// GUItool: end automatically generated code

float amp = 0.9;
int freq = 440;
int angle = 180;

void setup() {
  Serial.begin(9600);
  AudioMemory(50);

  sgtl5000_1.enable();
  sgtl5000_1.volume(.6);

  basicWave.frequency(freq);
  basicWave.amplitude(amp);
  basicWave.phase(angle);

  basicWave.begin(WAVEFORM_SQUARE);

}

// pitch scales logarithmically
float inputToPitch(int input)
{
  int n = map(input, 0, 1023, 21, 108);
  return 440 * pow(2, (n - 69) / 12.0);
}

void loop() {
  int frequencyKnobValue = map(analogRead(A14), 0, 1023, 220, 880);
  float ampKnobValue = map((float)analogRead(A15), 0, 1023, 0, 1);
  int angleKnobValue = map(analogRead(A16), 0, 1023, 0, 360);
  //  basicWave.frequency(frequencyKnobValue);
  //  basicWave.amplitude(ampKnobValue);

  if (frequencyKnobValue != freq) {
    // update if it has
    freq = frequencyKnobValue;
    basicWave.frequency(frequencyKnobValue);
  }
  if (ampKnobValue != amp) {
    // update if it has
    amp = ampKnobValue;
    basicWave.amplitude(ampKnobValue);
  }  

}
