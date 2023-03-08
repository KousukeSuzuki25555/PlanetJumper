#pragma once
#include "MapAct.h"
#include "Tutorial.h"
#include "Stage1.h"
#include "Stage2.h"
#include "Stage3.h"
#include "StageBoss.h"
#include "GameOver.h"
#include "Status.h"
#include "UserGuide.h"
#include "Player.h"
#include "Ground.h"
#include "Store.h"
#include "MyTime.h"

class GAMEMANAGER {	//ゲームマネージャーclass
private:
	TUTORIAL tutorial;
	STAGE1 stage1;
	STAGE2 stage2;
	STAGE3 stage3;
	MAP_ACT map;
	BossSt stageBoss;
	UserGuide guide;
	DRAW* pdraw;
	PLAYER* pplayer;	//PLAYERはここのみで生成し、ポインタを渡して扱う
	GROUND* pground;
	MY_TIME* ptime;
	STORE store;
	GAME_STATUS* pstatus;
	bool* pgameContinue;
	const Font font{ 32 };
	int select;		//どのステージをプレイしているか
	int old_select;	//ステージが変更された時などに気づくための変数
	bool st_start;					///ステージスタート演出を行う
	float perf_time;				//演出に使う変数
	float perf_x;					//演出の背景の移動に用いる

public:
	GAMEMANAGER();	//コンストラクタ
	void PointerSet(GAME_STATUS* pstatus,DRAW* pdraw,PLAYER* pplayer,GROUND* pground,MY_TIME* ptime, bool* pgameContinue);	//ポインタのセッター
	void Update();	//アップデート関数
	void MapInit();	//マップの初期化
	void StageStartPerf(int select);	//stage開始演出を行う関数
};
