#include "TicketPlayGame.h"

Ticket::Ticket() {	//コンストラクタ
	pstatus = 0;
	pdraw = 0;
	ticketNum = 0;
}

void Ticket::PointerInit(DRAW* pdraw, GAME_STATUS* pstatus) {	//ポインタの初期化
	this->pstatus = pstatus;
	this->pdraw = pdraw;
	ticketNum = 0;
}

void Ticket::Init() {	///初期化
	ticketNum = 0;
}

void Ticket::Draw(bool boss) {	//ゲーム画面での描画
	pdraw->TicketSmallDraw(boss);
	if (boss == false) {
		font(U"×", ticketNum).drawAt(650, Y_MAX - 278);
	}
	else {
		font(U"×", ticketNum).drawAt(350, Y_MAX - 14);
	}
}

void Ticket::ClearDraw() {	//クリア画面での描画
	font(ticketNum, U"枚チケットを獲得した").drawAt(X_MAX / 2, Y_MAX / 2 + 96);
}


void Ticket::SetTicket() {	//エネミーからチケットをドロップしたときに用いる
	ticketNum++;
}

void Ticket::SetStatus() {	//ステータスにチケットを更新する
	pstatus->SetTicket(pstatus->GetTicket() + ticketNum);
}
