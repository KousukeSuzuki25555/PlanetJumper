#include "GameManager.h"

GAMEMANAGER::GAMEMANAGER() {
	select = MAP;
	old_select = select;
	st_start = false;	//stage開始演出
	perf_x = X_MAX;
	perf_time = 0.0f;
	pdraw = 0;
	pplayer = 0;
	pground = 0;
	pstatus = 0;
}

void GAMEMANAGER::PointerSet(GAME_STATUS* pstatus, DRAW* pdraw,PLAYER* pplayer,GROUND* pground, MY_TIME* ptime,bool* pgameContinue) {
	this->pdraw = pdraw;
	this->pplayer = pplayer;
	this->pground = pground;
	this->ptime = ptime;
	tutorial.PointerInit(pstatus,pdraw, pplayer,ptime);
	stage1.PointerInit(pdraw, pplayer,ptime,pstatus);
	stage2.PointerInit(pdraw, pplayer,ptime,pstatus);
	stage3.PointerInit(pdraw, pplayer, ptime, pstatus);
	stageBoss.PointerInit(pdraw, pplayer, pground,ptime,pstatus);
	guide.PointerInit(pstatus,pdraw, pplayer,ptime);
	this->pgameContinue = pgameContinue;
	this->pstatus = pstatus;
	store.PointerInit(pstatus,pdraw);
}

void GAMEMANAGER:: Update() {

	switch (select) {
	case MAP:
		map.Update();
		if (KeyEnter.down()) {
			select = map.GetStage();
		}
		break;

	case ST_TUTORIAL:
		tutorial.Update();
		if (tutorial.GetContinue() == false) {
			select = MAP;
		}
		break;

	case ST1:
		stage1.Update();
		if (stage1.GetMap() == true) {
			select = MAP;
		}
		break;

	case ST2:
		stage2.Update();
		if (stage2.GetMap() == true) {
			select = MAP;
		}
		break;

	case ST3:
		stage3.Update();
		if (stage2.GetMap() == true) {
			select = MAP;
		}
		break;

	case ST_BOSS:
		stageBoss.Update(pstatus, ptime->GetTime());
		if (stageBoss.GetMap() == true) {
			select = MAP;
		}
		break;

	case ST_SHOP:
		store.Update();
		if (store.GetBack() == true) {
			select = MAP;
		}
		break;

	case ST_GUIDE:
		guide.Update();
		if (KeyEnter.down()) {
			select = MAP;
		}
		break;

	case ST_SAVE:
		pstatus->SaveData();
		select = MAP;
		break;

	case ST_INITIALIZE:
		pstatus->Init();
		select = MAP;
		break;

	case ST_FINISH:
		*pgameContinue = false;
		break;
	}

	if (old_select != select) {
		switch (select) {
		case ST1:
			stage1.Init();
			st_start = true;
			perf_time = ptime->GetTime() + 2.0f;
			break;

		case ST2:
			stage2.Init();
			st_start = true;
			perf_time = ptime->GetTime() + 2.0f;
			break;

		case ST3:
			stage3.Init();
			st_start = true;
			perf_time = ptime->GetTime() + 2.0f;
			break;

		case ST_BOSS:
			stageBoss.Init();
			break;

		case ST_TUTORIAL:
			tutorial.Init();
			break;

		case ST_SHOP:
			store.Init();
			break;

		case ST_GUIDE:
			guide.Init();
			break;

		case MAP:
			MapInit();
			break;
		}
	}

	if (old_select == ST_BOSS && select != ST_BOSS) {
		stageBoss.Uninit();
	}
	if (st_start == true) {
		StageStartPerf(select);
	}
	old_select = select;
}

void GAMEMANAGER::MapInit() {	//stage変数をリセットする
	map.Init();
}

void GAMEMANAGER::StageStartPerf(int select) {	//stage1の文字をスタート時に流す
	perf_x = X_MAX * (perf_time - ptime->GetTime()) / 2.0f;
	pdraw->StageSt(perf_x);
	if (perf_x < X_MAX / 2 - 32 * 3) {
		switch (select) {
		case ST1:
			font(U"STAGE1").draw(X_MAX / 2 - 32 * 3, Y_MAX / 2 - 64);
			break;

		case ST2:
			font(U"STAGE2").draw(X_MAX / 2 - 32 * 3, Y_MAX / 2 - 64);
			break;
		}
	}
	if (perf_x < 0.0f) {
		st_start = false;
	}
}
