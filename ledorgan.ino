#include "led_fullcolor_3.h"
#include "touch.h"
#include "playMelodyStep.h"

#define BUZZER_PIN 8
#define SWITCH_PIN 9
#define isPress() (!digitalRead(SWITCH_PIN))
#define MELODY_TEMPO 40

PlayMelodyStep melody(BUZZER_PIN);

void setup(){
    pinMode( SWITCH_PIN, INPUT_PULLUP); 
    Touch::init();
    Led::init();
}


void loop(){

	//自由演奏モード
	while( !isPress() ){
		Led::set(B111);
                
		//タッチされているキーの取得
		key nowKey = Touch::get();

		//キーに応じて音を鳴らす
		if(nowKey==KEY_NONE) noTone(BUZZER_PIN);
		else tone(BUZZER_PIN,key2note(nowKey));

		//キーに応じてLEDを発光
		Led::lighting(key2color(nowKey));
	}
	while( isPress() );


	//
	//[たきび]
	//
	//デモ演奏
	while( !isPress() ){
		//曲の設定
		melody.setMelody(takibi_Melody,takibi_Duration,takibi_Length);
		melody.next();
		autoPlay(melody);
	}while( isPress() );
	//演奏ガイド
	while( !isPress() ){
		//曲の設定
		melody.setMelody(takibi_Melody,takibi_Duration,takibi_Length);
		melody.next();
		modelPlay(melody);
	}while( isPress() );


	//
	//[Let It Go]
	//
	//デモ演奏
	while( !isPress() ){
		//曲の設定
		melody.setMelody(letitgo_Melody,letitgo_Duration,letitgo_Length);
		melody.next();
		autoPlay(melody);
	}while( isPress() );
	//演奏ガイド
	while( !isPress() ){
		//曲の設定
		melody.setMelody(letitgo_Melody,letitgo_Duration,letitgo_Length);
		melody.next();
		modelPlay(melody);
	}while( isPress() );


	//
	//[千本桜]
	//
	//デモ演奏
	while( !isPress() ){
		//曲の設定
		melody.setMelody(senbonzakura_Melody,senbonzakura_Duration,senbonzakura_Length);
		melody.next();
		autoPlay(melody);
	}while( isPress() );
	//演奏ガイド
	while( !isPress() ){
		//曲の設定
		melody.setMelody(senbonzakura_Melody,senbonzakura_Duration,senbonzakura_Length);
		melody.next();
		modelPlay(melody);
	}while( isPress() );


}


//演奏できるようにLEDで指示
void modelPlay(PlayMelodyStep melody){
	// 曲が終わるかスイッチが押されるまで繰り返す
	Led::lighting(OFF);//消灯
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
		case KEY_C8VA: 
			return RED;
		case KEY_D: 
			return MAGENTA;
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
	switch(k){
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
			return NOTE_A4;
		case KEY_B:
			return NOTE_B4;
		case KEY_C8VA:
			return NOTE_C5;
	}
}

