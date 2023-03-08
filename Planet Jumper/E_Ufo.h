#pragma once
#include "Main.h"
#include "Player.h"
#include "MyTime.h"
#include "TicketPlayGame.h"

class UFO {
	VECTOR2 pos;	//座標
	PLAYER* player;	//playerのポインタ
	Ticket* pticket;	//チケットのポインタ
	VECTOR2 camera;			//cameraのpos
	VECTOR2 p_vertex[4];	//playerの中心からの座標
	int hp;					//hp
	float time;				//移動などに使う時間関数
	float moveTime;			//移動するタイミング
	bool exist;				//存在するか
	bool hit;				//攻撃を食らったか

public:
	UFO();
	void PointerInit(PLAYER* pplayer, Ticket* pticket,MY_TIME* ptime);
	void Update();

};
