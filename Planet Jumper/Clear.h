#pragma once
#include "GameOver.h"
#include "TicketPlayGame.h"

class CLEAR :public GAMEOVER {
	Ticket* pticket;
public:
	void Init(Ticket* pticket);	//初期化
	void Update();	//アップデート関数
};
