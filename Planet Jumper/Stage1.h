#pragma once
#include "Main.h"
#include "Ground.h"
#include "Player.h"
#include "Icon.h"
#include "MyTime.h"
#include "Draw.h"
#include "E_Police.h"
#include "Block.h"
#include "GameOver.h"
#include "Clear.h"
#include "Status.h"
#include "FirstClear.h"
#include "TicketPlayGame.h"
#include "MyTime.h"
#include "Weapon.h"

class STAGE1 {	//簡単にチュートリアルをなぞるように
private:
	BLOCK block[10];
	I_VECTOR2 block_size[10];

protected:	//継承する変数	敵のみ宣言すればよいようにする
	PLAYER* pplayer;
	POLICE police;
	ICON icon;
	DRAW* pdraw;
	GROUND ground;
	GAMEOVER gameover;
	CLEAR clear;
	FirstClear fClear;
	Ticket ticket;
	Ticket* pticket;
	GAME_STATUS* pstatus;
	MY_TIME* ptime;
	WEAPON* pweapon;
	unsigned short int state;	//ステージ上での状態
	float camera;	//カメラ
	//float now;	//時間
	float meterTime;	//メーターで使う時間
	float rot;	//回転
	float time;	//時間変数
	bool meterAnm;	//メーターのアニメーションで用いる
	bool bulletHit;	//銃弾がヒットしたか

public:
	STAGE1();	//コンストラクタ
	void PointerInit(DRAW* pdraw,PLAYER* pplayer,MY_TIME* ptime, GAME_STATUS* pstatus);	//ポインタの初期化
	void Update();	//アップデート関数
	void Draw();	//描画関数
	void Init();	//初期化関数
	bool GetMap();	//マップに戻るか
};
