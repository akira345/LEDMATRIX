// modified by ikkei for Digit 32x16 dot matrix LED 2013.06.29
/*
  Scroll text from serial I/F ( Type in Serial Monitor 57600 baud )
  for ikkeiplexing shield
  and 8x16duino Tichaino
  Copyright ikkei 2012.2.28
  
*/

#include <MsTimer2.h>
#include <Digit32x16.h>
#include "dFont.h"

void setup(){
  Digit32x16::Init();
  Serial.begin(57600);
}


void loop(){
  unsigned char text[128];

  int16_t x=0;
  uint8_t d;
  int a;
  int textsize = sizeof(text)/sizeof(text[0]);
  a = Serial.read();
  a = max(a,' ');
  d = dFont::Width(a);
  for(int i=0;i<=d;i++) {
    uint8_t data = dFont::Data(a,i);
    Digit32x16::Vwrite(31, data);
    delay(80);
    Digit32x16::ShiftLeft();
  }
}


