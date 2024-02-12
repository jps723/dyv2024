#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include <Bounce.h>


// GUItool: begin automatically generated code
AudioInputI2S i2s1;                //xy=294,347
AudioFilterStateVariable filter1;  //xy=493,345
AudioOutputI2S i2s2;               //xy=739,366
AudioConnection patchCord1(i2s1, 0, filter1, 0);
AudioConnection patchCord2(filter1, 0, i2s2, 0);
AudioConnection patchCord3(filter1, 0, i2s2, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=639,471
// GUItool: end automatically generated code


Bounce button0 = Bounce(36, 15);
Bounce button1 = Bounce(37, 15);
Bounce button2 = Bounce(29, 15);

const int lineInput = AUDIO_INPUT_LINEIN;
//const int myInput = AUDIO_INPUT_MIC;

void setup() {
  // put your setup code here, to run once:
  AudioMemory(40);
  //change to INPUT_PULLUP if not using external resistor

  pinMode(36, INPUT);
  pinMode(37, INPUT);
  pinMode(29, INPUT);

  // Enable the audio shield, select input, and enable output
  sgtl5000_1.enable();
  sgtl5000_1.inputSelect(lineInput);
  sgtl5000_1.adcHighPassFilterDisable();
  sgtl5000_1.volume(0.3);

  filter1.frequency(100);
}

void loop() {

  int frequencyCutoff = map(analogRead(A14), 0, 1023, 0, 6000);
  filter1.frequency(frequencyCutoff);

  //divide by 1023 to get values between 0.0 and 1.0
  // float delayedSignal = (float)analogRead(A16) / 1023;
  // float feedbackLevel = (float)analogRead(A17) / 1023;
  // int delayTime = map(analogRead(A15), 0, 1023, 0, 700);



  Serial.print("filter frequency cutoff: ");
  Serial.println(frequencyCutoff);
  // Serial.print("Delay Time: ");
  // Serial.println(delayTime);
  // Serial.print("Affected Level: ");
  // Serial.println(delayedSignal);
  // Serial.print("Feedback Level: ");
  // Serial.println(feedbackLevel);
}
