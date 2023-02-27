#pragma once
#include "Main.h"
#include "Player.h"
#include "DragonSpine.h"
#include "Draw.h"
#include "Status.h"
#include "TicketPlayGame.h"

#define D_SIZE		(32)

struct DragonBox {	//DragonのBox毎の情報を入れる構造体
	VECTOR2 pos;
	I_VECTOR2 size;
	float rot;
	float before_rot;
	float hp;
	int g_v;	//上から何枚目の絵を使うか
	bool exist;
};

enum DRAGON_ST {	//Dragonの状態
	DST_NORMAL,
	DST_ATTACK1,
	DST_ATTACK2
};

enum DRAGON_ATTACK_ST {	//Attack中の状態遷移
	DST1,
	DST2,
	DST3
};

enum FORM {	//形態
	FIRST_FORM,
	SECOND_FORM
};

class Dragon {
private:
	DragonBox d_box[11];	//ドラゴンの胴体をそれぞれboxで管理
	VECTOR2 camera;	//カメラの座標
	VECTOR2 cameraSave;	//カメラに送る際の値を保存
	VECTOR2 hitPos[4];	//頂点座標
	VECTOR2 p_vertex[4];	//プレイヤーの頂点座標
	VECTOR2 ppos;	//プレイヤーの座標
	DRAW* pdraw;	
	SPINE spine[9];	//DragnSpineのclassを9個持つ
	Ticket* pticket;	
	unsigned short int state;	//状態
	unsigned short int attackState;	//攻撃中の状態
	unsigned short int form;	//形態
	unsigned short int attack1FirstBox;	//攻撃中の最初の箱
	unsigned short int firstBox;	//最初の箱
	int bulletNum;	//銃弾の数
	float hp;	//HP
	float time;	//時間変数
	float rot;	//回転
	float addRot;	//箱が連続しているため回転を足していく
	float radius;	//半径
	float anm_time;	//アニメーションにも散る時間変数
	float attack_time;	//attack1,attack2で用いる時間変数
	float atk;	//攻撃力
	float speed;	//スピード変数
	float radiusGoal;	//攻撃の際の半径のゴール地点
	float rotMs;	//回転の毎秒の移動量
	float timeMs;	//時間の毎秒の移動量
	float moveMs;	//毎秒の移動量
	bool d_vertex[4];	//当たったかの判定に使う
	bool playerHit;	//プレイヤーがヒットしたか
	bool attackFlag;	//攻撃中か
	bool attackTradition;	//攻撃中の状態遷移
	bool cameraFlag;	//カメラを使うか
	bool dragonState;	//dragonが起こり状態になるフラグ
	bool state2Init;	//状態２へ移行するフラグ
	bool witchAttack;	//攻撃するか

public:
	Dragon();	//コンストラクタ
	void PointerInit(DRAW* pdraw, Ticket* pticket);	//ポインタの初期化
	void Init(float now,int bulletNum);	//初期化
	void State2Init();	//状態２の初期化
	void Update(PLAYER* pplayer,float now, GAME_STATUS* pstatus);	//アップデート関数
	void Draw(VECTOR2 camera);	//描画関数
	void Anm(float now);	//アニメーション関数
	void PlayerHit(PLAYER* pplayer);	//プレイヤーとの当たり判定
	void BulletHit(PLAYER* pplayer, GAME_STATUS* pstatus);	//銃弾との当たり判定
	void DetectReset();	//d_vertex[4]を初期化する
	void SetSpeed(float speed);	//スピードをセット
	void Attack1Set(float now);	//攻撃１をセット
	void Attack1TrdSet();	//攻撃１を次の状態にセット
	void Attack2TrdSet();	//攻撃１を次の状態にセット
	void Attack1Act(float now);	//攻撃１の実働部
	void Attack1Uninit(float now);	//攻撃１の状態から抜ける
	void Attack2Set(float now);	//攻撃２をセット
	void Attack2Act(float now);	//攻撃２の実働部
	void Attack2Uninit(float now);	//攻撃２から抜ける
	void SpineUpdate(float now,PLAYER* pplayer);	//棘のアップデート
	VECTOR2 CameraPos();	//カメラを返す
	float GetHp();	//Hpを取得
	unsigned short int GetForm();	//状態を返す
};
