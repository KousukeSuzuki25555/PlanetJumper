#pragma once
#include "MyType.h"
#include "Status.h"

/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
マクロ
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
#define X_MAX	(1280)		//画面横の大きさ
#define Y_MAX	(720)		//画面縦の大きさ
#define G_SIZE	(32)		//グラフィックのサイズ
#define DIV_SPEED (125)		//speedを割る値
#define GRAVITY_ST	(0.30f)	//重力強い
#define GRAVITY_NOR	(0.25f)	//重力普通
#define GRAVITY_WE	(0.20f)	//重力弱い
#define SPEED_NOR	(30.0f)	//スピード普通
#define SPEED_FAST	(20.0f)	//スピード早い
#define SPEED_SLOW	(40.0f)	//スピード遅い
#define PLAYER_SIZE_X	(20)	//playerBoxの縦サイズ
#define PLAYER_SIZE_Y	(G_SIZE)	//playerBoxの横サイズ
#define PLAYER_POS_X	(440)	//playerの初期座標x
#define PLAYER_POS_Y	(240)	//playerの初期座標y
#define TIME_DIVIDER	(1000)	//時間を秒単位にする
#define PI	(3.1415926535f)	//π
#define RADIUS		(1020)	//地面の半径
#define CENTER_X	(440)	//円の中心x
#define CENTER_Y	(1278)	//円の中心y
#define D_GRA_SIZE	(64)	//ドラゴンの描画に使う
#define MAPSTAGE_GAP (16)	//マップのタイトル戸の隙間
#define HP_MAX		(6)		//PLAYERのHP最大値
#define BULLETS_MAX	(5)		//銃弾の最大値


enum SCENE_STATE {		//ゲームのどの状態にあるか
	SCENE_TITLE,
	SCENE_STAGESELECT,
	SCENE_OPTION
};

enum ORDER {			//jumpやspeedなどアイコンで使う物の強弱に用いる
	STRONG,
	NORMAL,
	WEAK
};

enum MAPSTAGE {			//MAP上での状態
	STAGE_SELECT = 64,
	ST1 = 128+ MAPSTAGE_GAP,
	ST2 = 128+32+ MAPSTAGE_GAP,
	ST3	= 128+32*2+MAPSTAGE_GAP,
	ST_BOSS = 128+32*3+ MAPSTAGE_GAP,
	ST_TUTORIAL=128+32*4+ MAPSTAGE_GAP,
	ST_SHOP = 128+32*5+ MAPSTAGE_GAP,
	ST_GUIDE = 128+32*6+ MAPSTAGE_GAP,
	ST_SAVE = 128+32*7 + MAPSTAGE_GAP,
	ST_INITIALIZE= 128+32*8 + MAPSTAGE_GAP,
	ST_FINISH = 128+32*9+ MAPSTAGE_GAP
};

enum STAGE_STATE {		//ステージ上での現在の状態
	PLAY,
	ST_GAMEOVER,
	ST_CLEAR,
	ST_MAP,
	ST_FIRST_CLEAR,
	//ST_TICKET_GET
};

enum WEAPON_NUM {
	NORMAL_GUN,
	MACHINE_GUN,
	CURSOR_GUN
};

/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 構造体
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

struct CLOCK2 {	//2つのtimeを保持できる
	float t1;
	float t2;
};

/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
プロトタイプ宣言
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
bool HitDetection(VECTOR2 a, VECTOR2 b, VECTOR2 c);	//当たり判定を外積で求める
float Diagonal(VECTOR2 start, VECTOR2 goal);	//三平方の定理
VECTOR2 VacNormalize(VECTOR2 start, VECTOR2 goal); 	//ベクトルの正規化
bool PlayerHitDetection(VECTOR2 ppos, VECTOR2 pos, I_VECTOR2 size);	//回転していない図形との当たり判定に使う sizeは回転しない矩形のサイズ
VECTOR2 MakeVirtualPos(VECTOR2 start, VECTOR2 point, float rot); //当たり判定のために同一平面上に点を移動する関数
bool LineCollision(float x, float p1, float p2);	//第一引数が縦の直線のｘ
float Damage(unsigned short int power, GAME_STATUS* pstatus);	//Bulletの攻撃力を算出

/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
グローバル変数宣言
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
