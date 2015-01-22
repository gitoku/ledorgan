#include "playOrgan.h"


#define SWITCH_PIN 9
#define isPress() (!digitalRead(SWITCH_PIN))


void setup(){
    pinMode( SWITCH_PIN, INPUT_PULLUP); 
    analogReference(INTERNAL);
    randomSeed(analogRead(0));

    Touch::init();
    Led::init();
    Led::setInterval(3);
    
}


void loop(){

	//自由演奏モード
	while( !isPress() ) freePlay();
	while( isPress() );

	//お手本演奏モード
	while( !isPress() ) pointPlay();
	while( isPress() );

}

