#pragma once
#include "Main.h"
#include "Draw.h"
#include "Player.h"

class BLOCK {	//建物のclass　継承してENEMYを作る
protected:
	VECTOR2 pos;	//座標
	VECTOR2 n_vertex[4];		//blockの頂点
	VECTOR2 ppos;	//playerの位置
	VECTOR2 camera;	//描画で用いる
	VECTOR2 p_vertex[4];	//playerの頂点座標を入れる
	I_VECTOR2 p_size;	//playerのサイズ
	I_VECTOR2 uv;	//uv値
	PLAYER* pplayer;
	DRAW* pdraw;
	I_VECTOR2 size;	//	Boxサイズ
	int radius;	//円の中心からの半径
	int bulletNum;	//playerの銃弾数を言える
	float rotate;	//どれだけ回転しているか
	float rotate_gap;	//初期化で現在との差を入れる
	float speed;	//移動の速さ
	bool d_vertex[4];			//各頂点の外積が内側にあるか判定

public:
	BLOCK();	//コンストラクタ
	void Init(float speed, float rotate, I_VECTOR2 size, int u, int v, int bulletNum);	//初期化
	void PointerInit(DRAW* pdraw,PLAYER* pplayer);	//Pointerの初期化
	void Draw(float camera);	//描画
	void Update(float now);	//アップデート関数
	bool Hit();	//playerとの当たり判定
	void DetectReset();	//Hitに用いる変数の初期化
	void SetSpeed(float speed);	//Boxの移動速度を求める
};
