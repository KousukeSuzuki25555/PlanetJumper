#include "FirstClear.h"
#include "Main.h"

FirstClear::FirstClear() {
	pos = { X_MAX / 2,Y_MAX / 2 };
}

void FirstClear::PointerInit(DRAW* pdraw) {
	this->pdraw = pdraw;
}
void FirstClear::Update() {
	Draw();
}

void FirstClear::Draw() {
	pdraw->TicketDraw(pos, false);
	font(U"初クリア！").drawAt(X_MAX / 2, Y_MAX / 2 - 100);
	font(U"チケットを入手 Shopへ行ってみよう").drawAt(X_MAX / 2, Y_MAX / 2 +150);
}
