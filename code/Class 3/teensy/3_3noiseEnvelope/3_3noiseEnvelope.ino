#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Bounce.h>


// GUItool: begin automatically generated code
AudioSynthNoiseWhite noise1;    //xy=278,317
AudioEffectEnvelope envelope1;  //xy=444,320
AudioOutputI2S i2s1;            //xy=664,313
AudioConnection patchCord1(noise1, envelope1);
AudioConnection patchCord2(envelope1, 0, i2s1, 0);
AudioConnection patchCord3(envelope1, 0, i2s1, 1);
AudioControlSGTL5000 sgtl5000_1;  //xy=671,258
// GUItool: end automatically generated code


float amp = 0.5;
int freq = 440;
int angle = 180;

// Bounce objects to read pushbuttons
Bounce noiseBurst = Bounce(36, 15);
Bounce noiseSwell = Bounce(37, 15);  // 15 ms debounce time
Bounce clickPop = Bounce(29, 15);
Bounce harshBurst = Bounce(30, 15);


void setup() {
  pinMode(36, INPUT);
  pinMode(37, INPUT);
  pinMode(29, INPUT);
  pinMode(30, INPUT);
  Serial.begin(9600);
  AudioMemory(10);
  sgtl5000_1.enable();
  sgtl5000_1.volume(.6);

  noise1.amplitude(amp);
}

void loop() {
  // Update all the button objects
  noiseBurst.update();
  noiseSwell.update();
  clickPop.update();
  harshBurst.update();

  triggerNoiseBurst();
  triggerNoiseSwell();
  triggerClickPop();
  triggerHarshBurst();
}

void triggerNoiseBurst() {
  if (noiseBurst.risingEdge()) {
    Serial.println("Hi Hat Triggered");
    float ampKnobValue = map((float)analogRead(A15), 0, 1023, 0, 1);
    noise1.amplitude(ampKnobValue);

    if (ampKnobValue != amp) {
      amp = ampKnobValue;
      noise1.amplitude(ampKnobValue);
    }

    //noise1.amplitude(ampKnobValue);
    envelope1.attack(0);
    //envelope1.hold(0);
    envelope1.decay(100);
    envelope1.sustain(0.0);
    envelope1.release(100);
    envelope1.noteOn();
    //add a short delay before shutting off the note
    delay(200);
    envelope1.noteOff();
  }
}


void triggerNoiseSwell() {
  if (noiseSwell.risingEdge()) {
    Serial.println("Noise Swell Triggered");
    noise1.amplitude(0);
    float ampKnobValue = map((float)analogRead(A15), 0, 1023, 0, 1);
    noise1.amplitude(ampKnobValue);
    if (ampKnobValue != amp) {
      amp = ampKnobValue;
      noise1.amplitude(ampKnobValue);
    }
    envelope1.attack(5000);
    envelope1.hold(0);
    envelope1.decay(1000);
    envelope1.sustain(0.5);
    envelope1.release(5000);
    envelope1.noteOn();
    //For the above envelope settings to work properly,
    //the delay time below must be longer than the attack, hold, and decay.
    //We need to allow these phases to execute before calling
    //noteOff() which immediately triggers the release phase
    delay(6000);
    envelope1.noteOff();
  }
}

void triggerClickPop() {
  if (clickPop.risingEdge()) {
    Serial.println("Click Pop Triggered");
    int val = random(100);
    float newVal = (float)val / 100;
    Serial.println(newVal);
    noise1.amplitude(newVal);
    envelope1.attack(0);
    //envelope1.hold(0);
    envelope1.decay(0);
    envelope1.sustain(0.0);
    envelope1.release(250);
    envelope1.noteOn();
    //add a short delay before shutting off the note
    delay(10);
    envelope1.noteOff();
  }
}

void triggerHarshBurst() {
  if (harshBurst.risingEdge()) {
    Serial.println("Keyboard Key Triggered");
    float ampKnobValue = map((float)analogRead(A15), 0, 1023, 0, 1);
    noise1.amplitude(ampKnobValue);
    envelope1.attack(0);
    //envelope1.hold(0);
    envelope1.decay(450);
    envelope1.sustain(0.0);
    envelope1.release(10000);
    envelope1.noteOn();
    //add a short delay before shutting off the note
    if (harshBurst.fallingEdge()) {
      envelope1.noteOff();
      delay(450);
    }
  }
}
