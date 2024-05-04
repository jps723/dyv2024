#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Bounce.h>

// GUItool: begin automatically generated code
AudioPlaySdWav playSdWav1;  //xy=703,428
AudioOutputI2S i2s1;        //xy=894,429
AudioConnection patchCord1(playSdWav1, 0, i2s1, 0);
AudioConnection patchCord2(playSdWav1, 1, i2s1, 1);
AudioControlSGTL5000 sgtl5000_1;  //xy=888,505
// GUItool: end automatically generated code

//// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN 10
#define SDCARD_MOSI_PIN 7
#define SDCARD_SCK_PIN 14

void setup() {
  // put your setup code here, to run once:
  AudioMemory(40);

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);

  //SDCard Initialise
  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    // stop here, but print a message repetitively
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
}

void loop() {
  //wav files must be 44100 sample rate, 16 or 8 bit
  if (!(playSdWav1.isPlaying())) {
    playSdWav1.play("nytrack.WAV");
    //playSdWav1.play("unfoldingMechanism_Vaetxh_libetTones.WAV");
   //playSdWav1.play("revans_Sora.WAV");
    //playSdWav1.play("piano.wav");
  }
}
