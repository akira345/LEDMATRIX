// modified by ikkei for Digit 32x16 dot matrix LED 2013.06.29
/*
  LED chika-chika for ikkeiplexing shield by ikkei
  http://blog.goo.ne.jp/jh3kxm
  
  History:
        2010-12-11 - V1.0 LED chika-chika by ikkei
 
*/

#include <MsTimer2.h>
#include <Digit32x16.h>

void setup()
{
  Digit32x16::Init();
}

void loop()
{
  static uint8_t x = 20;
  static uint8_t y = 6;
  static uint8_t s = 1;
  
  s ^= 1;
  Digit32x16::Set(x, y, s);
  delay(500);
}


