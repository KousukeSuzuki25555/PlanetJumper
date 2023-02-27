#include "Title.h"

GAME_TITLE::GAME_TITLE() {
	rot = 0.0f;
	titleFlag = false;
	time = (float)clock() / 1000;
	camera = { 0.0f,0.0f };
	enterTime = time;
	enterFlag = true;
}

void GAME_TITLE::PointerSet(DRAW* pdraw,PLAYER* pplayer,GROUND* pground) {
	this->pdraw = pdraw;
	this->pplayer = pplayer;
	this->pground = pground;
	pplayer->DrawPointerInit(pdraw);
}

void GAME_TITLE::Update(float now) {
	rot -= (now - time)/10;
	pplayer->Update(now);

	if (KeyEnter.down()) {
		titleFlag = true;
	}

	if (now - enterTime > 0.5f) {
		switch (enterFlag) {
		case true:
			enterFlag = false;
			break;

		case false:
			enterFlag = true;
			break;
		}
		enterTime = now;
	}
	time = now;
	Draw();
}

bool GAME_TITLE::GetTitleFlag() {
	return titleFlag;
}

void GAME_TITLE::Draw() {
	pdraw->TitleBackDraw(rot);
	pground->Draw(camera);
	pplayer->Draw(camera);
	font(U"Planet Jumper").drawAt(X_MAX / 2, Y_MAX / 2 + 32);
	if (enterFlag == true) {
		font32(U"Press Enter to Start").drawAt(X_MAX / 2, Y_MAX - 32);
	}
}
