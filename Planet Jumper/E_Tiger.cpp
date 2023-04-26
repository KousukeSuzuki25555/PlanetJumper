#include "E_Tiger.h"
#include <Math.h>
#include <stdlib.h>

#define JUMP_GROUND	(Y_MAX - 64)
#define NOT_JUMP_GROUND	(Y_MAX/2-64)

TIGER::TIGER() {
	size = { 64,64 };

	//頂点座標などのinput　当たり判定を三角形に変更したため[2]は必要ない
	point1.p1 = { -24,-4 };
	point1.p2 = { 18,4 };
	point1.p3 = { -16,32 };

	time = (float)clock() / 1000;
	anmTime = time;

	radius = size.v / 2 + 1020;

	rotate = 1.9f;
	hitTime = 0.0f;

	exist = true;

	hit = false;

	moveSpeed[0] = 20;	//値を小さくすると歩く速度が速くなる
	moveSpeed[1] = 15;
	movePt = 0;

	bullet_pos = { 0.0f,0.0f };

	pVertex[0] = { 0.0f,0.0f };
	pVertex[1] = { 0.0f,0.0f };
	pVertex[2] = { 0.0f,0.0f };
	pVertex[3] = { 0.0f,0.0f };

	hp = 3.0f;

	uv = { 0,1 };
}

void TIGER::GuideInit(bool jump) {
	if (jump == true) {
		pos = { 800,JUMP_GROUND-10 };
	}
	else {
		pos = { 800,NOT_JUMP_GROUND-10 };
	}
	rotate = 1.5f;
	time = ptime->GetTime();
	hp = 3.0f;
	uv = { 0,1 };
}

void TIGER::PointerInit(DRAW* pdraw, PLAYER* pplayer,MY_TIME* ptime, WEAPON* pweapon) {
	this->pdraw = pdraw;
	this->pplayer = pplayer;
	this->ptime = ptime;
	this->pweapon = pweapon;
}

void TIGER::PointerInit(DRAW* pdraw, PLAYER* pplayer, Ticket* pticket,MY_TIME* ptime, WEAPON* pweapon) {
	this->pdraw = pdraw;
	this->pplayer = pplayer;
	this->pticket = pticket;
	this->ptime = ptime;
	this->pweapon = pweapon;
}

void TIGER::Update() {
	rotate -= (ptime->GetTime() - time) / moveSpeed[movePt];
	if (rotate < 1.65f) {
		uv.v = 0;
		movePt = 1;
	}
	pos.x = cosf(rotate * PI) * (radius)+440;
	pos.y = sinf(rotate * PI) * (radius)+1278;
	//アニメーションの移行
	switch (uv.v) {
	case 0:
		if (ptime->GetTime()  - anmTime > 0.1) {
			uv.u++;
			anmTime = ptime->GetTime();
			if (uv.u == 10) {
				uv.u = 0;
			}
		}
		break;
	case 1:
		if (ptime->GetTime() -anmTime > 0.1) {
			uv.u++;
			anmTime = ptime->GetTime();
			if (uv.u == 5) {
				uv.u = 0;
			}
		}
		break;
	}
	/********************************************************************
	当たり判定
	********************************************************************/
	if (exist == true) {
		PlayerHit();
		BulletHit();
	}
	
	if (hit == true) {
		if (hitTime - ptime->GetTime() < 0) {
			HitUninit();
		}
	}
	time = ptime->GetTime();
}

void TIGER::GuideUpdate() {
	VECTOR2 ppos = pplayer->GetPos();
	if (pos.x - ppos.x < 300.0f) {
		uv.v = 0;
	}

	switch (uv.v) {
	case 0:
		pos.x -= (ptime->GetTime() - time) * 100;
		if (ptime->GetTime() - anmTime > 0.1) {
			uv.u++;
			anmTime = ptime->GetTime();
			if (uv.u == 10) {
				uv.u = 0;
			}
		}
		break;
	case 1:
		pos.x -= (ptime->GetTime() - time) * 50;
		if (ptime->GetTime() - anmTime > 0.1) {
			uv.u++;
			anmTime = ptime->GetTime();
			if (uv.u == 5) {
				uv.u = 0;
			}
		}
		break;
	}

	/********************************************************************
	当たり判定
	********************************************************************/
	if (exist == true) {
		PlayerHit();
		BulletHit();
	}
	


	if (hit == true) {
		if (hitTime - ptime->GetTime() < 0) {
			HitUninit();
		}
	}
	time = ptime->GetTime();
}

void TIGER::HitSet() {
	hit = true;
	hitTime = ptime->GetTime() + 0.1f;
}

void TIGER::HitUninit() {
	hit = false;
}

bool TIGER::GetExist() {
	return exist;
}

void TIGER::PlayerHit() {		//playerとの当たり判定
	//playerの各頂点の座標を取得
	pVertex[3] = pplayer->GetPos();
	pVertex[0] = { pVertex[3].x - 10 / 2,pVertex[3].y - G_SIZE / 2 };
	pVertex[1] = { pVertex[3].x + 10 / 2,pVertex[3].y - G_SIZE / 2 };
	pVertex[2] = { pVertex[3].x + 10 / 2,pVertex[3].y + G_SIZE / 2 };
	pVertex[3] = { pVertex[0].x ,pVertex[2].y };
	//同一平面に移動し、当たり判定を行う
	nVertex[0] = { pos.x + point1.p1.x,pos.y + point1.p1.y };
	nVertex[1] = { pos.x + point1.p2.x,pos.y + point1.p2.y };
	nVertex[2] = { pos.x + point1.p3.x,pos.y + point1.p3.y };

	for (int e = 0; e < 4; e++) {
		pVertex[e] = MakeVirtualPos(pos, pVertex[e], rotate);
		//外積での当たり判定
		d_vertex[0] = HitDetection(nVertex[0], nVertex[1], pVertex[e]);
		d_vertex[1] = HitDetection(nVertex[1], nVertex[2], pVertex[e]);
		d_vertex[2] = HitDetection(nVertex[2], nVertex[0], pVertex[e]);
		//外積で求めたflagを用いて当たり判定を行う
		if (d_vertex[0] == true && d_vertex[1] == true && d_vertex[2] == true) {
			pplayer->Hit();
			//exist = false;
			break;
		}
		DetectReset();
	}
}
void TIGER::BulletHit() {		//銃弾との当たり判定
	for (int e = 0; e < bulletNum; e++) {
		if (pweapon->GetBulletUse(e) == true) {
			bullet_pos = pweapon->GetBulletPos(e);
			bullet_pos = MakeVirtualPos(pos, bullet_pos, rotate);

			d_vertex[0] = HitDetection(nVertex[0], nVertex[1], bullet_pos);
			d_vertex[1] = HitDetection(nVertex[1], nVertex[2], bullet_pos);
			d_vertex[2] = HitDetection(nVertex[2], nVertex[0], bullet_pos);
			//外積で求めたflagを用いて当たり判定を行う
			if (d_vertex[0] == true && d_vertex[1] == true && d_vertex[2] == true) {
				pweapon->SetBulletUnuse(e);
				hp -= pweapon->GetBulletPower(e);
				if (hp <= 0) {
					exist = false;
					pticket->SetTicket();
				}
				else {
					HitSet();
				}
			}
			DetectReset();

		}
	}
}

void TIGER::Init(float rotate,int bulletNum) {
	this->rotate = rotate;
	exist = true;
	uv = { 0,1 };
	movePt = 0;
	hp = 3;
	time = ptime->GetTime();
	anmTime = ptime->GetTime();
	this->bulletNum = bulletNum;
}

float TIGER:: GetRotate() {
	return rotate;
}

VECTOR2 TIGER::GetPos() {
	return pos;
}

I_VECTOR2 TIGER::GetUv() {
	return uv;
}

void TIGER::Draw(float camera) {
	this->camera = pos;
	this->camera.y += camera;
	if (hit == false) {
		pdraw->Enemy3Draw(rotate, this->camera, uv);
	}
}

void TIGER:: Draw() {
	if (hit == false) {
		pdraw->Enemy3Draw(rotate, pos,uv);
	}
}

void TIGER::TicketGet() {	//チケットを入手するかの関数
	int ticket = 0;
	ticket = rand() % 2;
	if (ticket == 0) {
		pticket->SetTicket();
	}
}
//bool TIGER::DDraw() {	//falseなら描画
//	return hit;
//}
