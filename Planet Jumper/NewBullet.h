#pragma once
#include "Main.h"
#include "Draw.h"
//#include "Player.h"
#include "MyTime.h"

class NEW_BULLET {
	VECTOR2 pos;
	VECTOR2 camera;
	MY_TIME* ptime;
	DRAW* pdraw;
	//PLAYER* pplayer;
	float power;
	float time;
	float rot;		//回転
	float rotMs;	//毎秒の回転
	float haight;	//地面からの高さ
	float gravity;	//かかる重力
	float gravityAdd;	//加算される重力
	bool exist;	//使用されているか
	//bool useColision;	//playerとの当たり判定を行うか

public:
	NEW_BULLET();
	void PointerInit(DRAW* pdraw, MY_TIME* ptime);	//playerから呼び出すとき
	//void PointerInit(DRAW* pdraw,/* PLAYER* pplayer,*/ MY_TIME* ptime);	//敵から呼ぶとき
	void Init(VECTOR2 pos, float gravity, int power, float rot);	//playerからの初期化関数
	void Init(VECTOR2 pos, float gravity);	//enemyからの初期化
	void Update();
	void Move();	//移動の実働部
	void MakeRotMs(/*float rot*/);	//発射角が渡されると毎秒どのくらい角度を更新するかを求める関数
	void GravityAct();		//重力の実働部
	//void PlayerHit();	//playerとの当たり判定
	void LandHit();	//地面に接したかどうか
	VECTOR2 GetPos();	//ほかのclassから銃弾の座標を求めるときに使う
	bool GetExist();	//existのゲッター
	void SetExist(bool state);	//existが変化するとき
	float GetPower();	//powerのゲッター
	void Draw(float camera);	//描画(float)
};
