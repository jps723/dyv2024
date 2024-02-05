#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

//include the Bounce library for debouncing without delay
#include <Bounce.h>

// GUItool: begin automatically generated code
AudioSynthWaveform waveform3;      //xy=181,421
AudioSynthWaveform waveform1;      //xy=182,308
AudioSynthWaveform waveform2;      //xy=182,361
AudioSynthWaveform waveform4;      //xy=185,481
AudioMixer4 mixer1;                //xy=392,384
AudioSynthWaveform waveform5;      //xy=533,431
AudioEffectEnvelope envelope1;     //xy=534,383
AudioFilterStateVariable filter1;  //xy=719,386
AudioOutputI2S i2s1;               //xy=869,371
AudioConnection patchCord1(waveform3, 0, mixer1, 2);
AudioConnection patchCord2(waveform1, 0, mixer1, 0);
AudioConnection patchCord3(waveform2, 0, mixer1, 1);
AudioConnection patchCord4(waveform4, 0, mixer1, 3);
AudioConnection patchCord5(mixer1, envelope1);
AudioConnection patchCord6(waveform5, 0, filter1, 1);
AudioConnection patchCord7(envelope1, 0, filter1, 0);
AudioConnection patchCord8(filter1, 0, i2s1, 0);
AudioConnection patchCord9(filter1, 0, i2s1, 1);
AudioControlSGTL5000 sgtl5000_1;  //xy=877,440
// GUItool: end automatically generated code


//Create two bounce objects for our buttons. This makes their readings more stable/reliable
Bounce waveCycleButton = Bounce(36, 15);
Bounce envelopeTrigger = Bounce(37, 15);

//Variables for starting amplitude and frequencies for audible oscillators
float amp = 1.0;
int freq = 220;

//LFO variable
float lfoFrequency = 0.0;

//envelope variables
int attackInMilliseconds = 0;
int decayInMilliseconds = 0;
float sustainInAmplitude = 0.0;
int releaseInMilliseconds = 0;

//Store the waveform types in an array
int waveTypes[5] = {WAVEFORM_SINE, WAVEFORM_PULSE, WAVEFORM_TRIANGLE, WAVEFORM_SAWTOOTH, WAVEFORM_SQUARE};
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

  //this is our low frequency oscillator that will be applied to the filter frequency. We will not hear it.
  //It only influences the frequency cutoff point of the filter.
  waveform5.frequency(lfoFrequency);
  waveform5.amplitude(1);
  waveform5.begin(WAVEFORM_SINE);

//filter params -- the octave control is used to determine the full range that the filter will sweep
//if you hear white noise at the high end of your filter, lower the octave control
  filter1.octaveControl(3.5);
  filter1.resonance(5);

//equal mixer values for each of the 4 waveforms - do not exceed 1 or distortion will occur
  mixer1.gain(0, .25);
  mixer1.gain(1, .25);
  mixer1.gain(2, .25);
  mixer1.gain(3, .25);
}

void loop() {
  //check the buttons for updates
  waveCycleButton.update();
  envelopeTrigger.update();

  //resonance (Q) adjusts the shape of the cutoff curve - use values 0 to 5
  filter1.resonance(3);

  //read the pot position and convert to a floating point b/w 0.0 and 1.0, then multiply by 5 so that our effective range is from 0 to 5 as a float
  //the map function is for type int only
  lfoFrequency = (((float)analogRead(A17) / 1023) * 5);
  
  //remember, attack, decay, and release are measured in ms, where sustain is an amplitude value. Attack is hard coded as 0ms in this example
  decayInMilliseconds = map(analogRead(A16), 0, 1023, 0, 10000);
  sustainInAmplitude = (float)analogRead(A15) / 1023;
  releaseInMilliseconds = map(analogRead(A14), 0, 1023, 0, 10000);
  waveform5.frequency(lfoFrequency);

  Serial.println(lfoFrequency);

  playNote();

  if (waveCycleButton.fallingEdge()){
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

//A function that sets the parameters for our envelope and triggers it. 
void playNote() {
  if (envelopeTrigger.risingEdge()) {
    // waveform5.frequency(lfoFrequency);
    ///envelope1.attack(attackInMilliseconds);
    envelope1.decay(decayInMilliseconds);
    envelope1.sustain(sustainInAmplitude);
    envelope1.release(releaseInMilliseconds);
    envelope1.noteOn();
  }
  if (envelopeTrigger.fallingEdge()) {
    envelope1.noteOff();
  }
}
