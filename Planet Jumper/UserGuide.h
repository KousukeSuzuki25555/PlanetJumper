#pragma once
#include "Player.h"
#include "Draw.h"
#include "E_Tiger.h"
#include "Status.h"
#include "Icon.h"
#include "MyTime.h"
#include "Weapon.h"

enum USERGUIDE {	//表示部分の座標
	TITLE = 16,
	U_JUMP = 112,
	DOUBLE_JUMP = 144,
	TRIPLE_JUMP = 176,
	SINGLE_JUMP = 208,
	STRONG_JUMP = 240,
	WEAK_JUMP = 272,
	DODGE_ENEMY = 304,
	ATTACK = 368,
	STRONG_ATTACK = 400,
	WEAK_ATTACK = 432,
	SHOT_ENEMY = 464,
	U_RUN = 528,
	FAST_RUN = 560,
	SLOW_RUN = 592
};

class UserGuide {	//ガイドのclass
	//PLAYER player;
	PLAYER* pplayer;
	TIGER tiger;
	ICON icon;
	DRAW* pdraw;
	GAME_STATUS* pstatus;
	MY_TIME* ptime;
	WEAPON* pweapon;
	const Font font64{ 64 };
	const Font font32{ 32 };
	int cursor;					//カーソルの場所
	int oldCursor;	//前フレームでのカーソルの場所
	float time;	//時間変数
	bool guideJump;	//ジャンプの説明中か

public:
	UserGuide();	//コンストラクタ
	void PointerInit(GAME_STATUS* pstatus,DRAW* pdraw,PLAYER* pplayer,MY_TIME* ptime);	//ポインタの初期化
	void Init();	//初期化
	void Update();	//アップデート関数
	void GetCursor();	//カーソルの位置のゲッター
	void Draw();	//描画関数
};
