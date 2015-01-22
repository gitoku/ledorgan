#ifndef touch_h
#define touch_h
#include <CapSense.h>

enum key {
    KEY_NONE,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_A,
    KEY_B,
    KEY_C8VA
};

namespace Touch{
    const int touch_common_pin=4;
    const int touch_pins[]={19,18,17,16,15,14,13,12};
    CapSense cs[8];

    void init();
    key get();
}

void Touch::init(){
    for(int i=0;i<8;i++){ 
        pinMode( touch_pins[i], OUTPUT);
        cs[i] = new CapSense(touch_common_pin,touch_pins[i]);
        cs[i].set_CS_AutocaL_Millis(0xFFFFFFFF);
    }
}

int Touch::get(){
    for(int i=0;i<8;i++){ 
        cs[0]+=cs_0.capSense(CAPSENSE_SAMPLING);
    }
    //しきい値を最も大きく超えたものを返す
    //しきい値を超えたものがなければ0を返す
    return KEY_NONE;
}

key note2key(int note){
    switch(note){
        //ラ
        case NOTE_A1:
        case NOTE_AS1:
        case NOTE_A2:
        case NOTE_AS2:
        case NOTE_A3:
        case NOTE_AS3:
        case NOTE_A4:
        case NOTE_AS4:
        case NOTE_A5:
        case NOTE_AS5:
        case NOTE_A6:
        case NOTE_AS6:
        case NOTE_A7:
        case NOTE_AS7:
            return KEY_A;

        //シ
        case NOTE_B1:
        case NOTE_B2:
        case NOTE_B3:
        case NOTE_B4:
        case NOTE_B5:
        case NOTE_B6:
        case NOTE_B7:
            return KEY_B;


        //ド
        case NOTE_C2:
        case NOTE_CS2:
        case NOTE_C3:
        case NOTE_CS3:
        case NOTE_C4:
        case NOTE_CS4:
        case NOTE_C5:
        case NOTE_CS5:
        case NOTE_C6:
        case NOTE_CS6:
        case NOTE_C7:
        case NOTE_CS7:
        case NOTE_C8:
        case NOTE_CS8:
            return KEY_C;

        //レ
        case NOTE_D2:
        case NOTE_DS2:
        case NOTE_D3:
        case NOTE_DS3:
        case NOTE_D4:
        case NOTE_DS4:
        case NOTE_D5:
        case NOTE_DS5:
        case NOTE_D6:
        case NOTE_DS6:
        case NOTE_D7:
        case NOTE_DS7:
        case NOTE_D8:
        case NOTE_DS8:
            return KEY_D;

        //ミ
        case NOTE_E2:
        case NOTE_E3:
        case NOTE_E4:
        case NOTE_E5:
        case NOTE_E6:
        case NOTE_E7:
            return KEY_E;

        //ファ
        case NOTE_F2:
        case NOTE_FS2:
        case NOTE_F3:
        case NOTE_FS3:
        case NOTE_F4:
        case NOTE_FS4:
        case NOTE_F5:
        case NOTE_FS5:
        case NOTE_F6:
        case NOTE_FS6:
        case NOTE_F7:
        case NOTE_FS7:
            return KEY_F;

        //ソ
        case NOTE_G2:
        case NOTE_GS2:
        case NOTE_G3:
        case NOTE_GS3:
        case NOTE_G4:
        case NOTE_GS4:
        case NOTE_G5:
        case NOTE_GS5:
        case NOTE_G6:
        case NOTE_GS6:
        case NOTE_G7:
        case NOTE_GS7:
            return KEY_G;


        //無音
        case NOTE_R:
            return KEY_NONE;
    }

}

#endif