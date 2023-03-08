#include "Stage2.h"

STAGE2::STAGE2() {	//初期化
	block_size[0] = { 128,64 };
	block_size[1] = { 32,32 };
	block_size[2] = { 64,64 };
	block_size[3] = { 64,64 };
	block_size[4] = { 128,64 };
	block_size[5] = { 64,64 };
	block_size[6] = { 64,64 };
	block_size[7] = { 128,128 };
	block_size[8] = { 32,32 };
	block_size[9] = { 64,64 };
	block_size[10] = { 32,32 };
	block_size[11] = { 128,64 };
	block_size[12] = { 128,64 };
	block_size[13] = { 128,128 };
	block_size[14] = { 32,32 };
	block_size[15] = { 128,128 };
	block_size[16] = { 128,128 };
}

STAGE2::~STAGE2() {
	delete pticket;
}

void STAGE2::PointerInit(DRAW* pdraw, PLAYER* pplayer,MY_TIME* ptime,GAME_STATUS* pstatus) {	//ポインタの初期化
	this->pplayer = pplayer;
	this->pdraw = pdraw;
	this->ptime = ptime;
	this->pstatus = pstatus;
	pplayer->DrawPointerInit(pdraw);
	police.PointerInit(pdraw, pplayer,ptime);
	icon.PointerInit(pdraw);
	ground.PointerInit(pdraw);
	f_clear.PointerInit(pdraw);
	for (int e = 0; e < CROW_MAX; e++) {
		crow[e].PointerInit(pdraw, pplayer,pticket,ptime);
	}
	for (int e = 0; e < BLOCK_MAX; e++) {
		block[e].PointerInit(pdraw, pplayer);
	}
	for (int e = 0; e < TIGER_MAX; e++) {
		tiger[e].PointerInit(pdraw, pplayer,pticket,ptime);
	}
	clear.Init(pticket);
}
void STAGE2::Init() {
	time = ptime->GetTime();
	meter_time = ptime->GetTime();
	pplayer->Init(pstatus);
	pticket->PointerInit(pdraw, pstatus);
	police.Init();
	rot = 0.0f;
	block[0].Init(SPEED_NOR, 1.7f, block_size[0], 128, 0, pstatus->GetBulletsNum());
	block[1].Init(SPEED_NOR, 1.8f, block_size[1], 256, 64, pstatus->GetBulletsNum());
	block[2].Init(SPEED_NOR, 1.9f, block_size[2], 256, 0, pstatus->GetBulletsNum());
	block[3].Init(SPEED_NOR, 0.0f, block_size[3], 256, 0, pstatus->GetBulletsNum());
	block[4].Init(SPEED_NOR, 0.1f, block_size[4], 128, 64, pstatus->GetBulletsNum());
	block[5].Init(SPEED_NOR, 0.2f, block_size[5], 256, 0, pstatus->GetBulletsNum());
	block[6].Init(SPEED_NOR, 0.3f, block_size[6], 256, 0, pstatus->GetBulletsNum());
	block[7].Init(SPEED_NOR, 0.4f, block_size[7], 0, 0, pstatus->GetBulletsNum());
	block[8].Init(SPEED_NOR, 0.5f, block_size[8], 288, 64, pstatus->GetBulletsNum());
	block[9].Init(SPEED_NOR, 0.6f, block_size[9], 256, 0, pstatus->GetBulletsNum());
	block[10].Init(SPEED_NOR, 0.7f, block_size[10], 288, 64, pstatus->GetBulletsNum());
	block[11].Init(SPEED_NOR, 0.8f, block_size[11], 128, 64, pstatus->GetBulletsNum());
	block[12].Init(SPEED_NOR, 0.9f, block_size[12], 128, 0, pstatus->GetBulletsNum());
	block[13].Init(SPEED_NOR, 1.0f, block_size[13],0, 0, pstatus->GetBulletsNum());
	block[14].Init(SPEED_NOR, 1.1f, block_size[14], 256, 96, pstatus->GetBulletsNum());
	block[15].Init(SPEED_NOR, 1.2f, block_size[15], 0, 0, pstatus->GetBulletsNum());
	block[16].Init(SPEED_NOR, 1.4f, block_size[16], 0, 0, pstatus->GetBulletsNum());

	tiger[0].Init(1.7f,pstatus->GetBulletsNum());
	tiger[1].Init(2.0f, pstatus->GetBulletsNum());
	tiger[2].Init(2.5f, pstatus->GetBulletsNum());
	tiger[3].Init(3.0f, pstatus->GetBulletsNum());
	tiger[4].Init(3.4f, pstatus->GetBulletsNum());
	tiger[5].Init(2.7f, pstatus->GetBulletsNum());

	crow[0].Init(1.9f, pstatus->GetBulletsNum());
	crow[1].Init(2.6f, pstatus->GetBulletsNum());
	crow[2].Init(3.0f, pstatus->GetBulletsNum());
	state = PLAY;
	pticket->Init();
	icon.Init();
}
void  STAGE2::Update() {
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
		for (int e = 0; e < BLOCK_MAX; e++) {
			block[e].SetSpeed(icon.GetSpeedValue());
			block[e].Update(rot);
		}

		/******************************************************************************
		虎の処理
		*******************************************************************************/
		for (int e = 0; e < TIGER_MAX; e++) {
			if (tiger[e].GetExist() == true) {
				tiger[e].Update();
			}
		}

		/******************************************************************************
		カラスの処理
		*******************************************************************************/
		for (int e = 0; e < CROW_MAX; e++) {
			if (crow[e].GetExist() == true) {
				crow[e].Update();
			}
		}

		/******************************************************************************
		WINDOWの処理
		*******************************************************************************/
		if (ptime->GetTime() - meter_time > 0.5f) {
			switch (meter_anm) {
			case true:
				meter_anm = false;
				break;

			case false:
				meter_anm = true;
				break;
			}
			meter_time = ptime->GetTime();
		}
		/******************************************************************************
		GameOver,Clearか
		*******************************************************************************/
		if (pplayer->GetHp() <= 0) {
			state = ST_GAMEOVER;
		}
		if (rot <-1.95) {
			state = ST_CLEAR;
			pticket->SetStatus();
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
				if (pstatus->GetStageFlag(2) == false) {	//初クリアならチケットを獲得する
					pstatus->SetTicket(pstatus->GetTicket()+1);
					pstatus->SetStageFlag(true, 2);
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
		f_clear.Update();
		if (KeyEnter.down()) {
			state = ST_MAP;
		}
		break;
	}
}
void  STAGE2::Draw() {
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
	for (int e = 0; e < BLOCK_MAX; e++) {
		block[e].Draw(camera);
	}
	for (int e = 0; e < TIGER_MAX; e++) {
		if (tiger[e].GetExist() == true) {
			tiger[e].Draw(camera);
		}
	}
	for (int e = 0; e < CROW_MAX; e++) {
		if (crow[e].GetExist() == true) {
			crow[e].Draw(camera);
		}
	}

	pdraw->WindowDraw(meter_anm, police.GetRot());			//ウィンドウの描画
	pplayer->HartDraw();
	icon.Draw();
	pticket->Draw(false);
	pdraw->BulletDisp(pplayer->BulletNotUse());
}
