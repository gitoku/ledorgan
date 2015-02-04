#ifndef touch_h
#define touch_h
#include "CapacitiveSensor.h"
#include "sounds.h"

#define CAP_THRESHOLD_LO 1000
#define CAP_THRESHOLD_HI 3000
#define CAPSENSE_SAMPLING 10

//#define CAP_THRESHOLD_LO 400
//#define CAP_THRESHOLD_HI 1000
//#define CAPSENSE_SAMPLING 3

#define CAP_THRESHOLD_SHORT 400
#define CAPSENSE_SAMPLING_SHORT 3
#define NOTONE (-1)

//note2~7:oct1~6s
const int note[6][12]={
    {NOTE_C2,NOTE_CS2,NOTE_D2,NOTE_DS2,NOTE_E2,NOTE_F2,NOTE_FS2,NOTE_G2,NOTE_GS2,NOTE_A2,NOTE_AS2,NOTE_B2},
    {NOTE_C3,NOTE_CS3,NOTE_D3,NOTE_DS3,NOTE_E3,NOTE_F3,NOTE_FS3,NOTE_G3,NOTE_GS3,NOTE_A3,NOTE_AS3,NOTE_B3},
    {NOTE_C4,NOTE_CS4,NOTE_D4,NOTE_DS4,NOTE_E4,NOTE_F4,NOTE_FS4,NOTE_G4,NOTE_GS4,NOTE_A4,NOTE_AS4,NOTE_B4},
    {NOTE_C5,NOTE_CS5,NOTE_D5,NOTE_DS5,NOTE_E5,NOTE_F5,NOTE_FS5,NOTE_G5,NOTE_GS5,NOTE_A5,NOTE_AS5,NOTE_B5},
    {NOTE_C6,NOTE_CS6,NOTE_D6,NOTE_DS6,NOTE_E6,NOTE_F6,NOTE_FS6,NOTE_G6,NOTE_GS6,NOTE_A6,NOTE_AS6,NOTE_B6},
    {NOTE_C7,NOTE_CS7,NOTE_D7,NOTE_DS7,NOTE_E7,NOTE_F7,NOTE_FS7,NOTE_G7,NOTE_GS7,NOTE_A7,NOTE_AS7,NOTE_B7}
};

enum key {
    KEY_NONE=0,
    KEY_C,
    KEY_CD,
    KEY_D,
    KEY_DE,
    KEY_E,
    KEY_F,
    KEY_FG,
    KEY_G,
    KEY_GA,
    KEY_A,
    KEY_AB,
    KEY_B,
    KEY_C8VA
};

key id2key(int id){
    switch(id){
        case 0:return KEY_C;
        case 1:return KEY_C;    //CS -> C
        case 2:return KEY_D;
        case 3:return KEY_D;    //DS -> D
        case 4:return KEY_E;
        case 5:return KEY_F;
        case 6:return KEY_F;    //FS -> F
        case 7:return KEY_G;
        case 8:return KEY_G;    //GS -> G
        case 9:return KEY_A;
        case 10:return KEY_A;   //AS -> A
        case 11:return KEY_B;
        default: return KEY_NONE;
    }
}

int key2id(key k){
    switch(k){
        case KEY_C:return 0;
        case KEY_CD:return 1;
        case KEY_D:return 2;
        case KEY_DE:return 3;
        case KEY_E:return 4;
        case KEY_F:return 5;
        case KEY_FG:return 6;
        case KEY_G:return 7;
        case KEY_GA:return 8;
        case KEY_A:return 9;
        case KEY_AB:return 10;
        case KEY_B:return 11;
        case KEY_C8VA:return 0;
        case KEY_NONE:return -1;
    }
}



key pat2key(byte pattern){
  switch(pattern){
    case B00000001: return KEY_C;
    case B00000011: return KEY_CD;
    case B00000010: return KEY_D;
    case B00000110: return KEY_DE;
    case B00000100: return KEY_E;
    case B00001100: return KEY_F;
    case B00001000: return KEY_F;
    case B00011000: return KEY_FG;
    case B00010000: return KEY_G;
    case B00110000: return KEY_GA;
    case B00100000: return KEY_A;
    case B01100000: return KEY_AB;
    case B01000000: return KEY_B;
    case B11000000: return KEY_B;
    case B10000000: return KEY_C8VA;
    default: return KEY_NONE;
  }
}


namespace Touch{
    const int touch_common_pin=4;
    const int touch_pins[]={19,18,17,16,15,14,13,12};
    const key pins2key[8]={KEY_C,KEY_D,KEY_E,KEY_F,KEY_G,KEY_A,KEY_B,KEY_C8VA};
    CapacitiveSensor cs[8];
    long value[8];

    void init();
    key get();
    key get10();
//    key get(int* o,int samp);
    key getplus(int* o,int samp);
    
}

void Touch::init(){
    for(int i=0;i<8;i++) cs[i].setPins(touch_common_pin,touch_pins[i]);
}




//しきい値を最も大きく超えたものを返す
//しきい値を超えたものがなければ0を返す
key Touch::get(){
  key touch = KEY_NONE;
  for(int i=0;i<8;i++){ 
        value[i]=cs[i].capacitiveSensor(CAPSENSE_SAMPLING_SHORT);
        if(value[i]>CAP_THRESHOLD_SHORT) touch = pins2key[i];
    }
    
    for(int i=0;i<8;i++){
       Serial.print(value[i]);
       Serial.print("\t");
    }
    Serial.print("\n");
    return touch;
}

key Touch::get10(){
  key touch = KEY_NONE;
  for(int i=0;i<8;i++){ 
        value[i]=cs[i].capacitiveSensor(CAPSENSE_SAMPLING);
        if(value[i]>CAP_THRESHOLD_LO) touch = pins2key[i];
    }
    
    for(int i=0;i<8;i++){
       Serial.print(value[i]);
       Serial.print("\t");
    }
    Serial.print("\n");
    return touch;
}

//key Touch::get(int* o,int samp){
// key touch = KEY_NONE;
// *o=0;
// for(int i=0;i<8;i++){ 
//       value[i]=cs[i].capacitiveSensor(samp);
//       Serial.print(value[i]);
//       Serial.print("\t");
//       if(value[i]>12000){ 
//           touch = pins2key[i];
//           *o=1;
//       }
//       else if(value[i]>8000) touch = pins2key[i];
//   }
//   Serial.print("\n");
//   return touch;
//       
//}


key Touch::getplus(int* o,int samp){
  byte touchH=0,touchL=0;
  *o=0;
  for(int i=0;i<8;i++){ 
    value[i]=cs[i].capacitiveSensor(CAPSENSE_SAMPLING);
        if(value[i]>CAP_THRESHOLD_HI) bitWrite(touchH,i,HIGH);
        if(value[i]>CAP_THRESHOLD_LO) bitWrite(touchL,i,HIGH);
    }
    for(int i=0;i<8;i++){
       Serial.print(value[i]);
       Serial.print("\t");
    }
    Serial.print("\n");
//    Serial.print(touchH,BIN);
//    Serial.print("\t");
//    Serial.print(touchL,BIN);
//    Serial.print("\n");
    key h = pat2key(touchH);
    key l = pat2key(touchL);
    
    if(h==KEY_NONE) return l;
    else {
      *o=1;
      return h;
    }
}

//0:none
//1~8:noteaddr
int note2oct(int note){
    int oct=0;
    if(note > 1) oct++; 
    if(note > 62) oct++;
    if(note > 123) oct++;
    if(note > 247) oct++;
    if(note > 494) oct++;
    if(note > 88) oct++;
    if(note > 1976) oct++;
    if(note > 3951) oct++;
    return oct;
}

int note2addr(int n){
    for(int i=0;i<72;i++) if(n == *(&note[0][0]+i)) return i;
    return NOTONE;
}



#endif
