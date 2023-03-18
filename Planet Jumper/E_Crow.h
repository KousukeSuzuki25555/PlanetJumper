#pragma once
#include "Block.h"
#include "TicketPlayGame.h"
#include "MyTime.h"
#include "Weapon.h"

class CROW :public BLOCK {
	bool exist;	//存在しているか
	float time;	//時間変数
	float anm_time;	//アニメーションに用いる時間変数
	//int gra;	//何番目の絵を使うか
	Ticket* pticket;
	MY_TIME* ptime;
	VECTOR2 p_vertex[4];	//プレイヤーの頂点座標
	WEAPON* pweapon;

public:
	CROW();	//コンストラクタ
	void PointerInit(DRAW* pdraw, PLAYER* pplayer, Ticket* pticket,MY_TIME* ptime, WEAPON* pweapon);	//ポインタの初期化
	void Init(float rot,int ticketNum);	//初期化
	void Update();	//アップデート関数
	bool GetExist();	//exsistを返す
	void Draw(float camera);	//描画関数
};
