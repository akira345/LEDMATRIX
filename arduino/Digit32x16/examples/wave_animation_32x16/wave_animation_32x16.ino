// modified by ikkei for Digit 32x16 dot matrix LED 2013.06.30
/*** Wave Animation
 * by arms22 <http://arms22.blog91.fc2.com/>
 * 
 */

#include <MsTimer2.h>
#include <Digit32x16.h>

const unsigned int wave[] = {
  256*B00100000+B00000000,
  256*B00011100+B00000000,
  256*B00000011+B11000000,
  256*B00000000+B00111000,
  256*B00000000+B00000100,
  256*B00000000+B00000010,
  256*B00000000+B00000010,
  256*B00000000+B00000100,
  256*B00000000+B00111000,
  256*B00000011+B11000000,
  256*B00011100+B00000000,
  256*B00100000+B00000000,
  256*B01000000+B00000000,
  256*B01000000+B00000000,
};

void setup(){
  Digit32x16::Init();
}

int x = 0;
int len = sizeof(wave)/sizeof(wave[0]);

void loop(){
  for(int8_t j=0;j<len;j++) {
    Digit32x16::Vwrite(0, wave[j]);
    delay(80);
    Digit32x16::ShiftRight();
  }
}

