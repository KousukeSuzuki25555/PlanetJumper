#include "E_Police.h"
#include <time.h>
#include <math.h>

POLICE::POLICE() {
	rotate = 1.4f;
	pos = { 0.0f,0.0f };
	uv.u = 0;
	uv.v = 0;
	bust_uv = { 0,2 };
	anm_time = 0.0f;
	run_time = anm_time;
	attack_time = 0.0f;
	attack_flag = false;
	bullet_hit = false;		//bulletがplayerと当たったらtrue
	gravity = GRAVITY_NOR;	//ジャンプの抵抗
	ppos = 0.0f;
	pdraw = 0;
	pplayer = 0;
	ptime = 0;
}

void POLICE::PointerInit(DRAW* pdraw,PLAYER* pplayer,MY_TIME* ptime) {
	this->pdraw = pdraw;
	bullet.PointerInit(pdraw);
	this->pplayer = pplayer;
	this->ptime = ptime;
}

void POLICE::Init() {
	rotate = 1.4f;
	pos.x = cosf(rotate * PI) * (16 + 1024) + X_MAX / 2 - 200;
	pos.y = sinf(rotate * PI) * (16 + 1024) + 240 + 16 + 2048 / 2;
	attack_time = ptime->GetTime();
	anm_time = attack_time;
}

void POLICE::Update(float speed) {
	/************************************************************************
	攻撃をするかどうか
	*************************************************************************/
	if (ptime->GetTime() - attack_time > 3.0f) {
		attack_flag = true;
		AttackSet();
	}

	/************************************************************************
	前後移動
	*************************************************************************/
	if (speed - 30.0f != 0.0f) {	//スピードが通常時のスピードでないとき前後に移動する
		if (speed - 30.0f < 0) {	//後ろ
			if (rotate > 1.3) {		//rotateが1.3より小さくなる場合それ以下にならないようにする
				rotate -= (ptime->GetTime() - run_time) / (200.0f);
			}
		}
		else if(speed - 30.0f > 0) {	//前
			if (rotate < 1.5) {		//rotateが1.5より大きくなる場合それ以上にならないようにする
				rotate += (ptime->GetTime() - run_time) / (200.0f);
			}
		}
		pos.x = cosf(rotate * PI) * (16 + 1024) + X_MAX / 2 - 200;			//前後移動
		pos.y = sinf(rotate * PI) * (16 + 1024) + 240 + 16 + 2048 / 2;
	}
	run_time = ptime->GetTime();		//時間の経過を入れることで次のフレームで計算できるようにする


	/************************************************************************
	PLAYERとの当たり判定
	*************************************************************************/
	PlayerHit();

	/************************************************************************
	銃弾のアップデート
	*************************************************************************/
	if (bullet.GetUse() == true) {		//銃弾が使われている場合銃弾のアップデート処理をする
		bullet.SetPpos(ppos);
		bullet.Update(ptime->GetTime());
		if (bullet.GetHit() == true) {
			pplayer->Hit(1);
		}
	}

	/************************************************************************
	アニメーション
	*************************************************************************/
	Anm();
	//Draw();
}

void POLICE::Anm() {
	switch (attack_flag) {
	case true:
		if (ptime->GetTime() - anm_time > 0.1) {
			uv.u++;
			if (uv.u == 8) {
				uv.u = 0;
			}
			anm_time = ptime->GetTime();
		}
		if (ptime->GetTime() - attack_time > 0.5) {
			bust_uv.u++;
			if (bust_uv.u == 4) {
				if (bullet.GetUse() == false)
				{
					bullet.Init(pos, gravity,rotate);
				}
			}
			if (bust_uv.u == 5) {
				AttackFin();
			}
			attack_time = ptime->GetTime();
		}
		break;
	case false:
		if (ptime->GetTime() - anm_time > 0.1) {
			uv.u++;
			if (uv.u == 8) {
				uv.u = 0;
			}
			bust_uv.u = uv.u;
			anm_time = ptime->GetTime();
		}
		break;
	}
}

void POLICE::AttackFin() {		//攻撃の終了処理
	bust_uv = { uv.u,2 };		//胸の位置を体と同じにする
	attack_flag = false;
	attack_time = ptime->GetTime();
}

void POLICE::AttackSet() {	//攻撃の開始処理
	bullet_hit = false;
	attack_flag = true;
	bust_uv = { 2,1 };
}

void POLICE::SetGravity(unsigned short int strength) {
	if (strength == STRONG) {
		gravity = GRAVITY_WE;
	}
	else if (strength == NORMAL) {
		gravity = GRAVITY_NOR;
	}
	else {
		gravity = GRAVITY_ST;
	}
}

void POLICE::Draw(float camera) {		//描画をする関数
	this->camera = pos;
	this->camera.y += camera;
	pdraw->PoliceDraw(bust_uv, this->camera);
	pdraw->PoliceDraw(uv, this->camera);
	if (bullet.GetUse() == true) {
		bullet.Draw(camera);
	}
}

void POLICE::SetPpos(float ppos) {
	this->ppos = ppos;
}

float POLICE::GetRot() {
	return rotate;
}

bool POLICE::GetBulletHit() {
	return bullet_hit;

}

void POLICE::RotInit() {
	rotate = 1.4f;
}

VECTOR2 POLICE::GetPos() {
	return pos;
}

I_VECTOR2 POLICE::GetUv() {
	return uv;
}

I_VECTOR2 POLICE::GetBustUv() {
	return bust_uv;
}

void POLICE::PlayerHit() {
	//playerの当たり判定
	I_VECTOR2 size2 = { 10,G_SIZE / 2 };
	if (PlayerHitDetection(pplayer->GetPos(), pos, size2) == true) {
		pplayer->Hit(3);
	}
}

//void POLICE::DetectReset() {
//	for (int e = 0; e < 4; e++) {
//		d_vertex[e] = false;
//	}
//}
