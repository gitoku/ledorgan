LED Organ
==========

八頭ものづくり教室(第四回)スケッチ
------

![](reference/top.jpg)

### 概要
1. タッチセンサの鍵盤に触れると，対応した音がなり，対応した色で光る．
2. LEDの指示に合わせて鍵盤に触れると，曲の演奏ができる
3. 2.の曲のデモ演奏
4. 1~3の3つのモードをタクトスイッチで切り替えできる

#### (注意)
[RGB_matrix](https://github.com/gitoku/RGB_matrix)をもとに実装しているため，まわりくどいライブラリ・関数構成となっている．
余力があれば最適化する．もしくは誰かお願い．

#### デモ
次のモードがタクトスイッチ長押し(1秒程度)のたびに切り替わる

1. **自由演奏**：触れたセンサの音が再生され，対応する色にLEDが光る
2. **曲演奏デモ**(たきび)：いずれかのキーに触れていれば曲を再生する
2. **ガイド演奏**(たきび)：LEDが指示する色のセンサに触れれば，曲が再生される
2. **曲演奏デモ**(Let It Go)
2. **ガイド演奏**(Let It Go)
2. **曲演奏デモ**(千本桜)
2. **ガイド演奏**(千本桜)

Files
------

|ファイル名|内容|
|:-------|:---|
|RGB_matrix.ino|スケッチのメイン|
|led_fullcolor_3.h|9個のフルカラーLEDのライブラリ|
|digiRW.h|高速にIO処理を行うためのライブラリ|
|playMelodyStep.h|メロディの各情報を取り出すためのライブラリ|
|sounds.h|メロディを記述|
|touch.h|タッチセンサに関するライブラリ|
|README.md|このファイル|
|LICENCE|The MIT License|
|[reference]|参考プロジェクト|


Pins
------
|Pin番号|機能|
|:-----|:---|
|d0|
|d1|
|d2|left led cathode
|d3|
|d4|touch sensor common
|d5|green led anode
|d6|blue led anode
|d7|red led anode
|d8|buzzer
|d9|switch
|d10|middle led cathode
|d11|right led cathode
|d12|touch sensor C(8va)
|d13|touch sensor B
|d14(ai0)|touch sensor A
|d15(ai1)|touch sensor G
|d16(ai2)|touch sensor F
|d17(ai3)|touch sensor E
|d18(ai4)|touch sensor D
|d19(ai5)|touch sensor C

