#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <math.h>

//include the Bounce library for debouncing without delay
#include <Bounce.h>

// GUItool: begin automatically generated code
AudioSynthWaveform waveform1;      //xy=320,348
AudioSynthWaveform waveform2;      //xy=329,394
AudioMixer4 mixer;                 //xy=488,374
AudioFilterStateVariable filter1;  //xy=675,372
AudioOutputI2S i2s;                //xy=817,365
AudioConnection patchCord1(waveform1, 0, mixer, 0);
AudioConnection patchCord2(waveform2, 0, mixer, 1);
AudioConnection patchCord3(mixer, 0, filter1, 0);
AudioConnection patchCord4(mixer, 0, filter1, 1);
AudioConnection patchCord5(filter1, 0, i2s, 0);
AudioConnection patchCord6(filter1, 0, i2s, 1);
AudioControlSGTL5000 sgtl5000;  //xy=813,435
// GUItool: end automatically generated code


Bounce waveCycleButton = Bounce(36, 15);  // declare the pin and debounce time of 15ms

//set the initial values for frequency and detuning
int freq = 440;
int detuneAmount = 0;
int detuneValue = 0;

//we'll use this variable to cycle between waveform types with a button
int currentWaveform = 0;

void setup() {
  // reserve some memory for the audio functions
  AudioMemory(20);
  pinMode(36, INPUT);

  //set up the audio board
  sgtl5000.enable();
  //this affects the volume of the headphone jack. It does not affect the line level outputs
  sgtl5000.volume(0.5);

  // A pot to adjust the base frequency
  pinMode(A14, INPUT);

  // A pot to adjust the amount to detune the second oscillator
  pinMode(A15, INPUT);

  // A pot to adjust the filter frequency cutoff
  pinMode(A16, INPUT);

  currentWaveform = WAVEFORM_SQUARE;

  // waveform1 setup
  waveform1.frequency(freq);
  waveform1.amplitude(0.5);
  waveform1.begin(currentWaveform);

  // waveform2 setup
  waveform2.frequency(freq);
  waveform2.amplitude(0.5);
  waveform2.begin(currentWaveform);

  //filter1 setup
  filter1.frequency(800);
}

void loop() {
  waveCycleButton.update();
  // read the pitch pot position
  int baseFrequency = analogRead(A14);

  //Check to see if the knob value has changed
  if (baseFrequency != freq) {
    // if yes, update the variable
    freq = baseFrequency;

    //adjust the frequency based on the new value
    //the first waveform will play at the frequency we assign
    waveform1.frequency(inputToFreq(baseFrequency, 0));

    //the first waveform will play at the frequency we assign +/- the amount we detune it
    waveform2.frequency(inputToFreq(baseFrequency, detuneAmount));
  }

  // Average the values from the knob
  detuneValue = averageReadings(analogRead(A15), detuneValue, 32);

  //scale down the detune value by 5 to fit within the midi range of ~5 octaves, and then subtract the full range
  int newDetuneValue = detuneValue / 5 - 102;

  // Make values close to 0 more stable since detuning is most interesting as the bas frequencies diverge
  if (newDetuneValue > 0)
    newDetuneValue = max(0, newDetuneValue - 2);
  else if (newDetuneValue < 0)
    newDetuneValue = min(0, newDetuneValue + 2);
  //Check to see if the knob value has changed
  if (newDetuneValue != detuneValue) {
    // if yes, update the variable
    detuneAmount = newDetuneValue;

    //adjust the frequency based on the new value
    //the first waveform will play at the frequency we assign without being detuned
    waveform1.frequency(inputToFreq(baseFrequency, 0));

    //the second waveform will play at the frequency we assign +/- the amount we detune it
    waveform2.frequency(inputToFreq(baseFrequency, detuneAmount));

    Serial.print("Oscillator 2 is detuned by: ");
    Serial.println(detuneAmount);
  }

  waveCycleButtonHandler();

  int frequencyCutoffKnob = analogRead(A16);
  // quick and dirty equation for exp scale frequency adjust
  float frequencyCutoff = expf((float)frequencyCutoffKnob / 150.0) * 8;
  filter1.frequency(frequencyCutoff);
}

void waveCycleButtonHandler() {
  if (waveCycleButton.fallingEdge()) {
    switch (currentWaveform) {
      case WAVEFORM_SINE:
        currentWaveform = WAVEFORM_SAWTOOTH;
        break;
      case WAVEFORM_SAWTOOTH:
        currentWaveform = WAVEFORM_SQUARE;
        break;
      case WAVEFORM_SQUARE:
        currentWaveform = WAVEFORM_TRIANGLE;
        break;
      case WAVEFORM_TRIANGLE:
        currentWaveform = WAVEFORM_PULSE;
        break;
      case WAVEFORM_PULSE:
        currentWaveform = WAVEFORM_SINE;
        break;
    }
    AudioNoInterrupts();
    waveform1.begin(currentWaveform);
    waveform2.begin(currentWaveform);
    AudioInterrupts();
  }
}

// This function converts the base frequency and detuning amount
//to midi and then into a frequency based on a logarithmic scale - this is important in western music
float inputToFreq(int freq, int detuneAmount) {
  int midiVal = map(freq, 0, 1023, 21, 108);
  float f = 440 * pow(2, (midiVal - 69) / 12.0);
  // calculate the frequency and divide by 1200 cents (https://en.wikipedia.org/wiki/Cent_(music))
  return f * pow(2, detuneAmount / 1200.0);
}

// This function smoothes sensor values
int averageReadings(int newValue, int currentValue, int numberOfReadings) {
  return floor(((numberOfReadings - 1) * currentValue + newValue) / numberOfReadings);
}
