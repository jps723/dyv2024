#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

//include the Bounce library for debouncing without delay
#include <Bounce.h>

// GUItool: begin automatically generated code
AudioSynthWaveform waveform1;              //xy=199,199
AudioSynthWaveform waveform5;              //xy=235,471
AudioSynthWaveform waveform3;              //xy=236,325
AudioSynthWaveform waveform7;              //xy=245,596
AudioSynthWaveformModulated waveformMod1;  //xy=409,209
AudioSynthWaveformModulated waveformMod3;  //xy=418,468
AudioSynthWaveformModulated waveformMod2;  //xy=420,332
AudioSynthWaveformModulated waveformMod4;  //xy=420,598
AudioSynthWaveform waveform6;              //xy=433,526
AudioSynthWaveform waveform8;              //xy=437,654
AudioSynthWaveform waveform2;              //xy=443,257
AudioSynthWaveform waveform4;              //xy=478,384
AudioFilterStateVariable filter1;          //xy=598,215
AudioFilterStateVariable filter3;          //xy=607,474
AudioFilterStateVariable filter2;          //xy=609,338
AudioFilterStateVariable filter4;          //xy=609,604
AudioEffectEnvelope envelope1;             //xy=736,201
AudioEffectEnvelope envelope3;             //xy=745,460
AudioEffectEnvelope envelope2;             //xy=747,324
AudioEffectEnvelope envelope4;             //xy=747,590
AudioMixer4 mixer1;                        //xy=959,368
AudioOutputI2S i2s1;                       //xy=1087,369
AudioConnection patchCord1(waveform1, 0, waveformMod1, 0);
AudioConnection patchCord2(waveform5, 0, waveformMod3, 0);
AudioConnection patchCord3(waveform3, 0, waveformMod2, 0);
AudioConnection patchCord4(waveform7, 0, waveformMod4, 0);
AudioConnection patchCord5(waveformMod1, 0, filter1, 0);
AudioConnection patchCord6(waveformMod3, 0, filter3, 0);
AudioConnection patchCord7(waveformMod2, 0, filter2, 0);
AudioConnection patchCord8(waveformMod4, 0, filter4, 0);
AudioConnection patchCord9(waveform6, 0, filter3, 1);
AudioConnection patchCord10(waveform8, 0, filter4, 1);
AudioConnection patchCord11(waveform2, 0, filter1, 1);
AudioConnection patchCord12(waveform4, 0, filter2, 1);
AudioConnection patchCord13(filter1, 0, envelope1, 0);
AudioConnection patchCord14(filter3, 0, envelope3, 0);
AudioConnection patchCord15(filter2, 0, envelope2, 0);
AudioConnection patchCord16(filter4, 0, envelope4, 0);
AudioConnection patchCord17(envelope1, 0, mixer1, 0);
AudioConnection patchCord18(envelope3, 0, mixer1, 2);
AudioConnection patchCord19(envelope2, 0, mixer1, 1);
AudioConnection patchCord20(envelope4, 0, mixer1, 3);
AudioConnection patchCord21(mixer1, 0, i2s1, 0);
AudioConnection patchCord22(mixer1, 0, i2s1, 1);
AudioControlSGTL5000 sgtl5000_1;  //xy=1085,448
// GUItool: end automatically generated code

//Create bounce objects for buttons. This makes their readings more stable/reliable
Bounce button4 = Bounce(28, 15);
Bounce button0 = Bounce(29, 15);
Bounce button1 = Bounce(30, 15);
Bounce button2 = Bounce(36, 15);
Bounce button3 = Bounce(37, 15);

//a variable for shifting the position within the array
int currentOctave = 1;

float cMajorScale[7] = {130.81, 146.83, 164.81, 174.61, 196.00, 220, 246.94};

void setup() {
  pinMode(28, INPUT);
  pinMode(29, INPUT);
  pinMode(30, INPUT);
  pinMode(36, INPUT);
  pinMode(37, INPUT);

  Serial.begin(9600);
  AudioMemory(50);
  sgtl5000_1.enable();
  sgtl5000_1.volume(.6);

  voice1Setup();
  voice2Setup();
  voice3Setup();
  voice4Setup();

  mixer1.gain(0, .25);
  mixer1.gain(1, .25);
  mixer1.gain(2, .25);
  mixer1.gain(3, .25);
}

void loop() {
  button0.update();
  button1.update();
  button2.update();
  button3.update();
  button4.update();
  //updateKnobs();
  playNote0();
  playNote1();
  playNote2();
  playNote3();
  octaveCount();
}

void voice1Setup() {
  waveform1.frequency(map(analogRead(A14), 0, 1023, 220, 880));
  float fmModulatorAmp = analogRead(A15) / 1023;
  waveform1.amplitude(fmModulatorAmp);
  waveform1.begin(WAVEFORM_SINE);

  waveformMod1.frequency(cMajorScale[0] * currentOctave);
  waveformMod1.amplitude(0.8);
  waveformMod1.begin(WAVEFORM_SAWTOOTH);

  waveform2.frequency(map(analogRead(A16), 0, 1023, 0, 5));

  float waveform2Amplitude = (float)analogRead(A17) / 1023.0;
  waveform2.amplitude(waveform2Amplitude);
  waveform2.begin(WAVEFORM_SINE);
}

void voice2Setup() {
  waveform3.frequency(map(analogRead(A14), 0, 1023, 220, 880));
  float fmModulatorAmp = analogRead(A15) / 1023;
  waveform3.amplitude(fmModulatorAmp);
  waveform3.begin(WAVEFORM_SINE);

  waveformMod2.frequency(cMajorScale[2] * currentOctave);
  waveformMod2.amplitude(0.8);
  waveformMod2.begin(WAVEFORM_SQUARE);

  waveform4.frequency(map(analogRead(A16), 0, 1023, 0, 5));

  float waveform2Amplitude = (float)analogRead(A17) / 1023.0;
  waveform4.amplitude(waveform2Amplitude);
  waveform4.begin(WAVEFORM_SINE);
}

void voice3Setup() {
  waveform5.frequency(map(analogRead(A14), 0, 1023, 220, 880));
  float fmModulatorAmp = analogRead(A15) / 1023;
  waveform5.amplitude(fmModulatorAmp);
  waveform5.begin(WAVEFORM_SINE);

  waveformMod3.frequency(cMajorScale[4] * currentOctave);
  waveformMod3.amplitude(0.8);
  waveformMod3.begin(WAVEFORM_SAWTOOTH);

  waveform6.frequency(map(analogRead(A16), 0, 1023, 0, 5));

  float waveform2Amplitude = (float)analogRead(A17) / 1023.0;
  waveform6.amplitude(waveform2Amplitude);
  waveform6.begin(WAVEFORM_SINE);
}

void voice4Setup() {
  waveform7.frequency(map(analogRead(A14), 0, 1023, 220, 880));
  float fmModulatorAmp = analogRead(A15) / 1023;
  waveform7.amplitude(fmModulatorAmp);
  waveform7.begin(WAVEFORM_SINE);

  waveformMod4.frequency(cMajorScale[6] * currentOctave);
  waveformMod4.amplitude(0.8);
  waveformMod4.begin(WAVEFORM_SQUARE);

  waveform8.frequency(map(analogRead(A16), 0, 1023, 0, 5));

  float waveform2Amplitude = (float)analogRead(A17) / 1023.0;
  waveform8.amplitude(waveform2Amplitude);
  waveform8.begin(WAVEFORM_SINE);
}

void playNote0() {
  if (button0.risingEdge()) {
    Serial.println("Note Played");
    envelope1.attack(0);
    //envelope1.hold(0);
    envelope1.decay(0);
    envelope1.sustain(0.5);
    envelope1.release(3000);
    envelope1.noteOn();
    //add a short delay before shutting off the note
    delay(50);
    envelope1.noteOff();
  }
}
void playNote1() {
  if (button1.risingEdge()) {
    Serial.println("Note Played");
    envelope2.attack(0);
    //envelope1.hold(0);
    envelope2.decay(0);
    envelope2.sustain(0.5);
    envelope2.release(3000);
    envelope2.noteOn();
    //add a short delay before shutting off the note
    delay(50);
    envelope2.noteOff();
  }
}
void playNote2() {
  if (button2.risingEdge()) {
    Serial.println("Note Played");
    envelope3.attack(0);
    //envelope1.hold(0);
    envelope3.decay(0);
    envelope3.sustain(0.5);
    envelope3.release(3000);
    envelope3.noteOn();
    //add a short delay before shutting off the note
    delay(50);
    envelope3.noteOff();
  }
}
void playNote3() {
  if (button3.risingEdge()) {
    Serial.println("Note Played");
    envelope4.attack(0);
    //envelope1.hold(0);
    envelope4.decay(0);
    envelope4.sustain(0.5);
    envelope4.release(3000);
    envelope4.noteOn();
    //add a short delay before shutting off the note
    delay(50);
    envelope4.noteOff();
  }
}

void updateKnobs() {
  float modulatorFreq = map((float)analogRead(A14), 0, 1023, 100, 0.05);
  float fmModulatorAmp = analogRead(A15) / 1023.0;
  float filterLFOAmp = analogRead(A16) / 1023;
  float filterFrequencyCutoffFloat = analogRead(A17) / 1023;

  //voice1
  waveform1.frequency(modulatorFreq);
  waveform1.amplitude(fmModulatorAmp);
  Serial.println(fmModulatorAmp);
  //multuply by 5 to increase range from 0-5
  waveform2.frequency(filterFrequencyCutoffFloat * 5);
  waveform2.amplitude(1.0);

  //voice2
  waveform3.frequency(modulatorFreq);
  waveform3.amplitude(fmModulatorAmp);
  Serial.println(fmModulatorAmp);
  //multuply by 5 to increase range from 0-5
  waveform4.frequency(filterFrequencyCutoffFloat * 5);
  waveform4.amplitude(1.0);

  //voice3
  waveform5.frequency(modulatorFreq);
  waveform5.amplitude(fmModulatorAmp);
  Serial.println(fmModulatorAmp);
  //multuply by 5 to increase range from 0-5
  waveform6.frequency(filterFrequencyCutoffFloat * 5);
  waveform6.amplitude(1.0);

  //voice4
  waveform7.frequency(modulatorFreq);
  waveform7.amplitude(fmModulatorAmp);
  Serial.println(fmModulatorAmp);
  //multuply by 5 to increase range from 0-5
  waveform8.frequency(filterFrequencyCutoffFloat * 5);
  waveform8.amplitude(1.0);
}

void octaveCount() {
  if (button4.risingEdge()) {
    //if the button is pressed, add 1 to the index and then divide by the total 
    //number of indices in the array to calculate the remainder. Add 0ne afterwards so that we are always at 1 or above
    currentOctave = ((currentOctave + 1) % 4);

    //use AudioNoInterrupts() to pause the audio library and update the 4 waveforms all at the same time
    AudioNoInterrupts();
    //set the frequency based on the note position in the array, and octave setting. Add one to the octave setting to avoid hitting 0
    waveformMod1.frequency(cMajorScale[0] * (currentOctave + 1));
    waveformMod2.frequency(cMajorScale[2] * (currentOctave + 1));
    waveformMod3.frequency(cMajorScale[4] * (currentOctave + 1));
    waveformMod4.frequency(cMajorScale[6] * (currentOctave + 1));
    AudioInterrupts();
  }
}

