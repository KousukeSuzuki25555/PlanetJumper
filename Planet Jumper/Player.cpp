#include "Player.h"

#define GROUND_Y (240)
#define JUMP_GROUND	(Y_MAX - 64)
#define NOT_JUMP_GROUND	(Y_MAX/2-64)
#define GUIDE_X		(456.0f)

PLAYER::PLAYER() {
	pos = { PLAYER_POS_X,PLAYER_POS_Y };		//playerの座標
	uv = { 2,0 };			//g_v 0:上半身以外 1:歩き上半身
	bust_uv = { 2,1 };		//上半身のuv値
	anm_time = { 0.0f,0.0f };	//アニメーションに用いる時間変数
	attack_time = { 0.0f,0.0f };	//攻撃アニメーションに用いる時間変数
	action = RUN;			//playerが何をしているか
	jstrength = 0.0f;		//ジャンプの力
	gravity = GRAVITY_NOR;	//ジャンプの抵抗
	jump_limit = 2;			//ジャンプできる回数
	jump_limit_define = 2;	//地面着地時にjump_limitの初期化に用いる変数
	//g_plus = 1;
	hit_flag = false;		//ヒットしたらtrueとなる
	anm_flag = false;
	draw_flag = true;
	//for (int e = 0; e < 5; e++) {
	//	attack_flag[e] = false;	//球を打っているかの判定に使う　ダン数を増やす場合配列にする
	//}
	attack_flag = false;
	hit_num = 0;
	hit_time = 0.0f;
	g_time = 0.0f;
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
	gravity_source = pstatus->GetGravity();
	bulletNum = (unsigned short)pstatus->GetBulletsNum();
	hit_flag = false;
	pos = { PLAYER_POS_X,PLAYER_POS_Y };
	ground = GROUND_Y;
	draw_flag = true;
	power = 0.0f;
	attack_flag = false;
	weapon.Init(weaponNum, pstatus->GetBulletsNum());
}

void PLAYER::BossInit() {
	bossFlag = true;
	hit_flag = false;
	draw_flag = true;
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
	hit_flag = false;
	draw_flag = true;
}

void PLAYER::GuideUninit() {
	pos= { PLAYER_POS_X,PLAYER_POS_Y };
}

void PLAYER::Update(float now) {
	Anm();
	anm_time.t2 = now;
	attack_time.t2 = now;
	if (KeyJ.down()) {
		JumpSet();
	}
	if (KeySpace.down()) {
		AttackSet(now);
	}

	if (bossFlag == true) {	//ダメージ演出
		if (hit_flag == true) BossstHitAct(now);
	}
	else {
		if (hit_flag == true) HitAct(now);
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
	switch (draw_flag) {
	case true:
		pdraw->PlayerDraw(uv, pos);
		pdraw->PlayerDraw(bust_uv, pos);
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
	switch (draw_flag) {
	case true:
		this->camera = pos;
		this->camera.y += camera;
		pdraw->PlayerDraw(uv, this->camera);
		pdraw->PlayerDraw(bust_uv, this->camera);
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
	switch (draw_flag) {
	case true:
		this->camera = pos;
		this->camera = this->camera - camera;
		pdraw->PlayerDraw(uv, this->camera);
		pdraw->PlayerDraw(bust_uv, this->camera);
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
			if (anm_time.t2 - anm_time.t1 > 0.1) {
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
			if (anm_time.t2 - anm_time.t1 > 0.1) {
				uv.u ++;
				anm_flag = true;
				if (uv.u >= 10) {
					uv.u = 2;
				}
				anm_time.t1 = anm_time.t2;
			}
			switch (attack_flag) {
			case true: {	//攻撃中
				if (attack_time.t2 - attack_time.t1 > 0.1) {
					bust_uv.u++;
					attack_time.t1 = attack_time.t2;
				}
				if (bust_uv.u >= 6) {
					AttackUninit();
				}
				anm_flag = false;
				break;
			}
			case false: {
				if (anm_flag == true) {
					bust_uv.u = uv.u;
				}
				anm_flag = false;
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
		int repeat = (anm_time.t2-g_time) / 0.01;
		for (int e = 0; e < repeat; e++) {
			pos.y -= jstrength;
			jstrength -= gravity;
		}
		g_time = anm_time.t2;
		Land();
		if (anm_time.t2 - anm_time.t1 > 0.1) {
			if (uv.u != 2) {
				uv.u++;
			}
			switch (attack_flag) {
			case true: {
				if (attack_time.t2 - attack_time.t1 > 0.1) {
					bust_uv.u++;
					attack_time.t1 = attack_time.t2;
				}
				if (bust_uv.u >= 6) {
					AttackUninit();
				}
				break;
			}
			case false: {
				bust_uv.u = uv.u;
				break;
			}
			}
		}
		break;		//case JUMPのbreak
		return;
	}
}

void PLAYER::AttackSet(float now) {
	attack_time.t1 = now;
	bust_uv.u = 3;
	bust_uv.v = 3;
	float a = power * 10 + pstatus->GetBulletPower() * 10;
	weapon.Shot(pos, a, gravity);
	attack_flag = true;
	//if (GetUnuseBullet() != -1) {
	//	float a = power * 10 + pstatus->GetBulletPower() * 10;
	//	weapon.Shot(pos, power, gravity);
	//	//bullet[GetUnuseBullet()].Init(pos, gravity, (int)a);
	//	//attack_flag[GetUnuseBullet()] = true;
	//}
}
void PLAYER::AttackUninit() {
	attack_flag = false;
	bust_uv.u = uv.u;
	bust_uv.v = 1;
}

void PLAYER::JumpSet() {
	switch (action) {
	case RUN:
		uv.v = 2;
		uv.u = 0;
		bust_uv = { 0,3 };
		jstrength = 8.5f;
		action = JUMP;
		jump_limit = jump_limit_define;
		jump_limit--;
		g_time = (float)clock() / 1000;
		break;

	case JUMP:
		if (jump_limit > 0) {
			uv.v = 2;
			uv.u = 0;
			bust_uv.u = 0;
			bust_uv.v = 3;
			jstrength = 5.5f;
			action = JUMP;
			jump_limit--;
			g_time = (float)clock() / 1000;
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
		bust_uv.u = 2;
		bust_uv.v = 1;
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
	return bust_uv;
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
		jump_limit_define = 3;
	}
	else if (limit == NORMAL) {
		jump_limit_define = 2;
	}
	else {
		jump_limit_define = 1;
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
		jump_limit_define = 3;
	}
	else if (limit == NORMAL) {
		jump_limit_define = 2;
	}
	else {
		jump_limit_define = 1;
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
	hit_time= (float)clock() / TIME_DIVIDER;
	hit_num = 0;
	draw_flag = false;
	if (hit_flag == false) {
		hp--;
	}
	hit_flag = true;
}

void PLAYER::Hit(float atk) {
	hit_time = (float)clock() / TIME_DIVIDER;
	draw_flag = false;
	hit_num = 0;
	if (hit_flag == false) {
		hp -= atk;
	}
	hit_flag = true;
}

void PLAYER::BossstHit(float atk,float now) {
	hit_time = now;
	hp -= atk;
	hit_flag = true;
	draw_flag = false;
}

void PLAYER::HitAct(float now) {
	if (now - hit_time > 0.1) {
		hit_num++;
		hit_time = now;
		switch (draw_flag) {
		case true:
			draw_flag = false;
			break;
		case false:
			draw_flag = true;
			break;
		}
		if (hit_num == 3) {
			hit_flag = false;
			draw_flag = true;
		}
	}
}

void PLAYER::BossstHitAct(float now) {
 	if (now - hit_time > 0.1) {
		draw_flag = true;
		hit_flag = false;
	}
}

//VECTOR2 PLAYER::GetBulletPos(int e) {
//	return bullet[e].GetPos();
//}

float PLAYER::GetPos_y() {
	return pos.y;
}

bool PLAYER::GetHitFlag() {
	return hit_flag;
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
//			attack_flag[e] = true;
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
