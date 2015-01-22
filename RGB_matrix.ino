#include "sounds.h"
#include "pattern.h"


void setup(){
    pinMode( SWITCH_PIN, INPUT_PULLUP); 
    analogReference(INTERNAL);
    randomSeed(analogRead(0));

    Led::init();
    Led::setInterval(3);
    
}


void loop(){
  melody.setMelody(letitgo_Melody,letitgo_Duration,letitgo_Length);
  playPattern(patternFlushPoint,allcolor);

melody.setMelody(merrychristmas_Melody,merrychristmas_Duration,merrychristmas_Length);
playPattern(patternFlushC,allcolor);

melody.setMelody(bell_Melody,bell_Duration,bell_Length);
playPattern(patternFlushPointSlow,allcolor);

melody.setMelody(senbonzakura_Melody,senbonzakura_Duration,senbonzakura_Length);
playPattern(patternFlushTurn,allcolor);

melody.setMelody(ninjaribanban_Melody,ninjaribanban_Duration,ninjaribanban_Length);
playPattern(patternPitch2Color,allcolor);

melody.setMelody(ninjaribanban_Melody,ninjaribanban_Duration,ninjaribanban_Length);
playPattern(patternPitch2Color,allcolor);

melody.setMelody(rpg_Melody,rpg_Duration,rpg_Length);
playPattern(patternRandom3,allcolor);

melody.setMelody(wakeup_Melody,wakeup_Duration,wakeup_Length);
playPattern(patternRandom3Blink,allcolor);

melody.setMelody(oboroduki_Melody,oboroduki_Duration,oboroduki_Length);
playPattern(patternFlushPoint,allcolor);

melody.setMelody(hakonehachiri_Melody,hakonehachiri_Duration,hakonehachiri_Length);
playPattern(patternFlushC,allcolor);


}

