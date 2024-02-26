#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>

// WAV files converted to code by wav2sketch
#include "AudioSampleKick.h"
 #include "AudioSampleSnare.h"
 #include "AudioSampleHihat.h"
 #include "AudioSampleBlip.h"

// GUItool: begin automatically generated code
AudioPlayMemory sample2;  //xy=335,309
AudioPlayMemory sample1;  //xy=337,265
AudioPlayMemory sample3;  //xy=337,352
AudioPlayMemory sample4;  //xy=337,394
AudioMixer4 mixer;        //xy=511,345
AudioOutputI2S i2s1;      //xy=666,344
AudioConnection patchCord1(sample2, 0, mixer, 1);
AudioConnection patchCord2(sample1, 0, mixer, 0);
AudioConnection patchCord3(sample3, 0, mixer, 2);
AudioConnection patchCord4(sample4, 0, mixer, 3);
AudioConnection patchCord5(mixer, 0, i2s1, 0);
AudioConnection patchCord6(mixer, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=683,420
// GUItool: end automatically generated code

// Create the bounce objects for the buttons
Bounce button0 = Bounce(29, 15);
Bounce button1 = Bounce(30, 15);
Bounce button2 = Bounce(36, 15);
Bounce button3 = Bounce(37, 15);

void setup() {
  pinMode(29, INPUT);
  pinMode(30, INPUT);
  pinMode(36, INPUT);
  pinMode(37, INPUT);

  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(50);

  // turn on the output
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);

  mixer.gain(1, 0.5);
  mixer.gain(2, 0.5);
  mixer.gain(3, 0.5);
  mixer.gain(4, 0.5);
}

void loop() {
  // Update all the button objects
  button0.update();
  button1.update();
  button2.update();
  button3.update();

  // When the buttons are pressed, just start a sound playing.
  // The audio library will play each sound through the mixers
  // so any combination can play simultaneously.
  //
  if (button0.fallingEdge()) {
    sample1.play(AudioSampleKick);
  }
  if (button1.fallingEdge()) {
    sample2.play(AudioSampleSnare);
  }
  if (button2.fallingEdge()) {
    sample3.play(AudioSampleHihat);
  }
  if (button3.fallingEdge()) {
    sample4.play(AudioSampleBlip);
  }
}
