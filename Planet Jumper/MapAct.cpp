#include "MapAct.h"

#define CURSOR_X	(16)
#define CONTENT_X	(48)

MAP_ACT::MAP_ACT() {	//コンストラクタ
	cursor = ST1;

}

void MAP_ACT::Init() {
	cursor = ST1;
}

void MAP_ACT::Update() {	//アップデート関数
	KeyGet();
	Draw();
}

void MAP_ACT::KeyGet() {
	if (KeyDown.down()) {
		switch (cursor) {
		case ST1:
			cursor = ST2;
			break;

		case ST2:
			cursor = ST3;
			break;

		case ST3:
			cursor = ST_BOSS;
			break;

		case ST_BOSS:
			cursor = ST_TUTORIAL;
			break;

		case ST_TUTORIAL:
			cursor = ST_SHOP;
			break;

		case ST_SHOP:
			cursor = ST_GUIDE;
			break;

		case ST_GUIDE:
			cursor = ST_SAVE;
			break;

		case ST_SAVE:
			cursor= ST_INITIALIZE;
			break;

		case ST_INITIALIZE:
			cursor = ST_FINISH;
			break;

		case ST_FINISH:
			cursor = ST1;
			break;
		}
	}
	if (KeyUp.down()) {
		switch (cursor) {
		case ST1:
			cursor = ST_FINISH;
			break;

		case ST2:
			cursor = ST1;
			break;

		case ST3:
			cursor = ST2;
			break;

		case ST_BOSS:
			cursor = ST3;
			break;

		case ST_TUTORIAL:
			cursor = ST_BOSS;
			break;

		case ST_SHOP:
			cursor = ST_TUTORIAL;
			break;

		case ST_GUIDE:
			cursor = ST_SHOP;
			break;

		case ST_SAVE:
			cursor = ST_GUIDE;
			break;

		case ST_INITIALIZE:
			cursor = ST_SAVE;
			break;

		case ST_FINISH:
			cursor = ST_INITIALIZE;
			break;
		}
	}
}

void MAP_ACT::Draw() {
	font64(U"ステージセレクト").draw(CONTENT_X, STAGE_SELECT);
	font32(U"Stage1").draw(CONTENT_X, ST1);
	font32(U"Stage2").draw(CONTENT_X, ST2);
	font32(U"Stage3").draw(CONTENT_X, ST3);
	font32(U"Stageboss").draw(CONTENT_X, ST_BOSS);
	font32(U"チュートリアル").draw(CONTENT_X, ST_TUTORIAL);
	font32(U"ショップ").draw(CONTENT_X, ST_SHOP);
	font32(U"セーブ").draw(CONTENT_X, ST_SAVE);
	font32(U"初期化").draw(CONTENT_X, ST_INITIALIZE);
	font32(U"終了").draw(CONTENT_X, ST_FINISH);
	font32(U"操作説明").draw(CONTENT_X, ST_GUIDE);
	font32(U"▶").draw(CURSOR_X, cursor);
}

int MAP_ACT::GetStage() {
	return cursor;
}
