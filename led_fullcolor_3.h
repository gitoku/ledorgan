#ifndef led_fullcolor_9_h
#define led_fullcolor_9_h
#include "arduino.h"
#include "digiRW.h"



enum LedColor {
    RED = B001,
    GREEN = B010,
    BLUE = B100,
    CYAN = B110,
    YELLOW = B011,
    MAGENTA = B101,
    WHITE = B111,
    OFF = B000
};


namespace Led{
    LedColor color;
    byte state;
    const int cat_pins[]={3,10,11};
    const int ano_pins[]={7,5,6};
    
    //public
    void init();    //初期化
    void set(LedColor _color,byte _state);  //LEDを{color}色に設定
    void set(LedColor _color){color=_color;};
    void set(byte _state){state=_state;};
    void lighting();    //設定された状態に発光({interval}[ms]以内に定期的に呼び出しする必要あり)
    void lighting(LedColor _color,byte _state);
    void lighting(LedColor _color);
    void lighting(byte _state);
    //private
    void colorWrite(LedColor _color);    //アノード側LEDを{color}に設定して出力
    void ledWrite(byte on);    //カソード側LEDを{data}のどおり出力(ただしアノード側状態を{bit}で指定)
}

 void Led::init(){
    for(int i=0; i<3; i++){ 
        pinMode( cat_pins[i], OUTPUT);
        digiWrite(cat_pins[i],LOW);
    }
    for(int i=0; i<3; i++) pinMode( ano_pins[i], OUTPUT);

    set(OFF,B000);
}

void Led::set(LedColor _color,byte _state){
    color=_color;
    state = _state;
}

//色ごとのLEDのON/OFF出力(Anode:正論理)
void Led::colorWrite(LedColor color){
    digiWrite( ano_pins[0], color&RED);
    digiWrite( ano_pins[1], color&GREEN);
    digiWrite( ano_pins[2], color&BLUE);
}

//9個のLEDのON/OFF出力(Cathode:負論理)
void Led::ledWrite(byte on){
    digiWrite( cat_pins[2], !bitRead(on,0) );
    digiWrite( cat_pins[1], !bitRead(on,1) );
    digiWrite( cat_pins[0], !bitRead(on,2) );
}


void Led::lighting(){
    colorWrite(color);
    ledWrite(state);
}
void Led::lighting(LedColor _color,byte _state){
  set(_color,_state);
  lighting();
}

void Led::lighting(LedColor _color){
  set(_color);
  lighting();
}
void Led::lighting(byte _state){
  set(_state);
  lighting();
}

#endif
