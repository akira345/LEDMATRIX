// modified by ikkei for Digit 32x16 dot matrix LED 2013.06.29
/*
  Font check ( display all charactors )
  for ikkeiplexing shield and 8x16duino Tichaino
  Copyright ikkei 2012.2.28
  
  
  
  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330,
  Boston, MA 02111-1307, USA.
*/

#include <MsTimer2.h>
#include <Digit32x16.h>
#include "dFont.h"

#define textnum 224 // ' ' to 0xFF
unsigned char text[textnum];

void setup(){
  Digit32x16::Init();
  for(int i=0; i<textnum; i++){
    text[i] = ' '+i;
  }
}


void loop(){
  int16_t x=0;
  uint8_t d;
  int textsize = sizeof(text)/sizeof(text[0]);
  for(int16_t j=0;j<textsize;j++) {
    d = dFont::Width(text[j]);
    for(int i=0;i<=d;i++) {
      uint8_t data = dFont::Data(text[j],i);
      Digit32x16::Vwrite(15, data);
      delay(100);
      Digit32x16::ShiftLeft();
    }  
  }
}


