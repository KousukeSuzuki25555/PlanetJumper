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
	anm_time = time;

	radius = size.v / 2 + 1020;

	rotate = 1.9f;
	hit_time = 0.0f;

	exist = true;

	hit = false;

	move_speed[0] = 20;	//値を小さくすると歩く速度が速くなる
	move_speed[1] = 15;
	move_pt = 0;

	bullet_pos = { 0.0f,0.0f };

	p_vertex[0] = { 0.0f,0.0f };
	p_vertex[1] = { 0.0f,0.0f };
	p_vertex[2] = { 0.0f,0.0f };
	p_vertex[3] = { 0.0f,0.0f };

	hp = 3;

	uv = { 0,1 };
}

void TIGER::GuideInit(float now,bool jump) {
	if (jump == true) {
		pos = { 800,JUMP_GROUND-10 };
	}
	else {
		pos = { 800,NOT_JUMP_GROUND-10 };
	}
	rotate = 1.5f;
	time = now;
	hp = 3;
	uv = { 0,1 };
}

void TIGER::PointerInit(DRAW* pdraw, PLAYER* pplayer) {
	this->pdraw = pdraw;
	this->pplayer = pplayer;
}

void TIGER::PointerInit(DRAW* pdraw, PLAYER* pplayer, Ticket* pticket) {
	this->pdraw = pdraw;
	this->pplayer = pplayer;
	this->pticket = pticket;
}

void TIGER::Update(float now) {
	rotate -= (now - time) / move_speed[move_pt];
	if (rotate < 1.65f) {
		uv.v = 0;
		move_pt = 1;
	}
	pos.x = cosf(rotate * PI) * (radius)+440;
	pos.y = sinf(rotate * PI) * (radius)+1278;
	//アニメーションの移行
	switch (uv.v) {
	case 0:
		if (now - anm_time > 0.1) {
			uv.u++;
			anm_time = now;
			if (uv.u == 10) {
				uv.u = 0;
			}
		}
		break;
	case 1:
		if (now-anm_time > 0.1) {
			uv.u++;
			anm_time = now;
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
		BulletHit(now);
	}
	
	if (hit == true) {
		if (hit_time - now < 0) {
			HitUninit();
		}
	}
	time = now;
}

void TIGER::GuideUpdate(float now) {
	VECTOR2 ppos = pplayer->GetPos();
	if (pos.x - ppos.x < 300.0f) {
		uv.v = 0;
	}

	switch (uv.v) {
	case 0:
		pos.x -= (now - time) * 100;
		if (now - anm_time > 0.1) {
			uv.u++;
			anm_time = now;
			if (uv.u == 10) {
				uv.u = 0;
			}
		}
		break;
	case 1:
		pos.x -= (now - time) * 50;
		if (now - anm_time > 0.1) {
			uv.u++;
			anm_time = now;
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
		BulletHit(now);
	}
	


	if (hit == true) {
		if (hit_time - now < 0) {
			HitUninit();
		}
	}
	time = now;
}

void TIGER::HitSet(float now) {
	hit = true;
	hit_time = now += 0.1f;
}

void TIGER::HitUninit() {
	hit = false;
}

bool TIGER::GetExist() {
	return exist;
}

void TIGER::PlayerHit() {		//playerとの当たり判定
	//playerの各頂点の座標を取得
	p_vertex[3] = pplayer->GetPos();
	p_vertex[0] = { p_vertex[3].x - 10 / 2,p_vertex[3].y - G_SIZE / 2 };
	p_vertex[1] = { p_vertex[3].x + 10 / 2,p_vertex[3].y - G_SIZE / 2 };
	p_vertex[2] = { p_vertex[3].x + 10 / 2,p_vertex[3].y + G_SIZE / 2 };
	p_vertex[3] = { p_vertex[0].x ,p_vertex[2].y };
	//同一平面に移動し、当たり判定を行う
	n_vertex[0] = { pos.x + point1.p1.x,pos.y + point1.p1.y };
	n_vertex[1] = { pos.x + point1.p2.x,pos.y + point1.p2.y };
	n_vertex[2] = { pos.x + point1.p3.x,pos.y + point1.p3.y };

	for (int e = 0; e < 4; e++) {
		p_vertex[e] = MakeVirtualPos(pos, p_vertex[e], rotate);
		//外積での当たり判定
		d_vertex[0] = HitDetection(n_vertex[0], n_vertex[1], p_vertex[e]);
		d_vertex[1] = HitDetection(n_vertex[1], n_vertex[2], p_vertex[e]);
		d_vertex[2] = HitDetection(n_vertex[2], n_vertex[0], p_vertex[e]);
		//外積で求めたflagを用いて当たり判定を行う
		if (d_vertex[0] == true && d_vertex[1] == true && d_vertex[2] == true) {
			pplayer->Hit();
			//exist = false;
			break;
		}
		DetectReset();
	}
}
void TIGER::BulletHit(float now) {		//銃弾との当たり判定
	for (int e = 0; e < bulletNum; e++) {
		if (pplayer->GetBulletUse(e) == true) {
			bullet_pos = pplayer->GetBulletPos(e);
			bullet_pos = MakeVirtualPos(pos, bullet_pos, rotate);

			d_vertex[0] = HitDetection(n_vertex[0], n_vertex[1], bullet_pos);
			d_vertex[1] = HitDetection(n_vertex[1], n_vertex[2], bullet_pos);
			d_vertex[2] = HitDetection(n_vertex[2], n_vertex[0], bullet_pos);
			//外積で求めたflagを用いて当たり判定を行う
			if (d_vertex[0] == true && d_vertex[1] == true && d_vertex[2] == true) {
				pplayer->SetBulletUse(e);
				hp -= pplayer->GetBulletPower(e);
				if (hp <= 0) {
					exist = false;
					pticket->SetTicket();
				}
				else {
					HitSet(now);
				}
			}
			DetectReset();

		}
	}
}

void TIGER::Init(float rotate,float now,int bulletNum) {
	this->rotate = rotate;
	exist = true;
	uv = { 0,1 };
	move_pt = 0;
	hp = 3;
	time = now;
	anm_time = now;
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
