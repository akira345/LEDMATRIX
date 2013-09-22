
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
uint16_t kanji[16];
uint16_t buf[16];
unsigned int start_flg=0;
unsigned int len = 16;
unsigned int cnt =0;
void setup() {
  // put your setup code here, to run once:
  Digit32x16::Init();
  Serial.begin(9600);
  for(unsigned int i=0;i<len;i++){
    buf[i]=0x0000;
    kanji[i]=0xffff;
  } 
  pinMode(LED_PIN,OUTPUT);
}

void display_led(){
  digitalWrite(LED_PIN,LOW);  
  for(int j=0; j < len; j+=16) {
    for(unsigned int x=0;x<16;x++){
      for(unsigned int y=0;y<16;y++){
        unsigned int wk = kanji[j+y];
        Digit32x16::Set(31,y,bitRead(wk,15-x));//縦16bit分
      }
      delay(60);
      Digit32x16::ShiftLeft();
    }
  }
  digitalWrite(LED_PIN,HIGH);

}
void copy_display(){
  for(unsigned int i=0;i<len;i++){  
    kanji[i] = buf[i];
  }
  display_led();
}
void loop() {
  // put your main code here, to run repeatedly:
  //シリアルバッファにデータが有れば取り込む
  while(Serial.available()>1){
    if (cnt>len){
      cnt = 0;
      start_flg=1;
      copy_display();
    } 

    unsigned int high_bit=Serial.read();//上位8bit
    unsigned int low_bit =Serial.read();//下位8bit
    buf[cnt]=(high_bit<<8)+low_bit;//16bitに組み立て
    cnt ++;
  }
  //初回以外は、バッファにたまっているデータを表示し続ける
  if (start_flg){
    display_led(); 
  }
} 





