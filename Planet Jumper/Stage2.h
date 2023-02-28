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

#define TIGER_MAX	(6)	//虎の出現数
#define CROW_MAX	(3)	//カラスの出現数
#define BLOCK_MAX	(17)	//ブロックの出現数

class STAGE2:public STAGE1 {
private:
	CROW crow[CROW_MAX];
	TIGER tiger[TIGER_MAX];
	BLOCK block[BLOCK_MAX];
	I_VECTOR2 block_size[BLOCK_MAX];
	Ticket* pticket = new Ticket;

public:
	STAGE2();	//コンストラクタ
	~STAGE2();	//デストラクタ
	void PointerInit(DRAW* pdraw, PLAYER* pplayer);	//ポインタの初期化
	void Init(float now, GAME_STATUS* pstatus);	//初期化関数
	void Update(float now, GAME_STATUS* pstatus);	//アップデート関数
	void Draw();	//描画関数
};
