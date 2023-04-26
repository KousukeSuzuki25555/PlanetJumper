#include "Player.h"

#define GROUND_Y (240)
#define JUMP_GROUND	(Y_MAX - 64)
#define NOT_JUMP_GROUND	(Y_MAX/2-64)
#define GUIDE_X		(456.0f)

PLAYER::PLAYER() {
	pos = { PLAYER_POS_X,PLAYER_POS_Y };		//playerの座標
	uv = { 2,0 };			//g_v 0:上半身以外 1:歩き上半身
	bustUv = { 2,1 };		//上半身のuv値
	anmTime = { 0.0f,0.0f };	//アニメーションに用いる時間変数
	attackTime = { 0.0f,0.0f };	//攻撃アニメーションに用いる時間変数
	action = RUN;			//playerが何をしているか
	jstrength = 0.0f;		//ジャンプの力
	gravity = GRAVITY_NOR;	//ジャンプの抵抗
	jumpLimit = 2;			//ジャンプできる回数
	jumpLimitDefine = 2;	//地面着地時にjumpLimitの初期化に用いる変数
	//g_plus = 1;
	hitFlag = false;		//ヒットしたらtrueとなる
	anmFlag = false;
	drawFlag = true;
	//for (int e = 0; e < 5; e++) {
	//	attackFlag[e] = false;	//球を打っているかの判定に使う　ダン数を増やす場合配列にする
	//}
	attackFlag = false;
	hitNum = 0;
	hitTime = 0.0f;
	gTime = 0.0f;
	hp = 3.0f;
	//foothold = 0.0f;	//足場があるときに足場の高さを入れる
	bulletNum = 0;
	bossFlag = false;
	ground = GROUND_Y;
	power = 0.0f;
}

void PLAYER::PointerInit(GAME_STATUS* pstatus,DRAW* pdraw/*,PLAYER* pplayer*/,MY_TIME* ptime) {
	this->pdraw = pdraw;
	this->pstatus = pstatus;
	weapon.PointerInit(/*pplayer, */pdraw, ptime);
	/*for (int e = 0; e < 5; e++) {
		bullet[e].PointerInit(pdraw);
	}*/
}

WEAPON* PLAYER::GetPweapon() {	//武器クラスのゲッター
	return &weapon;
}

void PLAYER::Init(int weaponNum) {
	this->hp = (float)pstatus->GetHp();
	gravitySource = pstatus->GetGravity();
	bulletNum = (unsigned short)pstatus->GetBulletsNum();
	hitFlag = false;
	pos = { PLAYER_POS_X,PLAYER_POS_Y };
	ground = GROUND_Y;
	drawFlag = true;
	power = 0.0f;
	attackFlag = false;
	weapon.Init(weaponNum, pstatus->GetBulletsNum());
}

void PLAYER::BossInit() {
	bossFlag = true;
	hitFlag = false;
	drawFlag = true;
}

void PLAYER::BossUninit() {
	bossFlag = false;
}

void PLAYER::GuideInit(bool jump) {
	if (jump == true) {
		pos = { GUIDE_X,JUMP_GROUND };
		ground = JUMP_GROUND;
	}
	else {
		pos = { GUIDE_X,NOT_JUMP_GROUND };
		ground = NOT_JUMP_GROUND;
	}
	hitFlag = false;
	drawFlag = true;
}

void PLAYER::GuideUninit() {
	pos= { PLAYER_POS_X,PLAYER_POS_Y };
}

void PLAYER::Update(float now) {
	Anm();
	anmTime.t2 = now;
	attackTime.t2 = now;
	if (KeyJ.down()) {
		JumpSet();
	}
	if (KeySpace.down()) {
		AttackSet(now);
	}

	if (bossFlag == true) {	//ダメージ演出
		if (hitFlag == true) BossstHitAct(now);
	}
	else {
		if (hitFlag == true) HitAct(now);
	}
	//for (int e = 0; e < bulletNum; e++) {
	//	if (bullet[e].GetUse() == true) {
	//		bullet[e].Update(now);
	//	}
	//}
	weapon.Update(pos.y);
}

void PLAYER::Draw() {
	VECTOR2 tempCamera = { 0.0f,0.0f };
	switch (drawFlag) {
	case true:
		pdraw->PlayerDraw(uv, pos);
		pdraw->PlayerDraw(bustUv, pos);
		weapon.Draw(tempCamera.y);
		/*for (int e = 0; e < bulletNum; e++) {
			if (bullet[e].GetUse() == true) {
				bullet[e].Draw(tempCamera);
			}
		}*/
		break;

	case false:
		weapon.Draw(tempCamera.y);
	/*	for (int e = 0; e < bulletNum; e++) {
			if (bullet[e].GetUse() == true) {
				bullet[e].Draw(tempCamera);
			}
		}*/
	}
}

void PLAYER::Draw(float camera) {
	switch (drawFlag) {
	case true:
		this->camera = pos;
		this->camera.y += camera;
		pdraw->PlayerDraw(uv, this->camera);
		pdraw->PlayerDraw(bustUv, this->camera);
		weapon.Draw(camera);
		/*for (int e = 0; e < bulletNum; e++) {
			if (bullet[e].GetUse() == true) {
				bullet[e].Draw(camera);
			}
		}*/
		break;

	case false:
		weapon.Draw(camera);
		/*for (int e = 0; e < bulletNum; e++) {
			if (bullet[e].GetUse() == true) {
				bullet[e].Draw(camera);
			}
		}*/
	}
}

void PLAYER::Draw(VECTOR2 camera) {
	switch (drawFlag) {
	case true:
		this->camera = pos;
		this->camera = this->camera - camera;
		pdraw->PlayerDraw(uv, this->camera);
		pdraw->PlayerDraw(bustUv, this->camera);
		weapon.Draw(camera.y);
		/*for (int e = 0; e < bulletNum; e++) {
			if (bullet[e].GetUse() == true) {
				bullet[e].Draw(camera);
			}
		}*/
		break;

	case false:
		weapon.Draw(camera.y);
		/*for (int e = 0; e < bulletNum; e++) {
			if (bullet[e].GetUse() == true) {
				bullet[e].Draw(camera);
			}
		}*/
	}
}

void PLAYER::Anm() {
	//ジャンプ攻撃中に着地すると弾が2発発射される
	switch (action) {
	case RUN:
		switch (uv.u) {
		case 0:
		case 1:
		{
			if (anmTime.t2 - anmTime.t1 > 0.1) {
				if (uv.u == 0) {
					uv.u++;
				}
				else {
					uv.u--;
				}
			}
			break;
		}
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
		{
			if (anmTime.t2 - anmTime.t1 > 0.1) {
				uv.u ++;
				anmFlag = true;
				if (uv.u >= 10) {
					uv.u = 2;
				}
				anmTime.t1 = anmTime.t2;
			}
			switch (attackFlag) {
			case true: {	//攻撃中
				if (attackTime.t2 - attackTime.t1 > 0.1) {
					bustUv.u++;
					attackTime.t1 = attackTime.t2;
				}
				if (bustUv.u >= 6) {
					AttackUninit();
				}
				anmFlag = false;
				break;
			}
			case false: {
				if (anmFlag == true) {
					bustUv.u = uv.u;
				}
				anmFlag = false;
				break;
			}
			}
			break;	//case9のbreak
		}
		}
		break;		//case RUNのbreak
		return;
	case JUMP:
		//数値積分で落ちるときの距離を求める
		int repeat = (anmTime.t2-gTime) / 0.01;
		for (int e = 0; e < repeat; e++) {
			pos.y -= jstrength;
			jstrength -= gravity;
		}
		gTime = anmTime.t2;
		Land();
		if (anmTime.t2 - anmTime.t1 > 0.1) {
			if (uv.u != 2) {
				uv.u++;
			}
			switch (attackFlag) {
			case true: {
				if (attackTime.t2 - attackTime.t1 > 0.1) {
					bustUv.u++;
					attackTime.t1 = attackTime.t2;
				}
				if (bustUv.u >= 6) {
					AttackUninit();
				}
				break;
			}
			case false: {
				bustUv.u = uv.u;
				break;
			}
			}
		}
		break;		//case JUMPのbreak
		return;
	}
}

void PLAYER::AttackSet(float now) {
	attackTime.t1 = now;
	bustUv.u = 3;
	bustUv.v = 3;
	float a = power * 10 + pstatus->GetBulletPower() * 10;
	weapon.Shot(pos, a, gravity);
	attackFlag = true;
	//if (GetUnuseBullet() != -1) {
	//	float a = power * 10 + pstatus->GetBulletPower() * 10;
	//	weapon.Shot(pos, power, gravity);
	//	//bullet[GetUnuseBullet()].Init(pos, gravity, (int)a);
	//	//attackFlag[GetUnuseBullet()] = true;
	//}
}
void PLAYER::AttackUninit() {
	attackFlag = false;
	bustUv.u = uv.u;
	bustUv.v = 1;
}

void PLAYER::JumpSet() {
	switch (action) {
	case RUN:
		uv.v = 2;
		uv.u = 0;
		bustUv = { 0,3 };
		jstrength = 8.5f;
		action = JUMP;
		jumpLimit = jumpLimitDefine;
		jumpLimit--;
		gTime = (float)clock() / 1000;
		break;

	case JUMP:
		if (jumpLimit > 0) {
			uv.v = 2;
			uv.u = 0;
			bustUv.u = 0;
			bustUv.v = 3;
			jstrength = 5.5f;
			action = JUMP;
			jumpLimit--;
			gTime = (float)clock() / 1000;
		}
		break;
	}

}

void PLAYER::HartDraw() {
	pdraw->HartDraw(hp);
}

void PLAYER::HartDrawBoss() {
	pdraw->HartdrawBoss(hp);
}

void PLAYER::Land() {				//着地したか 着地したらRUNに戻るようにする
	if (pos.y > ground) {
		pos.y = ground;
		action = RUN;
		uv = { 2,0 };
		bustUv.u = 2;
		bustUv.v = 1;
	}
}

VECTOR2 PLAYER::GetPos() {
	if (this->pos.x == NULL && this->pos.y == NULL) {
		VECTOR2 a = { 0.0f,0.0f };
		return a;
	}
	return pos;
}

I_VECTOR2 PLAYER::GetUv() {
	return uv;
}

I_VECTOR2 PLAYER::GetBustUv() {
	return bustUv;
}

void PLAYER::SetStageStatus(int power, unsigned short int limit, unsigned short int strength) {
	if (strength == STRONG) {
		gravity = GRAVITY_WE;
	}
	else if (strength == NORMAL) {
		gravity = GRAVITY_NOR;
	}
	else {
		gravity = GRAVITY_ST;
	}

	if (limit == STRONG) {
		jumpLimitDefine = 3;
	}
	else if (limit == NORMAL) {
		jumpLimitDefine = 2;
	}
	else {
		jumpLimitDefine = 1;
	}

	SetWeaponPower(power);
}

void PLAYER::SetGravity(unsigned short int strength) {
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

void PLAYER::SetJumpLimit(unsigned short int limit) {
	if (limit == STRONG) {
		jumpLimitDefine = 3;
	}
	else if (limit == NORMAL) {
		jumpLimitDefine = 2;
	}
	else {
		jumpLimitDefine = 1;
	}
}

void PLAYER::SetWeaponPower(unsigned short int power) {
	switch(power) {
	case STRONG:
		this->power = 1.0f;
		break;
	case NORMAL:
		this->power = 0.5f;
		break;
	case WEAK:
		this->power = 0.0f;
		break;
	}
}

float PLAYER::GetGrvity() {
	return gravity;
}

void PLAYER::Hit() {
	hitTime= (float)clock() / TIME_DIVIDER;
	hitNum = 0;
	drawFlag = false;
	if (hitFlag == false) {
		hp--;
	}
	hitFlag = true;
}

void PLAYER::Hit(float atk) {
	hitTime = (float)clock() / TIME_DIVIDER;
	drawFlag = false;
	hitNum = 0;
	if (hitFlag == false) {
		hp -= atk;
	}
	hitFlag = true;
}

void PLAYER::BossstHit(float atk,float now) {
	hitTime = now;
	hp -= atk;
	hitFlag = true;
	drawFlag = false;
}

void PLAYER::HitAct(float now) {
	if (now - hitTime > 0.1) {
		hitNum++;
		hitTime = now;
		switch (drawFlag) {
		case true:
			drawFlag = false;
			break;
		case false:
			drawFlag = true;
			break;
		}
		if (hitNum == 3) {
			hitFlag = false;
			drawFlag = true;
		}
	}
}

void PLAYER::BossstHitAct(float now) {
 	if (now - hitTime > 0.1) {
		drawFlag = true;
		hitFlag = false;
	}
}

//VECTOR2 PLAYER::GetBulletPos(int e) {
//	return bullet[e].GetPos();
//}

float PLAYER::GetPos_y() {
	return pos.y;
}

bool PLAYER::GetHitFlag() {
	return hitFlag;
}

//int PLAYER::GetBulletPower(int e) {
//	return bullet[e].GetPower();
//}

float PLAYER::GetHp() {
	return hp;
}

//int PLAYER::GetUnuseBullet() {	//使っていない銃弾を返す
// 	for (int e = 0; e < bulletNum; e++) {
//		if (bullet[e].GetUse() == false) {
//			attackFlag[e] = true;
//			newBullet = e;
//			return e;
//		}
//	}
//	//全部の銃弾を使用していたら0を返す
//	return -1;
//}

//void PLAYER::SetBulletUse(int e) {		//弾が当たった際に呼ばれuseを解除する
//	bullet[e].SetUse();
//}

//bool PLAYER::GetBulletUse(int e) {	//その銃弾が使われているか
//	return bullet[e].GetUse();
//}

//int PLAYER::BulletNotUse() {	//何個銃弾が使われていないか
//	int num=0;
//	for (int e = 0; e < bulletNum; e++) {
//		if (bullet[e].GetUse() == false) {
//			num++;
//		}
//	}
//	return num;
//}
