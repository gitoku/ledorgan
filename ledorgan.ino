#include <EEPROM.h>
#include "led_fullcolor_3.h"
#include "touch.h"
#include "playMelodyStep.h"

#define HI_RESPONSE true

#define BUZZER_PIN 8
#define SWITCH_PIN 9
#define isPress() (!digitalRead(SWITCH_PIN))
#define MELODY_TEMPO 40

PlayMelodyStep melody(BUZZER_PIN);


void setup(){
    pinMode( SWITCH_PIN, INPUT_PULLUP); 
    randomSeed(analogRead(0));
    Touch::init();
    Led::init();
    
    
    byte song;
    song = EEPROM.read(0);
    if(isPress()){
      song++;
      song = song%6;
      EEPROM.write(0, song);
      for(int i=0;i<(song+1);i++){
		tone(BUZZER_PIN,NOTE_A6,125);
		delay(175);
      }
    }
    
    

    //曲の設定
    switch(song){
		case 0:
			melody.setMelody(haurunomaintame_Melody,haurunomaintame_Duration,haurunomaintame_Length);
			break;
		case 1:
			melody.setMelody(takibi_Melody,takibi_Duration,takibi_Length);
			break;
		case 2:
			melody.setMelody(rpg_Melody,rpg_Duration,rpg_Length);
			break;
		case 3:
			melody.setMelody(ninjaribanban_Melody,ninjaribanban_Duration,ninjaribanban_Length);
			break;
		case 4:
			melody.setMelody(senbonzakura_Melody,senbonzakura_Duration,senbonzakura_Length);
			break;
		case 5:
			melody.setMelody(letitgo_Melody,letitgo_Duration,letitgo_Length);
			break;
    }


    Serial.begin(115200);
    delay(500);
}


void loop(){
	//自由演奏モード
	buzz(WHITE,1);
	while( !isPress() ) freePlay();
	wait4Release();

	//早押しミッションモード
	buzz(RED,2);
	while( !isPress() ) missionSpeed();
	wait4Release();

	//記憶ミッションモード
	buzz(BLUE,2);
	while( !isPress() ) missionMemory();
	wait4Release();

	//デモ演奏
	buzz(GREEN,3);
	while( !isPress() ) autoPlay(melody);
	wait4Release();

	//ガイドつき演奏モード
	buzz(YELLOW,3);
	while( !isPress() ) modelPlay(melody);
	wait4Release();

}

void wait4Release(){
	Led::lighting(B000);
	tone(BUZZER_PIN,NOTE_C3,500);
	while( isPress() );
}

void buzz(LedColor color,int time){
	Led::lighting(color,B101);
	for(int i=0;i<time;i++){
		tone(BUZZER_PIN,NOTE_A4,100);
		delay(150);
	}
	delay(1000);
	Led::lighting(B000);
        delay(500);
}


//早押しミッションモード
void missionSpeed(){
	static unsigned long length = 4000;
	Led::lighting(OFF,B010);
	LedColor c=num2color(random(0,7));
	Led::lighting(c);
	unsigned long now = millis();
	tone(BUZZER_PIN,NOTE_C6,100);
	delay(500);

	while((millis()-now)<length){
		if( isPress() ) break;

		//タッチされているキーの取得
		key nowKey;

		if(HI_RESPONSE) nowKey = Touch::get();
		else nowKey = Touch::get10();

		if(key2color(nowKey)==c){
			Led::lighting(B111);
			tone(BUZZER_PIN,note[2][key2id(nowKey)],500);
			delay(700);
			noTone(BUZZER_PIN);
			length = length*97/100;
			break;
		}
		else if(nowKey!=KEY_NONE){ 
			Led::lighting(B000);
			tone(BUZZER_PIN,NOTE_A1,100);
			delay(300);
			Led::lighting(B010);
		}
	}
}


//記憶ミッションモード
const key num2key[8]={KEY_C,KEY_D,KEY_E,KEY_F,KEY_G,KEY_A,KEY_B,KEY_C8VA};
void missionMemory(){
	static unsigned int size = 2500;
	//gen color list
	Led::lighting(OFF,B001);
	key k[20];
	for(int i=0;i<20;i++) k[i]=num2key[random(0,8)];
	int len=size/1000;
	delay(500);

	//show color list
	for(int i=0;i<len;i++){
		if(isPress()) break;
		tone(BUZZER_PIN,note[2][key2id(k[i])],500);
		Led::lighting(key2color(k[i]),B111);
		delay(750);
		Led::lighting(B000);
		delay(100);
	}

	//to challenge color list question
	int cnt=0;
	int ecnt=0;
	while(1){
		if( isPress() ) break;
		delay(500);

		//タッチされているキーの取得
		key nowKey;
		if(HI_RESPONSE) nowKey = Touch::get();
		else nowKey = Touch::get10();

		Led::lighting(key2color(nowKey),B111);
		if(key2color(nowKey)==key2color(k[cnt])){
			tone(BUZZER_PIN,note[2][key2id(nowKey)],500);
			delay(750);
			cnt++;
			ecnt=0;
			Led::lighting(B000);
		}
		else if(nowKey!=KEY_NONE){ 
			tone(BUZZER_PIN,NOTE_A1,100);
			delay(300);
			Led::lighting(B000);
			ecnt++;
		}

		if(cnt==len){
			tone(BUZZER_PIN,NOTE_G5,300);
			delay(400);
			tone(BUZZER_PIN,NOTE_E5,400);
			delay(1300);
			size+=200;
			if(len>30000)len=30000;
			break;
		}


		if(ecnt>2){
			tone(BUZZER_PIN,NOTE_A1,100);
			delay(300);
			Led::lighting(B000);
			tone(BUZZER_PIN,NOTE_A1,300);
			delay(1300);
			Led::lighting(B000);
			size-=300;
			break;
		}
	}
}

//自由演奏モード
void freePlay(){
	Led::lighting(B111);

	//タッチされているキーの取得
	int oct=0;
	key nowKey = Touch::getplus(&oct,6);
	if(nowKey==KEY_C8VA) oct++;

//	Serial.println(nowKey);

	//キーに応じて音を鳴らす
	if(nowKey==KEY_NONE) noTone(BUZZER_PIN);
	else tone(BUZZER_PIN,note[2+oct][key2id(nowKey)]);

	//キーに応じてLEDを発光
	Led::lighting(key2color(nowKey));
}


//演奏できるようにLEDで指示
void modelPlay(PlayMelodyStep melody){
	// 曲が終わるかスイッチが押されるまで繰り返す
	Led::lighting(OFF);//消灯
	melody.next();
	while(melody.isPlaying()){
		if( isPress() ) break;
		noTone(BUZZER_PIN);

		//新たな再生音の取得
		int cAddr=0,cId=0,cOct=0;
		key cKey=KEY_NONE;
		int cNote = melody.getPitch();
		if(cNote!=NOTE_R){
			cAddr = note2addr(cNote);
			cId = cAddr%12;
			cOct = cAddr/12;
			cKey = id2key(cId);
		}
		else cKey=KEY_NONE;
		int leftTime = melody.getDuration()/MELODY_TEMPO;

		//押すべきキーをLEDで表示
		Led::lighting(key2color(cKey),B001);

		//押すべきキーが一定時間押されるまで待つ
		while(leftTime>0){
			if( isPress() ) break;

			//押しているキーを取得
			key k = Touch::get();
			int id = key2id(k);

			if(key2id(k)==key2id(cKey)){ 
				//キーに応じて音を鳴らす
				if(k==KEY_NONE) noTone(BUZZER_PIN);
				else tone(BUZZER_PIN,cNote);
				leftTime--; //押すべきキーが押されている時間をカウント
				Led::lighting(B111);
			}
			else{
				//キーに応じて音を鳴らす
				if(k==KEY_NONE) noTone(BUZZER_PIN);
				else tone(BUZZER_PIN,note[cOct][id]);
				Led::lighting(B001);
			}
		}

		//次の指示を行う前に，タッチセンサから手を離させる
		Led::lighting(OFF);
		key t = Touch::get();
		while(t!=KEY_NONE){ 
			t = Touch::get();
			if( isPress() ) break;
		}
		noTone(BUZZER_PIN);

		//次の音へ
		melody.next();
	}
}

//勝手に演奏
void autoPlay(PlayMelodyStep melody){
	// 曲が終わるかスイッチが押されるまで繰り返す
	melody.next();
	while(melody.isPlaying()){
		if( isPress() ) break;
		noTone(BUZZER_PIN);

		//新たな再生音の取得
		int cAddr=0,cId=0,cOct=0;
		key cKey=KEY_NONE;
		int cNote = melody.getPitch();
		if(cNote!=NOTE_R){
			cAddr = note2addr(cNote);
			cId = cAddr%12;
			cOct = cAddr/12;
			cKey = id2key(cId);
		}
		else cKey=KEY_NONE;
		int leftTime = melody.getDuration()/MELODY_TEMPO;

		//押すべきキーをLEDで表示
		Led::lighting(key2color(cKey),B001);

		//押すべきキーが一定時間押されるまで待つ
		while(leftTime>0){
			if( isPress() ) break;

			//押しているキーを取得
			key k = Touch::get();

			//キーを押してさえいれば再生
			if(k!=KEY_NONE){ 
				//キーに応じて音を鳴らす
				if(cKey==KEY_NONE) noTone(BUZZER_PIN);
				else tone(BUZZER_PIN,cNote);
				leftTime--; //キーが押されている時間をカウント
				Led::lighting(B111);
			}
			//押していなければ停止
			else{
				noTone(BUZZER_PIN);
				Led::lighting(B000);
			}
			
		}
		Led::lighting(OFF);
		key t = Touch::get();

		//次の音へ
		melody.next();
	}
}



LedColor key2color(key k){
	switch(k){
		case KEY_NONE:  
			return OFF;
		case KEY_C:
		case KEY_CD:
		case KEY_C8VA: 
			return RED;
		case KEY_D: 
		case KEY_DE: 
			return MAGENTA;
		case KEY_E: 
			return BLUE;
		case KEY_F: 
		case KEY_FG: 
			return GREEN;
		case KEY_G: 
		case KEY_GA: 
			return CYAN;
		case KEY_A: 
		case KEY_AB: 
			return YELLOW;
		case KEY_B: 
			return WHITE;
	}
}


LedColor num2color(int k){
	switch(k){
		case -1:  
			return OFF;
		case 0: 
			return RED;
		case 1: 
			return MAGENTA;
		case 2: 
			return BLUE;
		case 3: 
			return GREEN;
		case 4: 
			return CYAN;
		case 5: 
			return YELLOW;
		case 6: 
			return WHITE;
	}
}

//
//int key2note(key k){
//	switch(k){
//		case KEY_NONE:
//			return 0;
//		case KEY_C:
//			return NOTE_C4;
//		case KEY_D:
//			return NOTE_D4;
//		case KEY_E:
//			return NOTE_E4;
//		case KEY_F:
//			return NOTE_F4;
//		case KEY_G:
//			return NOTE_G4;
//		case KEY_A:
//			return NOTE_A4;
//		case KEY_B:
//			return NOTE_B4;
//		case KEY_C8VA:
//			return NOTE_C5;
//	}
//}
