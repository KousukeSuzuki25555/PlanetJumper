﻿#include "StageBoss.h"

BossSt::BossSt() {	//コンストラクタ
	//pplayer = &player;
	camera = { 0.0f,0.0f };
	speedValue = SPEED_NOR;
	bulletHit = false;
	state = PLAY;
	pdraw = 0;
	pplayer = 0;
	pground = 0;
}

void BossSt::PointerInit(DRAW* pdraw,PLAYER* pplayer,GROUND* pground,MY_TIME* ptime,GAME_STATUS* pstatus) {
	this->pdraw = pdraw;
	this->pplayer = pplayer;
	this->pground = pground;
	this->ptime = ptime;
	this->pstatus = pstatus;
	//this->pstatus = pstatus;
	pplayer->PointerInit(pstatus,pdraw/*,pplayer*/,ptime);
	this->pweapon = pplayer->GetPweapon();
	pticket->PointerInit(pdraw, pstatus);
	icon.PointerInit(pdraw);
	clear.Init(pticket);
	dragon.PointerInit(pdraw,pticket,pplayer,ptime,pstatus,pweapon);
}

void BossSt::Init() {		//ステージに入る際の初期化処理
	pplayer->Init(0);
	pplayer->BossInit();
	dragon.Init(pstatus->GetBulletsNum());
	state = PLAY;
	pticket->Init();
}

void BossSt::Uninit() {		//ステージから抜けるときの処理
	pplayer->BossUninit();
}

void BossSt::Update(GAME_STATUS* pstatus,float now) {
	switch (state) {
	/******************************************************************************
	ゲームプレイ中の処理
	*******************************************************************************/
	case PLAY: {
		if (KeyEnter.down()) {
			state = ST_MAP;
		}
		/******************************************************************************
		ICONの処理
		*******************************************************************************/
		icon.Update();						//アイコンのアップデート
		speedValue = icon.GetSpeedValue();

		/******************************************************************************
		PLAYERの処理
		*******************************************************************************/
		//player.SetGravity(icon.GetGravity());		//playerに重力をセット
		//player.SetJumpLimit(icon.GetJump());		//playerにジャンプをセット
		//player.SetWeaponPower(icon.GetWeapon());

		pplayer->SetStageStatus(icon.GetWeapon(), icon.GetJump(), icon.GetGravity());	//playerにステージのステータスを入力

		pplayer->Update(now);				//playerのアップデート

		dragon.SetSpeed(speedValue);
		dragon.Update();

		/******************************************************************************
		TICKETの処理
		*******************************************************************************/

		/******************************************************************************
		描画
		*******************************************************************************/
		Draw();

		/******************************************************************************
		GAMEOVERか
		*******************************************************************************/
		if (pplayer->GetHp()<=0) {
			state = ST_GAMEOVER;
		}

		/******************************************************************************
		CLEARか
		*******************************************************************************/
		if (dragon.GetHp() <= 0 ) {
			state = ST_CLEAR;
			pticket->SetStatus();
		}

		break;
	}

	/******************************************************************************
	ゲームオーバーの処理
	*******************************************************************************/
	case ST_GAMEOVER: {

		gameover.Update();
		if (KeyEnter.down()) {
			bool go_state = gameover.GetCursor();
			switch (go_state) {
			case true:
				state = PLAY;
				Init();
				dragon.Init(pstatus->GetBulletsNum());
				break;
			case false:
				state = ST_MAP;
				break;
			}
		}
		break;
	}
	
	/******************************************************************************
	ゲームクリアの処理
	*******************************************************************************/
	case ST_CLEAR: {

		clear.Update();
		if (KeyEnter.down()) {
			bool go_state = clear.GetCursor();
			switch (go_state) {
			case true:
				state = PLAY;
				Init();
				dragon.Init(pstatus->GetBulletsNum());
				break;
			case false:
				state = ST_MAP;
				break;
			}
		}
		break;
	}
	}
}

void BossSt::Draw() {	//描画処理関数
	VECTOR2 dIsAttack = { 0.0f,0.0f };
	VECTOR2 dPos = dragon.CameraPos();
	if (dIsAttack.x==dPos.x&&dIsAttack.y==dPos.y) {
		camera = { 0.0f,0.0f };
	}
	else {
		this->camera = dPos;
	}
	pdraw->BossBackDraw();
	pground->Draw(camera);
	pplayer->Draw(camera);
	dragon.Draw(camera);
	pplayer->HartDrawBoss();
	icon.Draw();
	pticket->Draw(true);
	pdraw->BulletDisp(pweapon->GetNotUseBullet());
}

bool BossSt::GetMap() {	//Mapに戻るかどうかを返す関数　true:mapへ　false:bossステージのまま
	if (state == ST_MAP) {
		return true;
	}
	else {
		return false;
	}
}
