#pragma once
#include "MyType.h"
#include "Draw.h"

class FirstClear {	//初クリア時に使う
	VECTOR2 pos;	//座標
	DRAW* pdraw;
	const Font font{ 32 };

public:
	FirstClear();	//コンストラクタ
	void PointerInit(DRAW* pdraw);	//ポインタの初期化
	void Update();	//アップデート関数
	void Draw();	//描画関数
};
