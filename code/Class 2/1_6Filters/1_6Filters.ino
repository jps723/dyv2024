#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

//include the bounce library for debouncing without delay
#include <Bounce.h>

// GUItool: begin automatically generated code
AudioPlaySdWav playSdWav1;         //xy=207.66670989990234,281.3333320617676
AudioFilterStateVariable filter1;  //xy=406.66670989990234,253.33333206176758
AudioFilterStateVariable filter2;  //xy=406.66670989990234,313.3333320617676
AudioMixer4 mixer1;                //xy=600.6667098999023,249.33333206176758
AudioMixer4 mixer2;                //xy=602.6667098999023,330.3333320617676
AudioOutputI2S i2s1;               //xy=742.6667098999023,281.3333320617676
AudioConnection patchCord1(playSdWav1, 0, filter1, 0);
AudioConnection patchCord2(playSdWav1, 1, filter2, 0);
AudioConnection patchCord3(filter1, 0, mixer1, 0);
AudioConnection patchCord4(filter1, 1, mixer1, 1);
AudioConnection patchCord5(filter1, 2, mixer1, 2);
AudioConnection patchCord6(filter2, 0, mixer2, 0);
AudioConnection patchCord7(filter2, 1, mixer2, 1);
AudioConnection patchCord8(filter2, 2, mixer2, 2);
AudioConnection patchCord9(mixer1, 0, i2s1, 0);
AudioConnection patchCord10(mixer2, 0, i2s1, 1);
AudioControlSGTL5000 sgtl5000_1;  //xy=860.6667098999023,465.3333320617676
// GUItool: end automatically generated code

// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN 10
#define SDCARD_MOSI_PIN 7
#define SDCARD_SCK_PIN 14

// Bounce objects to read pushbuttons
Bounce button0 = Bounce(36, 15);
Bounce button1 = Bounce(37, 15);  // 15 ms debounce time
Bounce button2 = Bounce(29, 15);

void setup() {
  pinMode(29, INPUT);
  pinMode(36, INPUT);
  pinMode(37, INPUT);
  Serial.begin(9600);
  AudioMemory(12);

  //audio board setup
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.8);
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
  mixer1.gain(0, 0.0);
  mixer1.gain(1, 1.0);  // default to hearing band-pass signal
  mixer1.gain(2, 0.0);
  mixer1.gain(3, 0.0);
  mixer2.gain(0, 0.0);
  mixer2.gain(1, 1.0);
  mixer2.gain(2, 0.0);
  mixer2.gain(3, 0.0);
  delay(1000);
}

void loop() {
  if (playSdWav1.isPlaying() == false) {
    Serial.println("Start playing");
    playSdWav1.play("RhythmVariation7_aokiTakamasa_RV8.WAV");
    //playSdWav1.play("unfoldingMechanism_Vaetxh_libetTones.WAV");
    //playSdWav1.play("revans_Sora.WAV");

    delay(10);  // wait for library to parse WAV info
  }

  // Update all of the button objects
  button0.update();
  button1.update();
  button2.update();

  if (button0.fallingEdge()) {
    Serial.println("Low Pass Signal");
    mixer1.gain(0, 1.0);  // hear low-pass signal
    mixer1.gain(1, 0.0);
    mixer1.gain(2, 0.0);
    mixer2.gain(0, 1.0);
    mixer2.gain(1, 0.0);
    mixer2.gain(2, 0.0);
  }
  if (button1.fallingEdge()) {
    Serial.println("Band Pass Signal");
    mixer1.gain(0, 0.0);
    mixer1.gain(1, 1.0);  // hear low-pass signal
    mixer1.gain(2, 0.0);
    mixer2.gain(0, 0.0);
    mixer2.gain(1, 1.0);
    mixer2.gain(2, 0.0);
  }
  if (button2.fallingEdge()) {
    Serial.println("High Pass Signal");
    mixer1.gain(0, 0.0);
    mixer1.gain(1, 0.0);
    mixer1.gain(2, 1.0);  // hear low-pass signal
    mixer2.gain(0, 0.0);
    mixer2.gain(1, 0.0);
    mixer2.gain(2, 1.0);
  }

  // read the knob and adjust the filter frequency
  int frequencyCutoffKnob = analogRead(A14);
  // quick and dirty equation for exp scale frequency adjust
  float freq = expf((float)frequencyCutoffKnob / 150.0) * 10.0 + 80.0;

  filter1.frequency(freq);
  filter2.frequency(freq);
  Serial.print("frequency Cutoff = ");
  Serial.println(freq);
  delay(200);
}
