#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

//include the Bounce library for debouncing without delay
#include <Bounce.h>

// GUItool: begin automatically generated code
AudioInputI2S i2s1;             //xy=422,348
AudioEffectEnvelope envelope1;  //xy=553,344
AudioOutputI2S i2s2;            //xy=695,342
AudioConnection patchCord1(i2s1, 0, envelope1, 0);
AudioConnection patchCord2(envelope1, 0, i2s2, 0);
AudioConnection patchCord3(envelope1, 0, i2s2, 1);
AudioControlSGTL5000 sgtl5000_1;  //xy=810,503
// GUItool: end automatically generated code

Bounce envelopeTrigger = Bounce(37, 15);

const int lineInput = AUDIO_INPUT_LINEIN;
//const int myInput = AUDIO_INPUT_MIC;


int attackInMilliseconds = 0;
int decayInMilliseconds = 0;
float sustainInAmplitude = 0.0;
int releaseInMilliseconds = 0;

void setup() {
  Serial.begin(9600);
  AudioMemory(10);
  pinMode(37, INPUT);

  sgtl5000_1.enable();
  sgtl5000_1.volume(.5);
  sgtl5000_1.inputSelect(lineInput);
}

void loop() {
  envelopeTrigger.update();

  //read the pot positions and convert to a floating point b/w 0.0 and 1.0
  attackInMilliseconds = map(analogRead(A14), 0, 1023, 0, 7500) - 180;
  decayInMilliseconds = map(analogRead(A15), 0, 1023, 0, 10000);
  sustainInAmplitude = (float)analogRead(A16) / 1023;
  releaseInMilliseconds = map(analogRead(A17), 0, 1023, 0, 10000);

  Serial.println(attackInMilliseconds);

  playNote();
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
