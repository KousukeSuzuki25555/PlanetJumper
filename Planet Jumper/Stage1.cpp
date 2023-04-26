#include "Stage1.h"

STAGE1::STAGE1() {
	camera = 0.0f;
	//now = (float)clock() / 1000;
	meterTime = 0.0f;
	rot = 0.0f;
	time = 0.0f;
	meterAnm = false;
	bulletHit = false;
	block_size[0] = {32,32};
	block_size[1] = { 32,32 };
	block_size[2] = { 32,32 };
	block_size[3] = { 64,64 };
	block_size[4] = { 32,32 };
	block_size[5] = { 64,64 };
	block_size[6] = { 64,64 };
	block_size[7] = { 32,32 };
	block_size[8] = { 64,64 };
	block_size[9] = { 128,128 };
	block[0].Init(SPEED_NOR, 1.7f, block_size[0], 256, 64,0);
	block[1].Init(SPEED_NOR, 1.8f, block_size[1], 288, 64,0);
	block[2].Init(SPEED_NOR, 1.9f, block_size[2], 256, 96,0);
	block[3].Init(SPEED_NOR, 2.0f, block_size[3], 256, 0,0);
	block[4].Init(SPEED_NOR, 2.1f, block_size[4], 288, 96,0);
	block[5].Init(SPEED_NOR, 2.2f, block_size[5], 256, 0,0);
	block[6].Init(SPEED_NOR, 2.3f, block_size[6], 256, 0,0);
	block[7].Init(SPEED_NOR, 2.4f, block_size[7], 288, 64,0);
	block[8].Init(SPEED_NOR, 2.5f, block_size[8], 256, 0,0);
	block[9].Init(SPEED_NOR, 2.6f, block_size[9], 0, 0,0);
	state = PLAY;
	pticket = &ticket;
}

void STAGE1::PointerInit(DRAW* pdraw,PLAYER* pplayer,MY_TIME* ptime, GAME_STATUS* pstatus) {
	this->pplayer = pplayer;
	this->pdraw = pdraw;
	this->ptime = ptime;
	this->pstatus = pstatus;
	pplayer->PointerInit(pstatus,pdraw/*,pplayer*/,ptime);
	pweapon = pplayer->GetPweapon();
	for (int e = 0; e < 10; e++) {
		block[e].PointerInit(pdraw,pplayer,pweapon);
	}
	police.PointerInit(pdraw,pplayer,ptime);
	icon.PointerInit(pdraw);
	ground.PointerInit(pdraw);
	fClear.PointerInit(pdraw);
	clear.Init(pticket);
}

void STAGE1::Init() {
	time = ptime->GetTime();
	meterTime = ptime->GetTime();
	pplayer->Init(0);
	police.Init();
	ticket.PointerInit(pdraw,pstatus);
	rot = 0.0f;
	block[0].Init(SPEED_NOR, 1.7f, block_size[0], 256, 64,pstatus->GetBulletsNum());
	block[1].Init(SPEED_NOR, 1.8f, block_size[1], 288, 64,pstatus->GetBulletsNum());
	block[2].Init(SPEED_NOR, 1.9f, block_size[2], 256, 96,pstatus->GetBulletsNum());
	block[3].Init(SPEED_NOR, 2.0f, block_size[3], 256, 0, pstatus->GetBulletsNum());
	block[4].Init(SPEED_NOR, 2.1f, block_size[4], 288, 96, pstatus->GetBulletsNum());
	block[5].Init(SPEED_NOR, 2.2f, block_size[5], 256, 0, pstatus->GetBulletsNum());
	block[6].Init(SPEED_NOR, 2.3f, block_size[6], 256, 0, pstatus->GetBulletsNum());
	block[7].Init(SPEED_NOR, 2.4f, block_size[7], 288, 64, pstatus->GetBulletsNum());
	block[8].Init(SPEED_NOR, 2.5f, block_size[8], 256, 0, pstatus->GetBulletsNum());
	block[9].Init(SPEED_NOR, 2.6f, block_size[9], 0, 0, pstatus->GetBulletsNum());
	state = PLAY;
	icon.Init();
}

void STAGE1::Update() {
	switch (state) {
	case PLAY: {
		if (KeyEnter.down()) {
			state = ST_MAP;
		}
		/******************************************************************************
		フレームごとのステージの標準的な処理
		*******************************************************************************/

		rot -= (ptime->GetTime() - time) / icon.GetSpeedValue();		//ステージで使う回転の基準
		time = ptime->GetTime();
		/******************************************************************************
		ICONの処理
		*******************************************************************************/
		icon.Update();						//アイコンのアップデート
		/******************************************************************************
		POLICEの処理
		*******************************************************************************/
		police.SetGravity(icon.GetGravity());
		police.SetPpos(pplayer->GetPos_y());
		police.Update(icon.GetSpeedValue());

		/******************************************************************************
		PLAYERの処理
		*******************************************************************************/
		pplayer->SetGravity(icon.GetGravity());		//playerに重力をセット
		pplayer->SetJumpLimit(icon.GetJump());		//playerにジャンプをセット
		pplayer->SetWeaponPower(icon.GetWeapon());
		pplayer->Update(ptime->GetTime());				//playerのアップデート
		/******************************************************************************
		BLOCKの処理
		*******************************************************************************/
		for (int e = 0; e < 10; e++) {
			block[e].SetSpeed(icon.GetSpeedValue());
			block[e].Update(rot);
		}
		/******************************************************************************
		WINDOWの処理
		*******************************************************************************/
		if (ptime->GetTime() - meterTime > 0.5f) {
			switch (meterAnm) {
			case true:
				meterAnm = false;
				break;

			case false:
				meterAnm = true;
				break;
			}
			meterTime = ptime->GetTime();
		}

		/******************************************************************************
		GameOver,Clearか
		*******************************************************************************/
		if (pplayer->GetHp() <= 0) {
			state = ST_GAMEOVER;
		}
		if (rot < -1.2) {
			state = ST_CLEAR;
		}
		/******************************************************************************
		描画の処理
		*******************************************************************************/
		Draw();
		break;
	}
		/******************************************************************************
		GameOverの処理
		*******************************************************************************/
	case ST_GAMEOVER:
		gameover.Update();
		if (KeyEnter.down()) {
			bool go_state = gameover.GetCursor();
			switch (go_state) {
			case true:
				state = PLAY;
				Init();
				break;
			case false:
				state = ST_MAP;
				break;
			}
		}
		break;
		/******************************************************************************
		GameClearの処理
		*******************************************************************************/
	case ST_CLEAR:
		clear.Update();
		if (KeyEnter.down()) {
			bool go_state = clear.GetCursor();
			switch (go_state) {
			case true:
				state = PLAY;
				Init();
				break;
			case false:
				if (pstatus->GetStageFlag(1) == false) {	//初クリアならチケットを獲得する
					pstatus->SetTicket(1);
					pstatus->SetStageFlag(true, 1);
					state = ST_FIRST_CLEAR;
				}
				else {
					state = ST_MAP;
				}
				break;
			}
		}
		break;
		/******************************************************************************
		初クリア時の処理
		*******************************************************************************/
	case ST_FIRST_CLEAR:
		fClear.Update();
		if (KeyEnter.down()) {
			state = ST_MAP;
		}
		break;
	}
}

void STAGE1::Draw() {
	if (pplayer->GetPos_y() < 64.0f) {
		camera = 64 - pplayer->GetPos_y();
	}
	else {
		camera = 0.0f;
	}
	pdraw->BackDraw();
	ground.Draw(camera);
	pplayer->Draw(camera);
	police.Draw(camera);
	for (int e = 0; e < 10; e++) {
		block[e].Draw(camera);
	}
	pdraw->WindowDraw(meterAnm, police.GetRot());			//ウィンドウの描画
	pplayer->HartDraw();
	icon.Draw();
	ticket.Draw(false);
	pdraw->BulletDisp(pweapon->GetNotUseBullet());
}

bool STAGE1::GetMap() {
	if (state == ST_MAP) {
		return true;
	}
	else {
		return false;
	}
}
