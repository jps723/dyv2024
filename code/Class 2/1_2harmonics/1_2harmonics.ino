#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

//include the Bounce library for debouncing without delay
#include <Bounce.h>

// GUItool: begin automatically generated code
AudioSynthWaveform       waveform3;      //xy=140,384
AudioSynthWaveform       waveform1;      //xy=141,271
AudioSynthWaveform       waveform2;      //xy=141,324
AudioSynthWaveform       waveform4;      //xy=144,444
AudioMixer4              mixer1;         //xy=396,319
AudioOutputI2S           i2s1;           //xy=617,313
AudioConnection          patchCord1(waveform3, 0, mixer1, 2);
AudioConnection          patchCord2(waveform1, 0, mixer1, 0);
AudioConnection          patchCord3(waveform2, 0, mixer1, 1);
AudioConnection          patchCord4(waveform4, 0, mixer1, 3);
AudioConnection          patchCord5(mixer1, 0, i2s1, 0);
AudioConnection          patchCord6(mixer1, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=619,381
// GUItool: end automatically generated code


Bounce waveCycleButton = Bounce(36, 15);

float amp = 1.0;
int freq = 55;


//we'll use this variable to cycle between waveform types with a button
int currentWaveform = 0;

void setup() {
  Serial.begin(9600);
  AudioMemory(10);
  pinMode(36, INPUT);

  sgtl5000_1.enable();
  sgtl5000_1.volume(.5);

  currentWaveform = WAVEFORM_TRIANGLE;

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

  //read the pot positions and convert to a floating point b/w 0.0 and 1.0
  float channel1Gain = (float)analogRead(A14) / 1023;
  float channel2Gain = (float)analogRead(A15) / 1023;
  float channel3Gain = (float)analogRead(A16) / 1023;
  float channel4Gain = (float)analogRead(A17) / 1023;

  //set the gain on the mixer of each channel based on the pot readings
  mixer1.gain(0, channel1Gain);
  mixer1.gain(1, channel2Gain);
  mixer1.gain(2, channel3Gain);
  mixer1.gain(3, channel4Gain);


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
    waveform2.begin(currentWaveform);
    waveform3.begin(currentWaveform);
    waveform4.begin(currentWaveform);
    AudioInterrupts();

  }
}
