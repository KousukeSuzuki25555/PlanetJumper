#pragma once
#include "MyType.h"
#include "Player.h"
#include "Draw.h"
#include "Ground.h"

class GAME_TITLE {
	DRAW* pdraw;
	PLAYER* pplayer;
	GROUND* pground;
	VECTOR2 camera;
	float rot;	//回転
	float time;	//回転量に使う時間関数
	float enterTime;	//enterの表示に用いる時間変数
	bool titleFlag;	//Enterが押されて次の画面に移動するか
	bool enterFlag;	//enterを表示するか
	const Font font{ 64 };
	const Font font32{ 32 };

public:
	GAME_TITLE();	//コンストラクタ
	void PointerSet(DRAW* pdraw,PLAYER* pplayer,GROUND* pground);	//ポインタのセッター
	void Update(float now);	//アップデート関数
	bool GetTitleFlag();	//タイトルフラグのゲッター
	void Draw();	//描画関数
};
