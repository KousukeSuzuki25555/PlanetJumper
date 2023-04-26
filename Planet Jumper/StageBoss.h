#pragma once
#include "Main.h"
#include "Ground.h"
#include "Player.h"
#include "Icon.h"
#include "MyTime.h"
#include "Draw.h"
#include "E_Dragon.h"
#include "GameOver.h"
#include "Clear.h"
#include "Status.h"
#include "TicketPlayGame.h"
#include "MyTime.h"
#include "Weapon.h"

class BossSt {
	//PLAYER player;
	PLAYER* pplayer;
	Dragon dragon;
	GROUND* pground;
	ICON icon;
	DRAW* pdraw;
	GAMEOVER gameover;
	CLEAR clear;
	VECTOR2 camera;
	Ticket* pticket = new Ticket;
	GAME_STATUS* pstatus;
	MY_TIME* ptime;
	WEAPON* pweapon;
	float speedValue;	//スピードの実数値
	bool bulletHit;	//銃弾がヒットしたか
	unsigned short int state;	//ステージの状態

public:
	BossSt();	//コンストラクタ
	void PointerInit(DRAW* pdraw,PLAYER* pplayer,GROUND* pground,MY_TIME* ptime,GAME_STATUS* pstatus);	//ポインタの初期化
	void Update(GAME_STATUS* pstatus,float now);	//アップデート関数
	void Init();	//初期化
	void Uninit();	//抜ける関数
	void Draw();	//描画関数
	bool GetMap();		//マップに戻るかどうか
};
