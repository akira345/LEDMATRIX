
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
uint16_t kanji[64];//ドット表示バッファ。16の整数倍を指定
uint16_t buff[64];
unsigned int len = 64;
unsigned int cnt = 0;
bool ret;
void setup() {
  // put your setup code here, to run once:
  Digit32x16::Init();
  Serial.begin(57600);
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
      if (buffer_full() || Serial.available()==0){
        delay(30);
      }
      else{
          delay(10);
        get_data(25);
      }
      Digit32x16::ShiftLeft();//出力したデータ全体を左に1bitシフトする
    }
  }
  digitalWrite(LED_PIN,LOW);
}
bool buffer_full(){
  if (cnt>len-1){
    return 1;
  } 
  else{
    return 0; 
  }

}
void get_data(unsigned int n){
  //シリアルバッファにデータが有れば取り込む
  unsigned int c;
  if(buffer_full()==0){
    if (Serial.available()>0){
      if (n==0){
        c=len;
      }
      for(unsigned int i=0;i<c;++i){
        if(buffer_full() || Serial.available()==0){
          break;
        }
        //シリアルデータがら上位8bit,下位8bitを取得し、16bitのデータを組み立てる
        unsigned int high_bit=Serial.read();//上位8bit
        Serial.write(high_bit);
        while(Serial.available()==0){
          //wait
        }
        unsigned int low_bit =Serial.read();//下位8bit
        Serial.write(low_bit);
        //delay(1);
        buff[cnt]=(high_bit<<8)+low_bit;//16bitに組み立て
        cnt ++;
      }
    }
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  get_data(0);
  if (buffer_full()){
    for (unsigned int i=0;i<len;i++){
      kanji[i]=buff[i];
    } 
    cnt=0;
    display_led();
  }
} 






