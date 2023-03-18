#include "Title.h"

GAME_TITLE::GAME_TITLE() {
	rot = 0.0f;
	titleFlag = false;
	time = (float)clock() / 1000;
	camera = { 0.0f,0.0f };
	enterTime = time;
	enterFlag = true;
}

void GAME_TITLE::PointerSet(DRAW* pdraw,PLAYER* pplayer,GROUND* pground,MY_TIME* ptime, GAME_STATUS* pstatus) {
	this->pdraw = pdraw;
	this->pplayer = pplayer;
	this->pground = pground;
	this->ptime = ptime;
	pplayer->PointerInit(pstatus, pdraw, ptime);
}

void GAME_TITLE::Update() {
	rot -= (ptime->GetTime() - time) / 10;
	pplayer->Update(ptime->GetTime());

	if (KeyEnter.down()) {
		titleFlag = true;
	}

	if (ptime->GetTime() - enterTime > 0.5f) {
		switch (enterFlag) {
		case true:
			enterFlag = false;
			break;

		case false:
			enterFlag = true;
			break;
		}
		enterTime = ptime->GetTime();
	}
	time = ptime->GetTime();
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
