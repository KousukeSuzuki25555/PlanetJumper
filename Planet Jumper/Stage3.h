#pragma once
#include "Player.h"
#include "Stage1.h"
#include "Block.h"
#include "E_Tiger.h"
#include "E_Crow.h"
#include "E_Police.h"
#include "E_Ufo.h"
#include "Ground.h"
#include "MyTime.h"
#include "Icon.h"
#include "GameOver.h"
#include "Clear.h"
#include "FirstClear.h"
#include "TicketPlayGame.h"
#include "Weapon.h"

#define TIGER_MAX	(3)	//虎の出現数
#define CROW_MAX	(4)	//カラスの出現数
#define BLOCK_MAX	(10)	//ブロックの出現数

class STAGE3 :public STAGE1 {
private:
	BLOCK block[BLOCK_MAX];
	I_VECTOR2 blockSize[BLOCK_MAX];
	TIGER tiger[TIGER_MAX];
	CROW crow[CROW_MAX];
	UFO ufo;
	Ticket* pticket = new Ticket;
	WEAPON* pweapon;
	float ufoInitTime;	//UFOを出現させる巻子

public:
	STAGE3();	//コンストラクタ
	~STAGE3();	//デストラクタ
	void PointerInit(DRAW* pdraw, PLAYER* pplayer, MY_TIME* ptime, GAME_STATUS* pstatus);	//ポインタの初期化
	void Init();	//初期化関数
	void Update();	//アップデート関数
	void Draw();	//描画関数
};
