// modified by ikkei for Digit 32x16 dot matrix LED 2013.06.29
/*
  Random fade 
  for ikkeiplexing shield
  and 8x16duino Tichaino
  Copyright ikkei 2012.2.29
  
*/

#include <MsTimer2.h>
#include <Digit32x16.h>

#define THMAX 20
#define SEEDMAX 10
#define WAIT 20
int th=0;
int dt=1;
byte state = 0;
byte cnt = WAIT;
int seed = 0;

const byte fig[] = {
  B00000000,B11100000,B00001110,B00000000,
  B00000011,B11111000,B00111111,B10000000,
  B00000111,B11111100,B01111111,B11000000,
  B00001111,B11111111,B11111111,B11100000,
  B00001111,B11111111,B11111111,B11100000,
  B00001111,B11111111,B11111111,B11100000,
  B00001111,B11111111,B11111111,B11100000,
  B00000111,B11111111,B11111111,B11000000,
  B00000011,B11111111,B11111111,B10000000,
  B00000001,B11111111,B11111111,B00000000,
  B00000000,B11111111,B11111110,B00000000,
  B00000000,B01111111,B11111100,B00000000,
  B00000000,B00011111,B11110000,B00000000,
  B00000000,B00001111,B11100000,B00000000,
  B00000000,B00000011,B10000000,B00000000,
  B00000000,B00000001,B00000000,B00000000,
};



void change_seed(){
  seed++;
  if (seed > SEEDMAX){
    seed = 0;
  }
}

void change_state(){
  switch (state){
    case 0:
      cnt--;
      if (cnt == 0){
        state = 1;
        change_seed();
      }
      break;
    case 1:
      th++;
      if (th > THMAX){
        state = 2;
        cnt = WAIT;
      }
      break;
    case 2:
      cnt--;
      if (cnt == 0){
        state = 3;
        change_seed();
      }
      break;
    case 3:
      th--;
      if (th == 0){
        state = 0;
        cnt = WAIT;
      }
      break;
  }
}

void setup(){
  Digit32x16::Init();
}


void loop(){ 
  change_state(); 
  randomSeed(seed); // seed == 0 : invalid
  for (byte y=0; y<16; y++){
    for (byte x=0; x<32; x++){
      Digit32x16::Set(x, y, bitRead(fig[y*4+x/8], 7-x%8) ^ (random(0,20) < th));
    }
  }
  delay(10);
}

