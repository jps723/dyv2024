#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

//include the Bounce library for debouncing without delay
#include <Bounce.h>

// GUItool: begin automatically generated code
AudioSynthWaveform waveform1;  //xy=493,410
AudioOutputI2S i2s1;           //xy=698,407
AudioConnection patchCord1(waveform1, 0, i2s1, 0);
AudioConnection patchCord2(waveform1, 0, i2s1, 1);
AudioControlSGTL5000 sgtl5000_1;  //xy=700,472
// GUItool: end automatically generated code

Bounce waveCycleButton = Bounce(36, 15);  // declare the pin and debounce time of 15ms

float amp = 1.0;
int freq = 110;

//we'll use this variable to cycle between waveform types with a button
int currentWaveform = 0;

void setup() {
  Serial.begin(9600);
  //declare some space on the board for audio memory
  AudioMemory(20);
  pinMode(36, INPUT);

  //set up the audio board
  sgtl5000_1.enable();
  //this affects the volume of the headphone jack. It does not affect the line level outputs
  sgtl5000_1.volume(0.5);

  currentWaveform = WAVEFORM_SQUARE;

  //setup for waveform object
  waveform1.frequency(freq);
  waveform1.amplitude(amp);
  waveform1.begin(currentWaveform);
}

void loop() {
  waveCycleButton.update();

  freq = map(analogRead(A14), 0, 1023, 55, 880);
  waveform1.frequency(freq);

  //if the button is pressed, move to the next waveform in the list
  if (waveCycleButton.fallingEdge()) {
    switch (currentWaveform) {
      case WAVEFORM_SINE:
        currentWaveform = WAVEFORM_SAWTOOTH;
        Serial.println("Sawtooth Wave");
        break;
      case WAVEFORM_SAWTOOTH:
        currentWaveform = WAVEFORM_SQUARE;
        Serial.println("Square Wave");
        break;
      case WAVEFORM_SQUARE:
        currentWaveform = WAVEFORM_TRIANGLE;
        Serial.println("Triangle Wave");
        break;
      case WAVEFORM_TRIANGLE:
        currentWaveform = WAVEFORM_PULSE;
        Serial.println("Pulse Wave");
        break;
      case WAVEFORM_PULSE:
        currentWaveform = WAVEFORM_SINE;
        Serial.println("Sine Wave");
        break;
    }
    AudioNoInterrupts();
    waveform1.begin(currentWaveform);
    AudioInterrupts();
  }
}
