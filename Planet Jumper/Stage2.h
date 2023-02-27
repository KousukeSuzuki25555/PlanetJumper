#pragma once
#include "Player.h"
#include "Stage1.h"
#include "Block.h"
#include "E_Tiger.h"
#include "E_Crow.h"
#include "E_Police.h"
#include "Ground.h"
#include "MyTime.h"
#include "Icon.h"
#include "GameOver.h"
#include "Clear.h"
#include "FirstClear.h"
#include "TicketPlayGame.h"

class STAGE2:public STAGE1 {
private:
	CROW crow[3];
	TIGER tiger[5];
	BLOCK block[17];
	I_VECTOR2 block_size[17];
	Ticket* pticket = new Ticket;

public:
	STAGE2();	//コンストラクタ
	~STAGE2();	//デストラクタ
	void PointerInit(DRAW* pdraw, PLAYER* pplayer);	//ポインタの初期化
	void Init(float now, GAME_STATUS* pstatus);	//初期化関数
	void Update(float now, GAME_STATUS* pstatus);	//アップデート関数
	void Draw();	//描画関数
};
