#include "Store.h"

#define SENTENCE_X	(64)

STORE::STORE() {		//コンストラクタ
	cursor = 0;		//カーソルの位置
	//ticketNum = 0;	//チケットの枚数
	ticketPos = { SENTENCE_X,Y_MAX / 2 - 100 };	//チケットを描画する位置
	buyFlag = false;	//購入画面へ移るフラグ
	backMap = false;	//Mapに戻るフラグ
}

void STORE::PointerInit(GAME_STATUS* pstatus, DRAW* pdraw) {	//使用するポインタの初期化
	this->pstatus = pstatus;
	this->pdraw = pdraw;
}

void STORE::Init() {	//使用時の初期化
	cursor = BULLET_POWER;
	//ticketNum = pstatus->GetMoney();
	buyFlag = false;
	backMap = false;
}

void STORE::Update() {	//アップデート関数
	if (buyFlag == false) {
		KeyGet();
	}
	else {
		BuyAct();
	}
	Draw();
}

void STORE::Draw() {	//描画関数
	font64(U"SHOP").draw(SENTENCE_X, STORE_TITLE);
	font32(U"銃弾の威力").draw(SENTENCE_X, BULLET_POWER);
	font32(U"弾数").draw(SENTENCE_X, BULLET_NUM);
	font32(U"HP").draw(SENTENCE_X, PLAYER_HP);
	font32(U"ステージセレクトへ戻る").draw(SENTENCE_X, BACK_MAP);
	font32(U"▶").draw(SENTENCE_X-32.0f, cursor);
	pdraw->TicketDraw(ticketPos, true);
	font32(U"×",pstatus->GetTicket()).draw(ticketPos.x+250, ticketPos.y+45);
}

void STORE::BuyAct() {	//購入を実行する関数
	if (pstatus->GetTicket() > 0) {
		font32(U"購入しますか？ Enterで購入　Spaceでやめる").draw(SENTENCE_X, SENTENCE);
		if (KeyEnter.down()) {
			switch (cursor) {
				font32(U"購入ありがとうございます").draw(SENTENCE_X, SENTENCE);
			case BULLET_POWER:
				pstatus->SetBulletPower(pstatus->GetBulletPower() + 0.5f);
				pstatus->SetTicket(pstatus->GetTicket() - 1);
				break;
			case BULLET_NUM:
				if (pstatus->GetBulletsNum() == BULLETS_MAX) {
					font32(U"これ以上は購入できません").draw(SENTENCE_X, SENTENCE);
				}
				else {
					pstatus->SetBulletsNum(pstatus->GetBulletsNum() + 1);
					pstatus->SetTicket(pstatus->GetTicket() - 1);
				}
				break;
			case PLAYER_HP:
				if (pstatus->GetHp() == HP_MAX) {
					font32(U"これ以上は購入できません").draw(SENTENCE_X, SENTENCE);
				}
				else {
					pstatus->SetHp(pstatus->GetHp() + 1);
					pstatus->SetTicket(pstatus->GetTicket() - 1);
				}
				break;
			}
			buyFlag = false;
		}
		else if (KeySpace.down()) {
			buyFlag = false;
		}
	}
	else {
		font32(U"お客様...チケットをお持ちでないですよ").draw(SENTENCE_X, SENTENCE);
		if (KeyEnter.down()) {
			buyFlag = false;
		}
	}
}

void STORE::KeyGet() {	//キー入力受付関数
	switch (cursor) {
	case BULLET_POWER:
		font32(U"銃弾の威力が上昇します 現在の威力", pstatus->GetBulletPower()).draw(SENTENCE_X, SENTENCE);
		if (KeyUp.down()) {
			cursor = BACK_MAP;
		}
		if (KeyDown.down()) {
			cursor = BULLET_NUM;
		}
		break;

	case BULLET_NUM:
		font32(U"同時に打つことのできる銃弾の数が増えます 最大数:5 現在の弾数:", pstatus->GetBulletsNum()).draw(SENTENCE_X, SENTENCE);
		if (KeyUp.down()) {
			cursor = BULLET_POWER;
		}
		if (KeyDown.down()) {
			cursor = PLAYER_HP;
		}
		break;

	case PLAYER_HP:
		font32(U"プレイヤーのHPが増えます 最大数:6 現在のHP:",pstatus->GetHp()).draw(SENTENCE_X, SENTENCE);
		if (KeyUp.down()) {
			cursor = BULLET_NUM;
		}
		if (KeyDown.down()) {
			cursor = BACK_MAP;
		}
		break;

	case BACK_MAP:

		if (KeyUp.down()) {
			cursor = PLAYER_HP;
		}
		if (KeyDown.down()) {
			cursor = BULLET_POWER;
		}
		break;

	}
	if (KeyEnter.down()) {
		if (cursor != BACK_MAP) {
			buyFlag = true;
		}
		else {
			backMap = true;
		}
	}
}

bool STORE::GetBack() {	//マップに戻るか　true:マップに戻る　false:そのまま
	return backMap;
}
