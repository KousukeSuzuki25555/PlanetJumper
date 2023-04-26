#pragma once
#include "Main.h"
#include "Draw.h"
#include "Player.h"

class SPINE {		//dragonが発射する棘class
private:
	VECTOR2 pos;	//座標
	VECTOR2 camera;	//カメラ座標
	VECTOR2 target;	//player座標
	VECTOR2 vertex;	//頂点座標
	VECTOR2 pVertex[4];	//playerの頂点座標
	I_VECTOR2 size;	//画像サイズ
	I_VECTOR2 pSize;	//プレイヤーのサイズ
	DRAW* pdraw;	
	float rot;	//回転
	float time;	//時間変数
	float atk;	//攻撃力
	bool exist;	//存在しているか
	//bool d_vertex[4];

public:
	SPINE();	//コンストラクタ
	void PointerInit(DRAW* pdraw);	//ポインタの初期化
	void Init(VECTOR2 pos,float now);	//初期化
	void Reset();	//棘をリセットする関数 
	void Update(float now,PLAYER* pplayer);	//アップデート関数
	void Draw(VECTOR2 camera);	//描画関数
	void PlayerHit(PLAYER* pplayer,float now);	//プレーヤーとの当たり判定
	bool GetExist();	//existを返す
	//void DetectReset();
};
