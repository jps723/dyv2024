#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Bounce.h>

// GUItool: begin automatically generated code
AudioPlaySdWav playSdWav4;  //xy=206,491
AudioPlaySdWav playSdWav3;  //xy=208,451
AudioPlaySdWav playSdWav1;  //xy=210,368
AudioPlaySdWav playSdWav2;  //xy=210,410
AudioMixer4 mixer1;         //xy=405,427
AudioOutputI2S i2s1;        //xy=559,429
AudioConnection patchCord1(playSdWav4, 0, mixer1, 3);
AudioConnection patchCord2(playSdWav3, 0, mixer1, 2);
AudioConnection patchCord3(playSdWav1, 0, mixer1, 0);
AudioConnection patchCord4(playSdWav2, 0, mixer1, 1);
AudioConnection patchCord5(mixer1, 0, i2s1, 0);
AudioConnection patchCord6(mixer1, 0, i2s1, 1);
AudioControlSGTL5000 sgtl5000_1;  //xy=786,381
// GUItool: end automatically generated code


// Use these with the Teensy Audio Shield
#define SDCARD_CS_PIN 10
#define SDCARD_MOSI_PIN 7  // Teensy 4 ignores this, uses pin 11
#define SDCARD_SCK_PIN 14  // Teensy 4 ignores this, uses pin 13

// Create the bounce objects for the buttons
Bounce button0 = Bounce(29, 15);
Bounce button1 = Bounce(30, 15);
Bounce button2 = Bounce(36, 15);
Bounce button3 = Bounce(37, 15);

void setup() {
  Serial.begin(9600);
  AudioMemory(20);

  pinMode(29, INPUT);
  pinMode(30, INPUT);
  pinMode(36, INPUT);
  pinMode(37, INPUT);

  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);

  mixer1.gain(1, 0.5);
  mixer1.gain(2, 0.5);
  mixer1.gain(3, 0.5);
  mixer1.gain(4, 0.5);

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
  button0.update();
  button1.update();
  button2.update();
  button3.update();

  float gain1 = (float)analogRead(A14) / 1023;
  float gain2 = (float)analogRead(A15) / 1023;
  float gain3 = (float)analogRead(A16) / 1023;
  float gain4 = (float)analogRead(A17) / 1023;

Serial.println(gain1);

  mixer1.gain(1, gain1);
  mixer1.gain(2, gain2);
  mixer1.gain(3, gain3);
  mixer1.gain(4, gain4);

  if (button0.fallingEdge()) {
    playSample1("birdacalls.WAV");
  }
  if (button1.fallingEdge()) {
    playSample2("poolsounds.WAV");
  }
  if (button2.fallingEdge()) {
    playSample3("roadsideDrone.WAV");
  }
  if (button3.fallingEdge()) {
    playSample4("waterDrip.WAV");
  }
}
void playSample1(const char *filename) {
  Serial.print("Playing file: ");
  Serial.println(filename);
  playSdWav1.play(filename);
  delay(25);
}

void playSample2(const char *filename) {
  Serial.print("Playing file: ");
  Serial.println(filename);
  playSdWav2.play(filename);
  delay(25);
}
void playSample3(const char *filename) {
  Serial.print("Playing file: ");
  Serial.println(filename);
  playSdWav3.play(filename);
  delay(25);
}
void playSample4(const char *filename) {
  Serial.print("Playing file: ");
  Serial.println(filename);
  playSdWav4.play(filename);
  delay(25);
}