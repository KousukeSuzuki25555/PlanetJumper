#pragma once
#include "Main.h"
#include "Draw.h"


class BULLET {	//銃弾class
protected:
	VECTOR2 pos;	//座標
	VECTOR2 ppos;	//playerの座標
	VECTOR2 camera;	//カメラ
	I_VECTOR2 pSize;	//playerのサイズ
	DRAW* pdraw;
	int power;	//銃の威力
	int ground;	//地面の距離
	float gravity;	//重力
	float time;	//移動に用いる時間の関数
	float rotate;	//回転
	float jstrength;	//重力の加算値
	float haight;	//地面からの高さ
	float stHaight;	//スタート時の高さ
	bool use;	//使っているか
	bool useColision;	//playerとの当たり判定を行うか
	bool guideFlag;	//guideで使っているか
	//bool d_vertex[4];
	bool hit;	//当たったかどうか

public:
	BULLET();	//コンストラクタ
	void PointerInit(DRAW* pdraw);	//ポインタの初期化
	void Update(float now);	//アップデート関数
	void Init(VECTOR2 pos,float gravity,int power);	//初期化
	void Init(VECTOR2 pos, float gravity, float rotate);	//初期化
	//void Init(VECTOR2 pos, float gravity, int power, int ground);	//初期化
	bool GetUse();	//
	bool GetHit();	//
	void Draw(float camera);	//
	void Draw(VECTOR2 camera);	//
	void SetUse();	//
	void SetPpos(float ppos);	//
	//void DetectReset();
	void PlayerHit();	//
	VECTOR2 GetPos();	//
	int GetPower();	//	
	float GetRot();	//
};
