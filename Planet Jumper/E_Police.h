#pragma once
#include "Main.h"
#include "Draw.h"
#include "Bullet.h"
#include "player.h"
#include "MyTime.h"

class POLICE {
	VECTOR2 pos;	//座標
	VECTOR2 camera;	//カメラ座標
	I_VECTOR2 uv;	//uv値
	I_VECTOR2 bustUv;	//上体のuv値
	DRAW* pdraw;	
	PLAYER* pplayer;	
	BULLET bullet;
	MY_TIME* ptime;
	bool attackFlag;	//攻撃中か
	bool bulletHit;	//銃弾が当たったか
	float gravity;	//重力
	float anmTime;	//アニメーションに用いる時間変数
	float rotate;	//回転
	float attackTime;	//攻撃に用いる時間関数
	float runTime;	//走りアニメーションに用いる変数
	float ppos;	//プレイヤーの座標
public:
	POLICE();	//コンストラクタ
	void PointerInit(DRAW* pdraw,PLAYER* pplayer,MY_TIME* ptime);	//ポインタの初期化
	void Update(float speed);	//アップデート関数
	void Init();	//初期化
	void AttackSet();	//攻撃への移行関数
	void AttackFin();	//攻撃終了関数
	void Anm();	//アニメーション
	void SetGravity(unsigned short int strength);	//重力のセッター
	void Draw(float camera);	//描画関数
	void SetPpos(float ppos);	//player座標をセット	
	void RotInit();	//回転の初期化
	bool GetBulletHit();	//銃弾が当たったか
	float GetRot();	//回転のゲッター
	VECTOR2 GetPos();	//座標を返す	
	I_VECTOR2 GetUv();	//uv値のゲッター
	I_VECTOR2 GetBustUv();	//上部のuv値のゲッター
	void PlayerHit();	//playerに当たった時の関数
};
