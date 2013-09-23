
// modified by ikkei for Digit 32x16 dot matrix LED 2013.06.29
/*
  LED chika-chika for ikkeiplexing shield by ikkei
 http://blog.goo.ne.jp/jh3kxm
 
 History:
 2010-12-11 - V1.0 LED chika-chika by ikkei
 
 */

#include <MsTimer2.h>
#include <Digit32x16.h>
#define LED_PIN 13
uint16_t kanji[32];//ドット表示バッファ。16の整数倍を指定
unsigned int len = 32;
unsigned int cnt = 0;
void setup() {
  // put your setup code here, to run once:
  Digit32x16::Init();
  Serial.begin(9600);
  pinMode(LED_PIN,OUTPUT);
}

void display_led(){
  digitalWrite(LED_PIN,HIGH);  
  for(int j=0; j < len; j+=16) {               //文字数分ループ
    for(unsigned int x=0;x<16;x++){            //横16bitループ
      for(unsigned int y=0;y<16;y++){          //縦16bitループ
        unsigned int wk = kanji[j+y];          //ドットデータ読み込み
        Digit32x16::Set(31,y,bitRead(wk,15-x));//縦1bit分送信。x座標は右端31固定
      }
      delay(37);
      Digit32x16::ShiftLeft();//出力したデータ全体を左に1bitシフトする
    }
  }
  digitalWrite(LED_PIN,LOW);
}
void loop() {
  // put your main code here, to run repeatedly:
  //シリアルバッファにデータが有れば取り込む
  while(Serial.available()>1){
  //16個取り込んだらLEDへ表示する
    if (cnt>len-1){
      cnt=0;
      display_led();
      //Serial.flush();
    } 
 //シリアルデータがら上位8bit,下位8bitを取得し、16bitのデータを組み立てる
    unsigned int high_bit=Serial.read();//上位8bit
    //Serial.write(high_bit);
    unsigned int low_bit =Serial.read();//下位8bit
    //Serial.write(low_bit);
    //delay(1);
    kanji[cnt]=(high_bit<<8)+low_bit;//16bitに組み立て
    cnt ++;
  }
} 





