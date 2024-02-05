#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

//include the Bounce library for debouncing without delay
#include <Bounce.h>

// GUItool: begin automatically generated code
AudioSynthWaveform waveform3;   //xy=199,457
AudioSynthWaveform waveform1;   //xy=200,344
AudioSynthWaveform waveform2;   //xy=200,397
AudioSynthWaveform waveform4;   //xy=203,517
AudioMixer4 mixer1;             //xy=410,420
AudioEffectEnvelope envelope1;  //xy=552,419
AudioOutputI2S i2s1;            //xy=879,393
AudioConnection patchCord1(waveform3, 0, mixer1, 2);
AudioConnection patchCord2(waveform1, 0, mixer1, 0);
AudioConnection patchCord3(waveform2, 0, mixer1, 1);
AudioConnection patchCord4(waveform4, 0, mixer1, 3);
AudioConnection patchCord5(mixer1, envelope1);
AudioConnection patchCord6(envelope1, 0, i2s1, 0);
AudioConnection patchCord7(envelope1, 0, i2s1, 1);
AudioControlSGTL5000 sgtl5000_1;  //xy=881,461
// GUItool: end automatically generated code

Bounce waveCycleButton = Bounce(36, 15);
Bounce envelopeTrigger = Bounce(37, 15);

float amp = 1.0;
int freq = 220;

int attackInMilliseconds = 0;
int decayInMilliseconds = 0;
float sustainInAmplitude = 0.0;
int releaseInMilliseconds = 0;

//Store the waveform types in an array
int waveTypes[5] = { WAVEFORM_SINE, WAVEFORM_PULSE, WAVEFORM_TRIANGLE, WAVEFORM_SAWTOOTH, WAVEFORM_SQUARE };
//a variable for shifting the position within the array
int currentWaveformIndex = 0;


void setup() {
  Serial.begin(9600);
  AudioMemory(10);
  pinMode(36, INPUT);
  pinMode(37, INPUT);

  sgtl5000_1.enable();
  sgtl5000_1.volume(.5);

  //waveform1 setup
  waveform1.frequency(freq);
  waveform1.amplitude(amp);
  waveform1.begin(WAVEFORM_SINE);

  //waveform2 setup, 1 octave lower than than waveform1
  waveform2.frequency(freq * 2);
  waveform2.amplitude(amp);
  waveform2.begin(WAVEFORM_TRIANGLE);

  //waveform3 setup, 2 octaves lower than than waveform1
  waveform3.frequency(freq * 3);
  waveform3.amplitude(amp);
  waveform3.begin(WAVEFORM_SINE);

  //waveform4 setup, 3 octaves lower than than waveform1
  waveform4.frequency(freq * 4);
  waveform4.amplitude(amp);
  waveform4.begin(WAVEFORM_SAWTOOTH);

  mixer1.gain(0, .25);
  mixer1.gain(1, .25);
  mixer1.gain(2, .25);
  mixer1.gain(3, .25);
}

void loop() {
  waveCycleButton.update();
  envelopeTrigger.update();

  //read the pot positions and convert to a floating point b/w 0.0 and 1.0
  attackInMilliseconds = map(analogRead(A17), 0, 1023, 0, 7500) - 180;
  decayInMilliseconds = map(analogRead(A16), 0, 1023, 0, 10000);
  sustainInAmplitude = (float)analogRead(A15) / 1023;
  releaseInMilliseconds = map(analogRead(A14), 0, 1023, 0, 10000);

  Serial.println(attackInMilliseconds);

  playNote();

  //if the button is pressed, move to the next waveform in the list
  if (waveCycleButton.fallingEdge()) {
    //if the button is pressed, add 1 to the index and then divide by the total number of indices in the array to calculate the remainder
    currentWaveformIndex = (currentWaveformIndex + 1) % 5;
    //use AudioNoInterrupts() to pause the audio library and update the 4 waveforms all at the same time
    AudioNoInterrupts();
    waveform1.begin(waveTypes[currentWaveformIndex]);
    waveform2.begin(waveTypes[currentWaveformIndex]);
    waveform3.begin(waveTypes[currentWaveformIndex]);
    waveform4.begin(waveTypes[currentWaveformIndex]);
    AudioInterrupts();
  }
}

void playNote() {
  if (envelopeTrigger.risingEdge()) {
    envelope1.attack(attackInMilliseconds);
    envelope1.decay(decayInMilliseconds);
    envelope1.sustain(sustainInAmplitude);
    envelope1.release(releaseInMilliseconds);
    envelope1.noteOn();
  }
  if (envelopeTrigger.fallingEdge()) {
    Serial.println("Note Down");
    envelope1.noteOff();
  }
}
