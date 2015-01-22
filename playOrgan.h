#ifndef playorgan_h
#define playorgan_h
#include "led_fullcolor_3.h"
#include "touch.h"

#define BUZZER_PIN 8

void freePlay(){
    while(1){
        key nowKey = Touch::get();
        duration = 100;
        tone(BUZZER_PIN,key2note(nowKey),duration);
        Led::setAll( key2color(nowKey) );
        Led::lightingWhile(duration);
    }
}

void freePlay(){
    while(1){
        key now = Touch::get();
        duration = 100;
        tone(BUZZER_PIN,now,duration);
        delay(duration);
    }
}


LedColor key2color(key k){
    switch(k){
        case KEY_NONE:  
            return OFF;
        case KEY_C:
        case KEY_C8VA: 
            return MAGENTA;
        case KEY_D: 
            return RED;
        case KEY_E: 
            return BLUE;
        case KEY_F: 
            return GREEN;
        case KEY_G: 
            return CYAN;
        case KEY_A: 
            return YELLOW;
        case KEY_B: 
            return WHITE;
    }
}

int key2note(key k){
    case KEY_NONE:
        return 0;
    case KEY_C:
        return NOTE_C4;
    case KEY_D:
        return NOTE_D4;
    case KEY_E:
        return NOTE_E4;
    case KEY_F:
        return NOTE_F4;
    case KEY_G:
        return NOTE_G4;
    case KEY_A:
        return NOTE_A5;
    case KEY_B:
        return NOTE_B5;
    case KEY_C8VA:
        return NOTE_C5
}

#endif