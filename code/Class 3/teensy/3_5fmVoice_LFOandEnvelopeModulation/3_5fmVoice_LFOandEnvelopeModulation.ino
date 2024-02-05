/*
This is a basic FM synth voice. 

Envelope2 is the modulation signal for adjusting the frequency of waveformMod1. This causes the pitch to change 
in a more expressive way than with an LFO alone. The DC signal is a constant signal that shaped by the envelope.
Adjust the amplitude to adjust the modulation depth.

Waveform2 is the modulation signal for the filter frequency cutoff. 

This example introduces using an envelope as a frequency modulator
*/

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Bounce.h>

// GUItool: begin automatically generated code
AudioSynthWaveformDc     dc1;            //xy=181,357
AudioEffectEnvelope      envelope2;      //xy=323,354
AudioSynthWaveformModulated waveformMod1;   //xy=489,359
AudioSynthWaveform       waveform2;      //xy=507,401
AudioFilterStateVariable filter1;        //xy=678,365
AudioEffectEnvelope      envelope1;      //xy=816,351
AudioOutputI2S           i2s1;           //xy=985,345
AudioConnection          patchCord1(dc1, envelope2);
AudioConnection          patchCord2(envelope2, 0, waveformMod1, 0);
AudioConnection          patchCord3(waveformMod1, 0, filter1, 0);
AudioConnection          patchCord4(waveform2, 0, filter1, 1);
AudioConnection          patchCord5(filter1, 0, envelope1, 0);
AudioConnection          patchCord6(envelope1, 0, i2s1, 0);
AudioConnection          patchCord7(envelope1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=923,407
// GUItool: end automatically generated code


// Bounce objects to read pushbuttons
Bounce button0 = Bounce(36, 15);

float dcAmp;

void setup() {
  // put your setup code here, to run once:
  pinMode(36, INPUT);
  pinMode(37, INPUT);
  pinMode(29, INPUT);
  pinMode(30, INPUT);

  Serial.begin(9600);
  AudioMemory(100);
  sgtl5000_1.enable();
  sgtl5000_1.volume(.6);

  dcAmp = (float)analogRead(A14) / 1023.0;

  dc1.amplitude(dcAmp);
  waveformMod1.frequency(110);
  waveformMod1.amplitude(0.8);
  waveformMod1.begin(WAVEFORM_SAWTOOTH);

  waveform2.frequency(map(analogRead(A16), 0, 1023, 0, 5));

  float knob_A17 = (float)analogRead(A17) / 1023.0;
  waveform2.amplitude(knob_A17);
  waveform2.begin(WAVEFORM_SINE);
}

void loop() {
  // Update all the button objects
  button0.update();
  button1.update();
  button2.update();
  button3.update();
  playNote();


  dcAmp = (float)analogRead(A14) / 1023.0;
  dc1.amplitude(dcAmp);

  //waveform1.frequency(modulatorFreq);
  //waveform1.frequency(440);
  //float fmModulatorAmp = (float)analogRead(A15) / 1023.0;
  // waveform1.amplitude(fmModulatorAmp);
  //Serial.println(fmModulatorAmp);
  //
  //waveformMod1.frequency(880);
  //waveformMod1.amplitude(0.8);

  waveform2.frequency(map((float)analogRead(A17), 0, 1023, 0.1, 5));
  float filterLFOAmp = analogRead(A17) / 1023;
  waveform2.amplitude(1.0);

}

void playNote() {
  if (button0.risingEdge()) {
    Serial.println("Note Up");
    envelope1.attack(0);
    //envelope1.hold(0);
    envelope1.decay(0);
    envelope1.sustain(0.5);
    envelope1.release(3000);

    envelope2.attack(0);
    //envelope1.hold(0);
    envelope2.decay(1000);
    envelope2.sustain(0.5);
    envelope2.release(3000);

    envelope1.noteOn();
    envelope2.noteOn();
    //add a short delay before shutting off the note
    //delay(50);
  }
  if (button0.fallingEdge()) {
    Serial.println("Note Up");
    envelope2.noteOff ();
    envelope1.noteOff();
  }

}
