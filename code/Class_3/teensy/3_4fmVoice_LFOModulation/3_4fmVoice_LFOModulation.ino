/*
This is a basic FM synth voice. 

Waveform1 is the modulation signal for adjusting the frequency of waveformMod1. 
Waveform2 is the modulation signal for the filter frequency cutoff. 
*/

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

//include the Bounce library for debouncing without delay
#include <Bounce.h>

// GUItool: begin automatically generated code
AudioSynthWaveform waveform1;              //xy=187,350
AudioSynthWaveformModulated waveformMod1;  //xy=366,355
AudioSynthWaveform waveform2;              //xy=404,396
AudioFilterStateVariable filter1;          //xy=555,361
AudioEffectEnvelope envelope1;             //xy=693,347
AudioOutputI2S i2s1;                       //xy=862,341
AudioConnection patchCord1(waveform1, 0, waveformMod1, 0);
AudioConnection patchCord2(waveformMod1, 0, filter1, 0);
AudioConnection patchCord3(waveform2, 0, filter1, 1);
AudioConnection patchCord4(filter1, 0, envelope1, 0);
AudioConnection patchCord5(envelope1, 0, i2s1, 0);
AudioConnection patchCord6(envelope1, 0, i2s1, 1);
AudioControlSGTL5000 sgtl5000_1;  //xy=800,403
// GUItool: end automatically generated code

//Create bounce objects for buttons. This makes their readings more stable/reliable
Bounce button0 = Bounce(36, 15);
Bounce button1 = Bounce(37, 15);  // 15 ms debounce time
Bounce button2 = Bounce(29, 15);
Bounce button3 = Bounce(30, 15);

void setup() {
  pinMode(36, INPUT);
  pinMode(37, INPUT);
  pinMode(29, INPUT);
  pinMode(30, INPUT);

  Serial.begin(9600);
  AudioMemory(100);
  sgtl5000_1.enable();
  sgtl5000_1.volume(.6);

  waveform1.frequency(map(analogRead(A14), 0, 1023, 220, 880));
  float fmModulatorAmp = analogRead(A15) / 1023;
  waveform1.amplitude(fmModulatorAmp);
  waveform1.begin(WAVEFORM_SINE);

  waveformMod1.frequency(110);
  waveformMod1.amplitude(0.8);
  waveformMod1.begin(WAVEFORM_SAWTOOTH);

  waveform2.frequency(map(analogRead(A16), 0, 1023, 0, 5));

  float waveform2Amplitude = (float)analogRead(A17) / 1023.0;
  waveform2.amplitude(waveform2Amplitude);
  waveform2.begin(WAVEFORM_SINE);
}

void loop() {
  // Update all the button objects
  button0.update();
  button1.update();
  button2.update();
  button3.update();
  playNote();

  float modulatorFreq = map((float)analogRead(A14), 0, 1023, 0.05, 100);

  waveform1.frequency(modulatorFreq);
  //waveform1.frequency(440);
  float fmModulatorAmp = (float)analogRead(A15) / 1023.0;
  waveform1.amplitude(fmModulatorAmp);
  Serial.println(fmModulatorAmp);
  //
  //waveformMod1.frequency(880);
  //waveformMod1.amplitude(0.8);

  waveform2.frequency(map((float)analogRead(A17), 0, 1023, 0.1, 5));
  waveform2.amplitude(1.0);
}

void playNote() {
  if (button0.risingEdge()) {
    Serial.println("Note Played");
    envelope1.attack(0);
    //envelope1.hold(0);
    envelope1.decay(0);
    envelope1.sustain(0.5);
    envelope1.release(500);
    envelope1.noteOn();
  }
  if (button0.fallingEdge()) {
    envelope1.noteOff();
  }
}
