// modified by ikkei for Digit 32x16 dot matrix LED 2013.06.29
/*
  reflection for ikkeiplexing shield by ikkei
  http://blog.goo.ne.jp/jh3kxm
  
  History:
        2010-12-11 - V1.0 reflection skeleton ikkei
 
*/

#include <MsTimer2.h>
#include <Digit32x16.h>

const uint8_t X_MAX = 31;
const uint8_t Y_MAX = 15;

void setup(){
  Digit32x16::Init();
}

void loop(){
  static uint8_t x = 0;
  static uint8_t dx = 1;
  static uint8_t y = 0;
  static uint8_t dy = 1;
  static uint8_t s = 1;
  
  Digit32x16::Set(x, y, 0);
  x += dx;
  y += dy;
  Digit32x16::Set(x, y, 1);
  
  if ((x <= 0)||(x >= X_MAX)){
    dx = -dx;
  }
  if ((y <= 0)||(y >= Y_MAX)){
    dy = -dy;
  }
  delay(50);
}


