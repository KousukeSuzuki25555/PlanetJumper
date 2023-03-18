#pragma once
#include "Main.h"
#include "Draw.h"

class CURSOR {
	VECTOR2 pos;
	VECTOR2 posArray[3];	//先に利用される座標を計算して入れておく
	VECTOR2 camera;
	DRAW* pdraw;
	float rot;
	bool changeRot;

public:
	CURSOR();
	void PointerInit(DRAW* pdraw);
	void Init();
	void Update(VECTOR2 ppos);
	void KeyGet();	//キー取得
	void Draw(float camera);
};
