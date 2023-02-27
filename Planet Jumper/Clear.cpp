#include "Clear.h"

void CLEAR::Init(Ticket* pticket) {
	this->pticket = pticket;
}

void CLEAR::Update() {
	font48(U"CLEAR!").drawAt(X_MAX / 2, F_GAMEOVER);
	font32(U"continue").drawAt(X_MAX / 2, CONTINUE);
	font32(U"map").drawAt(X_MAX / 2, MAP);
	
	pticket->ClearDraw();

	switch (cursor) {
	case true: {
		font32(U"▶").drawAt(CURSOR_X, CONTINUE);
		break;
	}
	case false: {
		font32(U"▶").drawAt(CURSOR_X, MAP);
		break;
	}
	}

	if (KeyDown.down() || KeyUp.down()) {
		switch (cursor) {
		case true:
			cursor = false;
			break;
		case false:
			cursor = true;
			break;
		}
	}
}
