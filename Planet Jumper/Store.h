#pragma once
#include "Main.h"
#include "Status.h"
#include "Draw.h"

enum STORE_CONTENT {
	STORE_TITLE = 16,
	BULLET_POWER = 96,
	BULLET_NUM = 128,
	PLAYER_HP = 160,
	BACK_MAP = 192,
	SENTENCE = Y_MAX/2+50
};

class STORE {
	int cursor;		//カーソルの位置
	//int ticketNum;	//チケットの枚数
	bool buyFlag;	//購入画面へ移るフラグ
	bool backMap;	//Mapに戻るフラグ
	VECTOR2 ticketPos;	//チケットを描画する位置
	GAME_STATUS* pstatus;
	DRAW* pdraw;
	const Font font32{ 32 };
	const Font font64{ 64 };

public:
	STORE();		//コンストラクタ
	void PointerInit(GAME_STATUS* pstatus, DRAW* pdraw);	//使用するポインタの初期化
	void Init();	//使用時の初期化作業
	void Update();	//アップデート関数
	void Draw();	//描画関数
	void BuyAct();	//購入を実行する関数
	void KeyGet();	//キー入力受付関数
	bool GetBack();	//マップに戻るか　true:マップに戻る　false:そのまま
};
