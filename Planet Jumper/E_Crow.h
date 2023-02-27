#pragma once
#include "Block.h"
#include "TicketPlayGame.h"

class CROW :public BLOCK {
	bool exist;	//存在しているか
	float time;	//時間変数
	float anm_time;	//アニメーションに用いる時間変数
	//int gra;	//何番目の絵を使うか
	Ticket* pticket;	
	VECTOR2 p_vertex[4];	//プレイヤーの頂点座標

public:
	CROW();	//コンストラクタ
	void PointerInit(DRAW* pdraw, PLAYER* pplayer, Ticket* pticket);	//ポインタの初期化
	void Init(float rot,float time,int ticketNum);	//初期化
	void Update(float now);	//アップデート関数
	bool GetExist();	//exsistを返す
	void Draw(float camera);	//描画関数
};
