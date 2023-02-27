#pragma once
#include <time.h>

class MY_TIME {			//プログラム上で用いる時間class
	float time;	//時間変数
public:
	MY_TIME();	//コンストラクタ
	void Update();	//アップデート関数
	float GetTime();	//時間のゲッター
};
