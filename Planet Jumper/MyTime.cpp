#include "MyTime.h"

MY_TIME::MY_TIME() {	//プログラムで用いる時間のコンストラクタ
	time = (float)clock() / 1000;
}

void MY_TIME::Update() {	//フレームごとに時間を更新する
	time = (float)clock() / 1000;
}

float MY_TIME::GetTime() {	//現在のフレームの時間のゲッター
	return (float)time;
}
