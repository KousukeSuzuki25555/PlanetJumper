#include "E_Dragon.h"
#include <Math.h>

#define WAVE_DIV	(20)	//大きくするとウエーブアニメーションが小さくなる　初期値10
#define D_BOX_HP	(3)		//boxごとのhp
#define D_Y_MAX		(384)	//絵の横幅
#define ATTACK1_TIME	(2)	//何秒でATTACK1の次のモーションに移るか
#define ATTACK2_ROT	(0.2f)
#define DRAGON_HP	(30)
#define DRFON_RADIUS	(RADIUS +95.0f)
#define PLAYER_FOOT_X	(440)
#define PLAYER_FOOT_Y	(220)

Dragon::Dragon() {
	for (int e = 0; e < 11; e++) {	//DragonBoxの配列に値を入れる
		switch (e) {	
		case 0:
			d_box[e] = { {0.0f,0.0f},{32* D_GRA_SIZE/D_SIZE,14 * D_GRA_SIZE / D_SIZE},0.0f,0.0f,D_BOX_HP ,0,true};
			break;
		case 1:
			d_box[e] = { {0.0f,0.0f},{16 * D_GRA_SIZE / D_SIZE,14 * D_GRA_SIZE / D_SIZE},0.0f,0.0f,D_BOX_HP ,0,true };
			break;
		case 2:
			d_box[e] = { {0.0f,0.0f},{16 * D_GRA_SIZE / D_SIZE,13 * D_GRA_SIZE / D_SIZE},0.0f,0.0f,D_BOX_HP ,0,true };
			break;
		case 3:
			d_box[e] = { {0.0f,0.0f},{16 * D_GRA_SIZE / D_SIZE,12 * D_GRA_SIZE / D_SIZE},0.0f,0.0f,D_BOX_HP ,0,true };
			break;
		case 4:
			d_box[e] = { {0.0f,0.0f},{16 * D_GRA_SIZE / D_SIZE,11 * D_GRA_SIZE / D_SIZE},0.0f,0.0f,D_BOX_HP ,0,true };
			break;
		case 5:
			d_box[e] = { {0.0f,0.0f},{16 * D_GRA_SIZE / D_SIZE,10 * D_GRA_SIZE / D_SIZE},0.0f,0.0f,D_BOX_HP ,0,true };
			break;
		case 6:
			d_box[e] = { {0.0f,0.0f},{16 * D_GRA_SIZE / D_SIZE,9 * D_GRA_SIZE / D_SIZE},0.0f,0.0f,D_BOX_HP ,0,true };
			break;
		case 7:
			d_box[e] = { {0.0f,0.0f},{16 * D_GRA_SIZE / D_SIZE,8 * D_GRA_SIZE / D_SIZE},0.0f,0.0f,D_BOX_HP ,0,true };
			break;
		case 8:
			d_box[e] = { {0.0f,0.0f},{16 * D_GRA_SIZE / D_SIZE,6 * D_GRA_SIZE / D_SIZE},0.0f,0.0f,D_BOX_HP ,0,true };
			break;
		case 9:
			d_box[e] = { {0.0f,0.0f},{16 * D_GRA_SIZE / D_SIZE,5 * D_GRA_SIZE / D_SIZE},0.0f,0.0f,D_BOX_HP ,0,true };
			break;
		case 10:
			d_box[e] = { {0.0f,0.0f},{16 * D_GRA_SIZE / D_SIZE,4 * D_GRA_SIZE / D_SIZE},0.0f,0.0f,D_BOX_HP ,0,true };
			break;
		}
	}
	time = 0.0f;
	rot = 1.6f;		//角度　1.5fで真上
	addRot = 0.0f;
	radius = DRFON_RADIUS;		//ステージの中心からの距離(ステージからの高さになる)
	anm_time = 0.0f;	//アニメーションに用いる時間
	attack_time = anm_time;
	hitPos[0] = { 0.0f,0.0f };	//当たり判定に用いる　仮の頂点を持つのに用いる
	hitPos[1] = { 0.0f,0.0f };
	for (int e = 0; e < 4; e++) {
		d_vertex[e] = false;
		p_vertex[e] = { 0.0f,0.0f };
		hitPos[e] = { 0.0f,0.0f };
	}
	atk = 3.0f;	//攻撃力
	camera = { 0.0f,0.0f };
	ppos = { PLAYER_FOOT_X,PLAYER_FOOT_Y };
	attackFlag = false;
	attackTradition = false;
	moveMs = 0.0f;
	rotMs = 0.0f;
	speed = SPEED_NOR;
	radiusGoal = 0.0f;
	timeMs = 0.0f;
	attack1FirstBox = 0;
	firstBox = 0;
	pdraw = 0;
	bulletNum = 0;
	cameraSave = { 0.0f,0.0f };
	playerHit = false;
	cameraFlag = false;
	attackState=DST1;
	form = FIRST_FORM;
	state = DST_NORMAL;
	hp = DRAGON_HP;
	dragonState = false;
	state2Init;
	witchAttack = false;
}

void Dragon::PointerInit(DRAW* pdraw, Ticket* pticket, PLAYER* pplayer, MY_TIME* ptime, GAME_STATUS* pstatus) {
	this->pdraw = pdraw;
	this->pticket = pticket;
	this->pplayer = pplayer;
	this->ptime = ptime;
	this->pstatus = pstatus;
	for (int e = 0; e < 9; e++) {
		spine[e].PointerInit(pdraw);
	}
}

void Dragon::State2Init() {
	for (int e = 0; e < 11; e++) {	//DragonBoxの配列に値を入れる
		switch (e) {
		case 0:
			d_box[e] = { {0.0f,0.0f},{32 * D_GRA_SIZE / D_SIZE,14 * D_GRA_SIZE / D_SIZE},0.0f,0.0f,D_BOX_HP ,1,true };
			break;
		case 1:
			d_box[e] = { {0.0f,0.0f},{16 * D_GRA_SIZE / D_SIZE,14 * D_GRA_SIZE / D_SIZE},0.0f,0.0f,D_BOX_HP ,1,true };
			break;
		case 2:
			d_box[e] = { {0.0f,0.0f},{16 * D_GRA_SIZE / D_SIZE,13 * D_GRA_SIZE / D_SIZE},0.0f,0.0f,D_BOX_HP ,1,true };
			break;
		case 3:
			d_box[e] = { {0.0f,0.0f},{16 * D_GRA_SIZE / D_SIZE,12 * D_GRA_SIZE / D_SIZE},0.0f,0.0f,D_BOX_HP ,1,true };
			break;
		case 4:
			d_box[e] = { {0.0f,0.0f},{16 * D_GRA_SIZE / D_SIZE,11 * D_GRA_SIZE / D_SIZE},0.0f,0.0f,D_BOX_HP ,1,true };
			break;
		case 5:
			d_box[e] = { {0.0f,0.0f},{16 * D_GRA_SIZE / D_SIZE,10 * D_GRA_SIZE / D_SIZE},0.0f,0.0f,D_BOX_HP ,1,true };
			break;
		case 6:
			d_box[e] = { {0.0f,0.0f},{16 * D_GRA_SIZE / D_SIZE,9 * D_GRA_SIZE / D_SIZE},0.0f,0.0f,D_BOX_HP ,1,true };
			break;
		case 7:
			d_box[e] = { {0.0f,0.0f},{16 * D_GRA_SIZE / D_SIZE,8 * D_GRA_SIZE / D_SIZE},0.0f,0.0f,D_BOX_HP ,1,true };
			break;
		case 8:
			d_box[e] = { {0.0f,0.0f},{16 * D_GRA_SIZE / D_SIZE,6 * D_GRA_SIZE / D_SIZE},0.0f,0.0f,D_BOX_HP ,1,true };
			break;
		case 9:
			d_box[e] = { {0.0f,0.0f},{16 * D_GRA_SIZE / D_SIZE,5 * D_GRA_SIZE / D_SIZE},0.0f,0.0f,D_BOX_HP ,1,true };
			break;
		case 10:
			d_box[e] = { {0.0f,0.0f},{16 * D_GRA_SIZE / D_SIZE,4 * D_GRA_SIZE / D_SIZE},0.0f,0.0f,D_BOX_HP ,1,true };
			break;
		}
	}
}

void Dragon::Init(int bulletNum) {
	for (int e = 0; e < 11; e++) {	//DragonBoxの配列に値を入れる
		switch (e) {
		case 0:
			d_box[e] = { {0.0f,0.0f},{32 * D_GRA_SIZE / D_SIZE,14 * D_GRA_SIZE / D_SIZE},0.0f,0.0f,D_BOX_HP ,0,true };
			break;
		case 1:
			d_box[e] = { {0.0f,0.0f},{16 * D_GRA_SIZE / D_SIZE,14 * D_GRA_SIZE / D_SIZE},0.0f,0.0f,D_BOX_HP ,0,true };
			break;
		case 2:
			d_box[e] = { {0.0f,0.0f},{16 * D_GRA_SIZE / D_SIZE,13 * D_GRA_SIZE / D_SIZE},0.0f,0.0f,D_BOX_HP ,0,true };
			break;
		case 3:
			d_box[e] = { {0.0f,0.0f},{16 * D_GRA_SIZE / D_SIZE,12 * D_GRA_SIZE / D_SIZE},0.0f,0.0f,D_BOX_HP ,0,true };
			break;
		case 4:
			d_box[e] = { {0.0f,0.0f},{16 * D_GRA_SIZE / D_SIZE,11 * D_GRA_SIZE / D_SIZE},0.0f,0.0f,D_BOX_HP ,0,true };
			break;
		case 5:
			d_box[e] = { {0.0f,0.0f},{16 * D_GRA_SIZE / D_SIZE,10 * D_GRA_SIZE / D_SIZE},0.0f,0.0f,D_BOX_HP ,0,true };
			break;
		case 6:
			d_box[e] = { {0.0f,0.0f},{16 * D_GRA_SIZE / D_SIZE,9 * D_GRA_SIZE / D_SIZE},0.0f,0.0f,D_BOX_HP ,0,true };
			break;
		case 7:
			d_box[e] = { {0.0f,0.0f},{16 * D_GRA_SIZE / D_SIZE,8 * D_GRA_SIZE / D_SIZE},0.0f,0.0f,D_BOX_HP ,0,true };
			break;
		case 8:
			d_box[e] = { {0.0f,0.0f},{16 * D_GRA_SIZE / D_SIZE,6 * D_GRA_SIZE / D_SIZE},0.0f,0.0f,D_BOX_HP ,0,true };
			break;
		case 9:
			d_box[e] = { {0.0f,0.0f},{16 * D_GRA_SIZE / D_SIZE,5 * D_GRA_SIZE / D_SIZE},0.0f,0.0f,D_BOX_HP ,0,true };
			break;
		case 10:
			d_box[e] = { {0.0f,0.0f},{16 * D_GRA_SIZE / D_SIZE,4 * D_GRA_SIZE / D_SIZE},0.0f,0.0f,D_BOX_HP ,0,true };
			break;
		}
	}
	hp = DRAGON_HP;
	attackFlag = false;
	attackTradition = false;
	playerHit = false;
	cameraFlag = false;
	time = ptime->GetTime();
	DetectReset();
	for (int e = 0; e < 9; e++) {
		spine[e].Reset();
	}
	this->bulletNum = bulletNum;
	dragonState = false;
	state2Init = false;
	witchAttack = false;
	anm_time = ptime->GetTime();
	attack_time = ptime->GetTime();
	radius = DRFON_RADIUS;		//ステージの中心からの距離(ステージからの高さになる)
	state = DST_NORMAL;
}

void Dragon::Update() {
	//角度の処理
	if (state == DST_NORMAL) {
		if (speed == SPEED_FAST) {
			rot -= 0.0005f;
		}
		else if (speed == SPEED_SLOW) {
			rot += 0.0005f;
		}
	}

	switch (state) {
	case DST_NORMAL:
		break;
	case DST_ATTACK1:
		switch (attackFlag) {
		case true:
			Attack1Act();
			break;

		case false:
			Attack1Set();
			break;
		}
		break;
	case DST_ATTACK2:
		switch (attackFlag) {
		case true:
			Attack2Act();
			break;

		case false:
			Attack2Set();
			break;
		}
		break;
	}

	//攻撃
	if (dragonState == false) {
		if (ptime->GetTime() - attack_time > 6.0f) {
			state = DST_ATTACK1;
		}
	}
	else {
		if (witchAttack == true) {
			if (ptime->GetTime() - attack_time > 6.0f) {
				state = DST_ATTACK1;
				witchAttack = false;
			}
		}
		else {
			if (ptime->GetTime() - attack_time > 5.0f) {
				state = DST_ATTACK2;
				witchAttack = true;
			}
		}
	}

	//アニメーション
	for (int e = 0; e < 11; e++) {
		if (d_box[e].exist == true) {
			firstBox = (unsigned short)e;
			break;
		}
	}
	Anm();
	//当たり判定(player)
	PlayerHit();
	//当たり判定(bullet)
	for (int e = 0; e < bulletNum; e++) {
		if (pplayer->GetBulletUse(e) == true) {	//bulletが使われていたら当たり判定を行う
			BulletHit();
		}
	}

	//とげの管理
	SpineUpdate();

	//hpの管理 hp=すべてのboxのhpの合計
	/*hp = 0;
	for (int e = 0; e < 11; e++) {
		if (d_box[e].exist == true) {
			hp += d_box[e].hp;
		}
	}*/

	time = ptime->GetTime();
}

void Dragon::Draw(VECTOR2 camera) {
	addRot = rot;
	for (int e = 0; e <11; e++) {
		addRot += d_box[e].rot;	//一個前のボックスのposを加算
		if (d_box[e].exist == true) {
			this->camera = d_box[e].pos;
			this->camera = this->camera-camera;
			pdraw->DragonDraw(this->camera, d_box[e].size, e, addRot, d_box[e].g_v);
		}
	}
	pdraw->DragonHpDraw(hp,DRAGON_HP);
	for (int e = 0; e < 9; e++) {
		if (spine[e].GetExist() == true) {
			spine[e].Draw(camera);
		}
	}
}

void Dragon::Anm() {	//アニメーション
	//それぞれのBOXにposを入れる
	addRot = rot;	//ドラゴン自体の回転
	radius += sinf(ptime->GetTime())/3;
	if (state == DST_NORMAL || (state == DST_ATTACK1 && (attackState == DST1 || attackState == DST2))||state==DST_ATTACK2) {
		d_box[firstBox].pos.x = cosf(rot * PI) * radius + CENTER_X;	//先頭ボックスのposを作成
		d_box[firstBox].pos.y = sinf(rot * PI) * radius + CENTER_Y;
	}
	if (state != DST_ATTACK2) {
		for (int e = firstBox + 1; e < 11; e++) {
			d_box[e].rot = sinf(ptime->GetTime() + 2 / e) / e / WAVE_DIV;	//逓減するsin波で波打つアニメーションを作る
		}
	}
	for (int e = firstBox+1; e < 11; e++) {
		//前のボックスのrotを加算
		addRot += d_box[e - 1].rot;	//一個前のボックスのposを加算
		if (d_box[e].rot > 0) {		//rotが0以上の時一個前のboxの右下の頂点を求め、現在のボックスのposを作成する
			VECTOR2 beforeLowerRightVertex;
			beforeLowerRightVertex.x = cosf((addRot * PI) + atan2f((float)d_box[e - 1].size.u, (float)-d_box[e - 1].size.v))
				* (float)hypot((int)d_box[e - 1].size.u / 2, (int)d_box[e - 1].size.v / 2) + d_box[e - 1].pos.x;
			beforeLowerRightVertex.y = sinf((addRot * PI) + atan2f((float)d_box[e - 1].size.u, (float)-d_box[e - 1].size.v))
				* (float)hypot((int)d_box[e - 1].size.u / 2, (int)d_box[e - 1].size.v / 2) + d_box[e - 1].pos.y;
			//int a = 0;
			d_box[e].pos.x = cosf((addRot + d_box[e].rot) * PI + atan2f((float)d_box[e].size.u, (float)d_box[e].size.v))
				* (float)hypot((int)d_box[e].size.u / 2, (int)d_box[e].size.v / 2) + beforeLowerRightVertex.x;
			d_box[e].pos.y = sinf((addRot + d_box[e].rot) * PI + atan2f((float)d_box[e].size.u, (float)d_box[e].size.v))
				* (float)hypot((int)d_box[e].size.u / 2, (int)d_box[e].size.v / 2) + beforeLowerRightVertex.y;
		}
		else if (d_box[e].rot < 0) {	//rotが0以下の時、一個前のboxの右上の頂点を求める
			VECTOR2 beforeLowerLeftVertex;
			beforeLowerLeftVertex.x = cosf((addRot * PI) + atan2f((float)d_box[e - 1].size.u, (float)d_box[e - 1].size.v))
				* (float)hypot((int)d_box[e - 1].size.u / 2, (int)d_box[e - 1].size.v / 2) + d_box[e - 1].pos.x;
			beforeLowerLeftVertex.y = sinf((addRot * PI) + atan2f((float)d_box[e - 1].size.u, (float)d_box[e - 1].size.v))
				* (float)hypot((int)d_box[e - 1].size.u / 2, (int)d_box[e - 1].size.v / 2) + d_box[e - 1].pos.y;
			//int a = 0;
			d_box[e].pos.x = cosf((addRot + d_box[e].rot) * PI + atan2f((float)d_box[e].size.u, (float)-d_box[e].size.v))
				* (float)hypot((int)d_box[e].size.u / 2, (int)d_box[e].size.v / 2) + beforeLowerLeftVertex.x;
			d_box[e].pos.y = sinf((addRot + d_box[e].rot) * PI + atan2f((float)d_box[e].size.u, (float)-d_box[e].size.v))
				* (float)hypot((int)d_box[e].size.u / 2, (int)d_box[e].size.v / 2) + beforeLowerLeftVertex.y;
		}
	}
}

void Dragon::PlayerHit() {	//当たり判定を行う　playerの頂点をboxの角度に移動して行う
	addRot = rot;
	for (int e = 0; e < 11; e++) {
		addRot += d_box[e].rot;
		p_vertex[3] = pplayer->GetPos();
		//playerの各頂点の座標を取得
		p_vertex[0] = { p_vertex[3].x - 10 / 2,p_vertex[3].y - G_SIZE / 2 };
		p_vertex[1] = { p_vertex[3].x + 10 / 2,p_vertex[3].y - G_SIZE / 2 };
		p_vertex[2] = { p_vertex[3].x + 10 / 2,p_vertex[3].y + G_SIZE / 2 };
		p_vertex[3] = { p_vertex[0].x ,p_vertex[2].y };
		//判定したいboxの各座標を取得
		hitPos[0] = { d_box[e].pos.x - (float)d_box[e].size.u / 2,d_box[e].pos.y - (float)d_box[e].size.v / 2 };
		hitPos[1] = { d_box[e].pos.x + (float)d_box[e].size.u / 2,d_box[e].pos.y - (float)d_box[e].size.v / 2 };
		hitPos[2] = { d_box[e].pos.x + (float)d_box[e].size.u / 2,d_box[e].pos.y + (float)d_box[e].size.v / 2 };
		hitPos[3] = { d_box[e].pos.x - (float)d_box[e].size.u / 2,d_box[e].pos.y + (float)d_box[e].size.v / 2 };


		for (int f = 0; f < 4; f++) {
			p_vertex[f] = MakeVirtualPos(d_box[e].pos, p_vertex[f], addRot);
			
			//外積での当たり判定
			d_vertex[0] = HitDetection(hitPos[0], hitPos[1], p_vertex[f]);
			d_vertex[1] = HitDetection(hitPos[1], hitPos[2], p_vertex[f]);
			d_vertex[2] = HitDetection(hitPos[2], hitPos[3], p_vertex[f]);
			d_vertex[3] = HitDetection(hitPos[3], hitPos[0], p_vertex[f]);
			//外積で求めたflagを用いて当たり判定を行う
			if (d_vertex[0] == true && d_vertex[1] == true && d_vertex[2] == true&&d_vertex[3]==true) {
				pplayer->Hit(atk);
				playerHit = true;
				break;
			}
			DetectReset();
		}
		//一度playerと当たっている判定をしたらplayerとの当たり判定を終了する
		if (playerHit == true) {
			break;
		}
	}
}

void Dragon::BulletHit() {		//bulletとの当たり判定
	addRot = rot;
	for (int e = 0; e < 11; e++) {
		if (d_box[e].exist == true) {
			addRot += d_box[e].rot;
			for (int f = 0; f < bulletNum; f++) {
				VECTOR2 bullet_pos = pplayer->GetBulletPos(f);
				bullet_pos = MakeVirtualPos(d_box[e].pos, bullet_pos, addRot);

				hitPos[0] = { d_box[e].pos.x - (float)d_box[e].size.u / 2,d_box[e].pos.y - (float)d_box[e].size.v / 2 };
				hitPos[1] = { d_box[e].pos.x + (float)d_box[e].size.u / 2,d_box[e].pos.y - (float)d_box[e].size.v / 2 };
				hitPos[2] = { d_box[e].pos.x + (float)d_box[e].size.u / 2,d_box[e].pos.y + (float)d_box[e].size.v / 2 };
				hitPos[3] = { d_box[e].pos.x - (float)d_box[e].size.u / 2,d_box[e].pos.y + (float)d_box[e].size.v / 2 };

				d_vertex[0] = HitDetection(hitPos[0], hitPos[1], bullet_pos);
				d_vertex[1] = HitDetection(hitPos[1], hitPos[2], bullet_pos);
				d_vertex[2] = HitDetection(hitPos[2], hitPos[3], bullet_pos);
				d_vertex[3] = HitDetection(hitPos[3], hitPos[0], bullet_pos);
				//外積で求めたflagを用いて当たり判定を行う
				if (d_vertex[0] == true && d_vertex[1] == true && d_vertex[2] == true && d_vertex[3] == true) {
					pplayer->SetBulletUse(f);

					if (state == DST_NORMAL) {
						d_box[e].hp -= Damage(pplayer->GetBulletPower(f), pstatus);
						if (d_box[e].hp <= 1.5 && (d_box[e].g_v == 0||d_box[e].g_v==1)) {
							d_box[e].g_v += 2;
						}
					}
					if (d_box[e].hp <= 0) {
						d_box[e].exist = false;
						pticket->SetTicket();
					}
					hp -= Damage(pplayer->GetBulletPower(f), pstatus);
					if (hp < DRAGON_HP / 2 && state2Init == false) {	//hpが半分を切ったら怒り状態になる
						state2Init = true;
						dragonState = true;
						State2Init();
					}
					
				}
				DetectReset();
			}
		}
	}
}

void Dragon:: DetectReset() {
	for (int e = 0; e < 4; e++) {
		d_vertex[e] = false;
	}
}

void Dragon::SetSpeed(float speed) {
	this->speed = speed;
}

void Dragon::Attack1Set() {	//空高く上がってplayerめがけて突撃する攻撃
	state = DST_ATTACK1;
	attackState = DST1;
	attack_time = ptime->GetTime();
	for (int e = 0; e < 11; e++) {
		if (d_box[e].exist == true) {
			attack1FirstBox = (unsigned short)e;
			break;
		}
	}
	radiusGoal = RADIUS + D_Y_MAX;
	moveMs = (radiusGoal - radius) / ATTACK1_TIME;
	rotMs = (0.5 - d_box[attack1FirstBox].rot) / (float)ATTACK1_TIME;
	attackFlag = true;
	attackTradition = false;
	for (int e = 0; e < 11; e++) {
		d_box[e].g_v = 4;
	}
}

void Dragon::Attack1TrdSet() {
	attackTradition = true;
	timeMs = attack_time + ATTACK1_TIME/2.5f;
	norm = VacNormalize(d_box[attack1FirstBox].pos, ppos);
	timeGoal = ptime->GetTime() + ATTACK1_TIME;
}

void Dragon::Attack2TrdSet() {
	attackTradition = true;
	moveMs = (radius - RADIUS) / ATTACK1_TIME;
}

void Dragon::Attack1Act() {
	switch (attackState) {
	case DST1:
		
		radius += moveMs * (ptime->GetTime() - attack_time);
		
		d_box[attack1FirstBox].rot += rotMs * (ptime->GetTime() - attack_time);
		attack_time = ptime->GetTime();
		if (radius>RADIUS+ D_Y_MAX) {
			radius = radiusGoal;
			d_box[attack1FirstBox].rot = 0.5f;
			attackState = DST2;
		}
		break;
	case DST2:
		switch (attackTradition) {
		case true:
			float remainder;
			d_box[attack1FirstBox].rot -= rotMs * (ptime->GetTime() - attack_time)*2.5f;
			attack_time = ptime->GetTime();
			if (ptime->GetTime() >timeMs) {
				attackState = DST3;
			}
			break;
		case false:
			Attack1TrdSet();
			
			break;
		}
		break;
	case DST3:	//playerの場所までの距離から正規化して近づく
		switch (attackTradition) {
		case true:

			d_box[attack1FirstBox].pos = d_box[attack1FirstBox].pos+norm* (ptime->GetTime() - attack_time)*500;
			d_box[attack1FirstBox].rot = atan2f(d_box[attack1FirstBox].pos.y - ppos.y, d_box[attack1FirstBox].pos.x - ppos.y);
			attack_time = ptime->GetTime();

			if (timeGoal<attack_time) {	//playerとの距離が一定以下になったら攻撃から抜ける処理へ移動
				Attack1Uninit();
			}
			break;
		case false:
			Attack2TrdSet();
			break;
		}
		break;
	}
}

void Dragon::Attack1Uninit() {
	d_box[0].rot = 0.0f;
	state = DST_NORMAL;
	rot = 1.6f;
	radius = DRFON_RADIUS;
	for (int e = 0; e < 11; e++) {
		if (dragonState == false) {
			d_box[e].g_v = 0;
			d_box[e].hp = 3;
		}
		else {
			d_box[e].g_v = 1;
			d_box[e].hp = 3;
		}
	}
	attack_time = ptime->GetTime();
	attackState = DST1;
	attackFlag = false;
}

void Dragon::Attack2Set() {	//回転しながらとげを飛ばす攻撃
	state = DST_ATTACK2;
	attackState = DST1;
	attack_time = ptime->GetTime();
	for (int e = 0; e < 11; e++) {
		if (d_box[e].exist == true) {
			attack1FirstBox = (unsigned short)e;
			break;
		}
	}
	radiusGoal = RADIUS + D_Y_MAX;
	moveMs = (radiusGoal - radius) / ATTACK1_TIME;
	rotMs = ATTACK2_ROT / ATTACK1_TIME;
	attackFlag = true;
	attackTradition = false;
	for (int e = 0; e < 11; e++) {
		d_box[e].g_v = 5;
	}
}

void Dragon::Attack2Act() {
	switch (attackState) {
	case DST1:	//3秒で384まで上昇し、rotを0.5にする
		radius += moveMs * (ptime->GetTime() - attack_time);

		for (int e = attack1FirstBox + 1; e < 11; e++) {
			d_box[e].rot += rotMs * (ptime->GetTime() - attack_time);
		}

		attack_time = ptime->GetTime();
		if (radius > RADIUS + D_Y_MAX) {
			radius = radiusGoal;
			for (int e = attack1FirstBox + 1; e < 11; e++) {
				d_box[e].rot = ATTACK2_ROT;
			}
			attackState = DST2;
		}
		break;
	case DST2:
		d_box[attack1FirstBox].rot -= rotMs * (ptime->GetTime() - attack_time)*3;
		for (int e=attack1FirstBox + 1; e < 11; e++) {
			d_box[e].rot -= rotMs * (ptime->GetTime() - attack_time)*0.8f;
		}
		attack_time = ptime->GetTime();
		if (d_box[attack1FirstBox+1].rot < 0.0f) {
			for (int e = attack1FirstBox+1; e < 10; e++) {
				if (d_box[e].exist == true) {
					spine[e - 1].Init(d_box[e].pos, ptime->GetTime());
				}
			}
			Attack2Uninit();
		}
		break;
	}
}

void Dragon::Attack2Uninit() {
	state = DST_NORMAL;
	attackState = DST1;
	d_box[attack1FirstBox].rot = 0.0f;
	attackFlag = false;
	rot = 1.6f;
	radius = DRFON_RADIUS;
	attack_time = ptime->GetTime();
	for (int e = 0; e < 11; e++) {
		if (dragonState == false) {
			d_box[e].g_v = 0;
			d_box[e].hp = 3;
		}
		else {
			d_box[e].g_v = 1;
			d_box[e].hp = 3;
		}
	}
}

void Dragon::SpineUpdate() {
	for (int e = 0; e < 9; e++) {
		if (spine[e].GetExist() == true) {
			spine[e].Update(ptime->GetTime(),pplayer);
		}
	}
}

VECTOR2 Dragon::CameraPos() {
	if (cameraFlag == false) {
		if (state != DST_NORMAL ||(state==DST_NORMAL&& rot > 1.65f)) {
			cameraSave = d_box[0].pos;
			cameraFlag = true;
		}
	}
	else {
		if (state == DST_NORMAL && rot < 1.65f) {
			cameraFlag = false;
		}
	}

	if (cameraFlag == true) {
		for (int e = 0; e < 11; e++) {
			if (d_box[e].exist == true) {
				return d_box[e].pos - cameraSave;
			}
		}
	}
	else {
		VECTOR2 notUse = { 0.0f,0.0f };
		return notUse;
	}
}

float Dragon::GetHp() {
	return hp;
}

unsigned short int Dragon::GetForm() {
	return form;
}
