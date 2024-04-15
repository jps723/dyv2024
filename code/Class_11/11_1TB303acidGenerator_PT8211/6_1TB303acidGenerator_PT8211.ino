#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

//include the local scales.h file
#include "scales.h"
//include midi to frequency lib by littlescale
#include <mtof.h>
//include the bounce library for more stable button readings
#include <Bounce.h>

// GUItool: begin automatically generated code
AudioSynthWaveformDc     dc1;            //xy=214.09091186523438,354
AudioSynthWaveformModulated waveformMod1;   //xy=348.0909118652344,306
AudioEffectEnvelope      envelope2;      //xy=357.0909118652344,353
AudioFilterStateVariable filter1;        //xy=537.0909118652344,312
AudioEffectEnvelope      envelope1;      //xy=675.0909118652344,298
AudioOutputPT8211        pt8211_1;       //xy=876.0909118652344,312.0909118652344
AudioConnection          patchCord1(dc1, envelope2);
AudioConnection          patchCord2(waveformMod1, 0, filter1, 0);
AudioConnection          patchCord3(envelope2, 0, filter1, 1);
AudioConnection          patchCord4(filter1, 0, envelope1, 0);
AudioConnection          patchCord5(envelope1, 0, pt8211_1, 0);
AudioConnection          patchCord6(envelope1, 0, pt8211_1, 1);
// GUItool: end automatically generated code


// Bounce objects to read pushbuttons
Bounce button0 = Bounce(36, 15);
Bounce button1 = Bounce(37, 15);  // 15 ms debounce time
Bounce button2 = Bounce(29, 15);
Bounce button3 = Bounce(30, 15);

//a 2D array to store the notes of our scales in.
//There are 7 scales (diatonic modes), with 8 notes each
int rootScaled[7][8] = {};

//pick a root note/key.
int rootNote = 40;
int currentWaveform = 0;

//Store the waveform types in an array
int waveTypes[5] = { WAVEFORM_SAWTOOTH, WAVEFORM_SINE, WAVEFORM_PULSE, WAVEFORM_TRIANGLE, WAVEFORM_SQUARE };
//a variable for shifting the position within the waveTypes[] array
int currentWaveformIndex = 0;

void setup() {
  pinMode(29, INPUT);
  pinMode(30, INPUT);
  pinMode(36, INPUT);
  pinMode(37, INPUT);

  Serial.begin(9600);
  AudioMemory(100);

  dc1.amplitude(1.0);
  waveformMod1.frequency(55);
  waveformMod1.amplitude(0.8);

  waveformMod1.begin(waveTypes[currentWaveformIndex]);

  //this adjusts the range of the frequency sweep in the filter. Make it smaller
  //if you ever get static at a polar end.
  filter1.octaveControl(3.5);
  filter1.resonance(5);

  //this fills the scales array with the scales in scales.h
  fillScalesArrays();
}

void loop() {
  // Update all the button objects
  button0.update();
  button1.update();
  button2.update();
  button3.update();

  playSequence();

  //Cycle through the waveTypes array with a button press
  if (button1.fallingEdge()) {
    //if the button is pressed, add 1 to the index and then divide by the total number of indices in the array to calculate the remainder
    currentWaveformIndex = (currentWaveformIndex + 1) % 5;
    //use AudioNoInterrupts() to pause the audio library and update the 4 waveforms all at the same time
    AudioNoInterrupts();
    waveformMod1.begin(waveTypes[currentWaveformIndex]);
    AudioInterrupts();
  }
}

//This function calculates the array of MIDI
//values that we have immediate access to, to play
void fillScalesArrays() {
  for (int i = 0; i < scalesArrayLength; i++) {
    for (int j = 0; j < diatonicArrayLength; j++) {
      rootScaled[i][j] = rootNote + scales[i][j];
    }
  }
}

//This function plays a random sequence as set by a hardcoded scale
//and calculation by a random value. The knobs determine note length,
//filter attack time, envelope release time, and tempo via a simple delay.
void playSequence() {
  int randomVal = random(8);
  waveformMod1.frequency(mtof.toFrequency(rootScaled[0][randomVal]));
  Serial.print("MIDI Value: ");
  Serial.print(mtof.toPitch(mtof.toFrequency(rootScaled[0][randomVal])));
  Serial.print(" || Frequency: ");
  Serial.println(mtof.toFrequency(rootScaled[0][randomVal]));

  int tempo = 200;
  int filterAttackTime = 1;
  int envelopeReleaseTime = 10;
  float filterResonance = 0;

  //set all of the parameters for the note
  envelope1.attack(0);
  envelope1.decay(0);
  envelope1.sustain(1);
  envelope1.release(envelopeReleaseTime);

  envelope2.attack(filterAttackTime);
  envelope2.decay(1000);
  envelope2.sustain(1);
  envelope2.release(envelopeReleaseTime);

  filter1.resonance(filterResonance);

  //trigger the note
  envelope1.noteOn();
  envelope2.noteOn();

  //add a short delay before shutting off the note
  delay(10);
  envelope2.noteOff();
  envelope1.noteOff();
  //delay by the knob value to control the overall speed of the sequence
  delay(tempo);
}
