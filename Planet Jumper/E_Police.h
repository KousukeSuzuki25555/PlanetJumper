#pragma once
#include "Main.h"
#include "Draw.h"
#include "Bullet.h"
#include "player.h"

class POLICE {
	VECTOR2 pos;	//座標
	VECTOR2 camera;	//カメラ座標
	I_VECTOR2 uv;	//uv値
	I_VECTOR2 bust_uv;	//上体のuv値
	DRAW* pdraw;	
	PLAYER* pplayer;	
	BULLET bullet;	
	bool attack_flag;	//攻撃中か
	bool bullet_hit;	//銃弾が当たったか
	float gravity;	//重力
	float anm_time;	//アニメーションに用いる時間変数
	float rotate;	//回転
	float attack_time;	//攻撃に用いる時間関数
	float run_time;	//走りアニメーションに用いる変数
	float ppos;	//プレイヤーの座標
public:
	POLICE();	//コンストラクタ
	void PointerInit(DRAW* pdraw,PLAYER* pplayer);	//ポインタの初期化
	void Update(float now,float speed);	//アップデート関数
	void Init(float now);	//初期化
	void AttackSet();	//攻撃への移行関数
	void AttackFin(float now);	//攻撃終了関数
	void Anm(float now);	//アニメーション
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
