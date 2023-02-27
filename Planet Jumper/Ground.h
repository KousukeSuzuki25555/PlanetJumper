#pragma once
#include "Main.h"
#include "Draw.h"

class GROUND {	//地面関数
private:
	VECTOR2 pos;	//座標
	VECTOR2 camera;	//カメラ座標
	DRAW* pdraw;	
public:
	GROUND();	//コンストラクタ
	void PointerInit(DRAW* pdraw);	//ポインタの初期化
	void Draw(float camera);	//描画関数(float)
	void Draw(VECTOR2 camera);	//描画関数(VECTOR2)
};
