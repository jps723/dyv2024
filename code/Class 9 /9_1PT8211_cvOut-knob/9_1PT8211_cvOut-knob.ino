/*
   This is example code for interacting directly with a PT8211
   DAC over i2s. 

   It was originally written by github user @Dilshan and was
   accompanied by the blog post below. The pin definitions were
   changed to interface with a teensy 4.1.

   https://jayakody2000lk.blogspot.com/2019/08/verification-module-for-pt8211-dac.html

*/

#include <limits.h>
//change these if using a different i2s interface/board
#ifndef PIN_BCK
#define PIN_BCK   21
#endif
#ifndef PIN_WS
#define PIN_WS    20
#endif
#ifndef PIN_DIN
#define PIN_DIN   7
#endif

#define NOP __asm__ __volatile__ ("nop\n\t")

void writeDACChannel(short waveData) {
  unsigned char pos = 16;

  // Send data into PT8211 in least significant bit justified (LSBJ) format.
  while (pos > 0) {
    pos--;
    digitalWrite(PIN_BCK, LOW);
    // Write next bit in stream into DIN.
    digitalWrite(PIN_DIN, (waveData & (1 << pos)) ? HIGH : LOW);
    NOP;
    // Toggle BCK.
    digitalWrite(PIN_BCK, HIGH);
    NOP;
  }
}

void writeDAC(short waveData) {
  digitalWrite(PIN_WS, LOW);
  digitalWrite(PIN_BCK, LOW);
  // Write data into right channel of DAC.
  writeDACChannel(waveData);
  digitalWrite(PIN_WS, HIGH);
  // Write data into left channel of DAC.
  writeDACChannel(waveData);
}

void setup() {
  pinMode(PIN_BCK, OUTPUT);
  pinMode(PIN_WS, OUTPUT);
  pinMode(PIN_DIN, OUTPUT);
}

void loop() {
  //map a knob to the min/max values for the DAC 
    float val = map(analogRead(A16), 0, 1023, 5, 32767);
    //Write the knob position to the DAC for a constant voltage
    writeDAC(val);
  
}
