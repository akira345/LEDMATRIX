// modified by ikkei for Digit 32x16 dot matrix LED 2013.06.29
/*
  Scroll text 
  for ikkeiplexing shield
  and 8x16duino Tichaino
  Copyright ikkei 2012.2.29
  
*/

#include <MsTimer2.h>
#include <Digit32x16.h>
#include "dFont.h"


void setup(){
  Digit32x16::Init();
}



void loop(){
  const unsigned char text[]="Hello world!  \xCA\xDB\xB0\xDC\xB0\xD9\xC4\xDE! \xEA\xFB\xB0\xFC\xB0\xF9\xE4\xDE! \x81\x83\x84\x80   ";
  //const unsigned char text[]="\xE1\x8F\xE1\x8C\x92\xB0\xE9 "; // Tichaino

  uint8_t d;
  int textsize = sizeof(text)/sizeof(text[0]);
  for(int16_t j=0;j<textsize;j++) {
    d = dFont::Width(text[j]);
    for(int i=0;i<=d;i++) {
      uint8_t data = dFont::Data(text[j],i);
      Digit32x16::Vwrite(31, data);
      delay(80);
      Digit32x16::ShiftLeft();
    }  
  }
}

