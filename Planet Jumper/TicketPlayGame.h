#pragma once
//#include "MyType.h"
#include "Status.h"
#include "Draw.h"

class Ticket {	//ゲーム中にチケットを獲得したり、クリア後にステータスに更新する
	//VECTOR2 pos;
	GAME_STATUS* pstatus;
	DRAW* pdraw;
	int ticketNum;	//ゲーム中に獲得したチケットの枚数
	const Font font{ 32 };

public:
	Ticket();	//コンストラクタ
	void PointerInit(DRAW* pdraw,GAME_STATUS* pstatus);	//ポインタの初期化
	void Init();	///初期化
	void Draw(bool boss);	//描画
	void ClearDraw();	//クリア画面での描画
	void SetTicket();	//エネミーからチケットをドロップしたときに用いる
	void SetStatus();	//ステータスにチケットを更新する
};
