#ifndef playmelodystep_h
#define playmelodystep_h

#include "arduino.h"
#include <avr/pgmspace.h> 

class PlayMelodyStep{
	public:
		PlayMelodyStep(){};
		void setMelody(int* _melodyArr,int* _durationArr,int _length);	//メロディーの設定
		int next();	//再生(戻り値[1:新しい音の出力][0:前回と同じ音を出力])
		void stop();	//停止、再び再生するときははじめから
		int getPosition();	//再生位置を返す
		int getPitch();	//再生中の音程を返す
		int getDuration();	//再生中の音の残り再生時間を返す
	private:
		int* melodyArr;
		int* durationArr;
		int length;
		int position;
		int nowSound;
		int nowDuration;
};


void PlayMelodyStep::setMelody(int* _melodyArr,int* _durationArr,int _length){
	melodyArr = _melodyArr;
	durationArr = _durationArr;
	length = _length;
	position = 0;
	nowSound = 0;
}



int PlayMelodyStep::next(){
	if( position > length+1 ) nowSound = 0;	//再生終了

	else{ 
		nowDuration = 1000/( pgm_read_word_near(durationArr+position) );
		nowSound = ( pgm_read_word_near(melodyArr+position) );
		position++;
		return 1;
	}
}


void PlayMelodyStep::stop(){
	nowSound = 0;
	position = 0;
}


int PlayMelodyStep::getPosition(){ return position; };
int PlayMelodyStep::getPitch(){ return nowSound; };
int PlayMelodyStep::getDuration(){ return nowDuration; };


#endif