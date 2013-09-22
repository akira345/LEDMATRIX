// modified by ikkei for Digit 32x16 dot matrix LED 2013.06.29
/*** Flip Animation
 * by arms22 <http://arms22.blog91.fc2.com/>
 * 
 * Demonstrates the use of the Dots library
 * 
 */

#include <MsTimer2.h>
#include <Digit32x16.h>

const byte one[] = {
  B00000000,B00000000,
  B00000000,B00000000,
  B00000000,B00000000,
  B00000000,B00000000,
  B00000000,B01111000,
  B00000000,B11111100,
  B00000001,B11111110,
  B00000011,B11111110,
  B00000111,B11111111,
  B00001111,B11111111,
  B00001111,B11111111,
  B00011111,B11111110,
  B00111111,B11111110,
  B00111111,B11111100,
  B01111111,B11111000,
  B11111111,B11111000,
  B01111111,B11111000,
  B00111111,B11111100,
  B00111111,B11111110,
  B00011111,B11111110,
  B00001111,B11111111,
  B00001111,B11111111,
  B00000111,B11111111,
  B00000011,B11111110,
  B00000001,B11111110,
  B00000000,B11111100,
  B00000000,B01111000,
  B00000000,B00000000,
  B00000000,B00000000,
  B00000000,B00000000,
  B00000000,B00000000,
  B00000000,B00000000,
};

const byte two[] = {
  B00000000,B00000000,
  B00000000,B00000000,
  B00000000,B00000000,
  B00000000,B00000000,
  B00000000,B00000000,
  B00000000,B00000000,
  B00000000,B00000000,
  B00000000,B01110000,
  B00000000,B11111000,
  B00000001,B11111100,
  B00000011,B11111100,
  B00000111,B11111100,
  B00001111,B11111100,
  B00001111,B11111000,
  B00011111,B11110000,
  B00111111,B11110000,
  B00011111,B11110000,
  B00001111,B11111000,
  B00001111,B11111100,
  B00000111,B11111100,
  B00000011,B11111100,
  B00000001,B11111100,
  B00000000,B11111000,
  B00000000,B01110000,
  B00000000,B00000000,
  B00000000,B00000000,
  B00000000,B00000000,
  B00000000,B00000000,
  B00000000,B00000000,
  B00000000,B00000000,
  B00000000,B00000000,
  B00000000,B00000000,
};

void setup(){
  Digit32x16::Init();
}

void loop(){
  Digit32x16::write90(0, two, 64);
  delay(750);
  
  Digit32x16::write90(0, one, 64);
  delay(750);
}

