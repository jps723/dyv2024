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
AudioSynthWaveformDc dc1;                  //xy=355,407
AudioSynthWaveformModulated waveformMod1;  //xy=489,359
AudioEffectEnvelope envelope2;             //xy=498,406
AudioFilterStateVariable filter1;          //xy=678,365
AudioEffectEnvelope envelope1;             //xy=816,351
AudioOutputI2S i2s1;                       //xy=985,345
AudioConnection patchCord1(dc1, envelope2);
AudioConnection patchCord2(waveformMod1, 0, filter1, 0);
AudioConnection patchCord3(envelope2, 0, filter1, 1);
AudioConnection patchCord4(filter1, 0, envelope1, 0);
AudioConnection patchCord5(envelope1, 0, i2s1, 0);
AudioConnection patchCord6(envelope1, 0, i2s1, 1);
AudioControlSGTL5000 sgtl5000_1;  //xy=923,407
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
int rootNote = 36;
int currentWaveform = 0;

//Store the waveform types in an array
int waveTypes[5] = { WAVEFORM_SAWTOOTH, WAVEFORM_SINE, WAVEFORM_PULSE, WAVEFORM_TRIANGLE, WAVEFORM_SQUARE };

//a variable for shifting the position within the waveTypes[] array
int currentWaveformIndex = 0;

//a variable for shifting the position within the array
int currentOctave = 1;

void setup() {
  pinMode(29, INPUT);
  pinMode(30, INPUT);
  pinMode(36, INPUT);
  pinMode(37, INPUT);

  Serial.begin(9600);
  AudioMemory(100);
  sgtl5000_1.enable();
  sgtl5000_1.volume(.6);

  dc1.amplitude(1.0);
  waveformMod1.frequency(55 * currentOctave);
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

  playNote();
  octaveCount();
  waveSelect();
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

//This function plays a random note from a scale that is hardcoded. Change the 
//value in the first array of rootScaled[this one][] to cycle through different scales/modes
//The knobs determine note length,filter attack time, envelope release
//time, and tempo via a simple delay.
void playNote() {
  if (button0.risingEdge()) {
    int randomVal(random(8));
    waveformMod1.frequency(mtof.toFrequency(rootScaled[0][randomVal] + ((currentOctave)*12)));
    //Print the MIDI value and Frequencies
    Serial.print("MIDI Value: ");
    Serial.print(mtof.toPitch(mtof.toFrequency(rootScaled[0][randomVal] + ((currentOctave)*12))));
    Serial.print(" | Frequency: ");
    Serial.print(mtof.toFrequency(rootScaled[0][randomVal] + ((currentOctave + 1) * 12)));
    Serial.print(" | Octave: ");
    Serial.println(currentOctave + 1);

    int filterAttackTime = map(analogRead(A15), 0, 1023, 1, 5000);
    int envelopeReleaseTime = map(analogRead(A17), 0, 1023, 1, 5000);
    float filterResonance = map((float)analogRead(A16), 0, 1023, 0, 5);

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
  }
  if (button0.fallingEdge()) {
    envelope2.noteOff();
    envelope1.noteOff();
  }
}

void waveSelect() {
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
void octaveCount() {
  if (button2.risingEdge()) {
    //if the button is pressed, add 1 to the index and then divide by the total
    //number of indices in the array to calculate the remainder.
    currentOctave = ((currentOctave + 1) % 4);
  }
}