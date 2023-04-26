#pragma once
#include "Ground.h"
#include "Player.h"
#include "Icon.h"
#include "MyTime.h"
#include "E_Tiger.h"
#include "Draw.h"
#include "E_Police.h"
#include "Block.h"
#include "Status.h"
#include "Weapon.h"

enum TUTORIAL_TEXT {	//チュートリアルに用いるテキストの座標
	START,
	EXP_JUMP,
	EXP_ATTACK,
	EXP_ICON,
	EXP_Y,
	EXP_U,
	EXP_I,
	EXP_K,
	EXP_N,
	EXP_H,
	EXP_M,
	EXP_COMMA,
	EXP_CNC,	//conclude
	EXP_METER
};

class TUTORIAL {	//チュートリアルのclass
public:
	GROUND ground;
	//PLAYER player;
	PLAYER* pplayer;
	POLICE police;
	ICON icon;
	MY_TIME* ptime;
	TIGER tiger;
	DRAW* pdraw;
	BLOCK block;
	GAME_STATUS* pstatus;
	WEAPON* pweapon;
	I_VECTOR2 buildSize[2];
	int speed;	//スピード
	float now;	//時間
	float rot;	//回転
	float speedValue;	//スピードの実数値
	float meterTime;	//メーターに用いる時間
	float tTime;	//時間変数
	float enemyTime;	//敵に用いる時間変数
	bool meterAnm;	//メーターのアニメーションを用いるか
	bool bulletHit;	//銃弾がヒットしたか
	bool key_get;	//キーを取得したか
	bool buildInitFlag;	//建物を初期化したか
	bool enemyInitFlag;	//敵を初期化したか
	bool usePolice;	//警察を使うか
	bool useTiger;	//虎を用いるか
	bool useBlock;	//建物を用いるか
	const Font font{ 32 };
	int text;	//テキストの座標
	int expIcon;	//アイコンの説明
	float camera;	//カメラの座標
	bool tFlag;	//チュートリアルを終えるかのフラグ

public:
	TUTORIAL();	//コンストラクタ
	void PointerInit(GAME_STATUS* pstatus,DRAW* pdraw,PLAYER* pplayer,MY_TIME* ptime);	//ポインタの初期化
	void Init();	//初期化
	void Update();	//アップデート関数
	void Draw();	//描画関数
	void T_BlockInit1();	//ブロックの初期化１
	void T_BlockInit2();	//ブロックの初期化２
	void T_EnemyInit();	//敵の初期化
	void TutorialAct();	//チュートリアル部分の実働部
	bool GetContinue();	//続けるか
};
