#pragma once
#include "Main.h"

class CURSOR {
	VECTOR2 pos;
	VECTOR2 posArray[3];	//先に利用される座標を計算して入れておく
	float rot;
	bool changeRot;

public:
	CURSOR();
	void Init();
	void Update(VECTOR2 ppos);
	void KeyGet();	//キー取得
};
