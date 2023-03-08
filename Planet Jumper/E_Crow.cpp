#include "E_Crow.h"
#include <time.h>

CROW::CROW() {
	exist = true;
	time = (float)clock() / 1000;
	size = { 32,16 };
	rotate = 1.7f;
	uv = { 0,0 };
	radius = 0;
}

void CROW::Init(float rot,int bulletNum) {
	rotate = rot;
	this->time = ptime->GetTime();
	this->bulletNum = bulletNum;

	radius = RADIUS + 75.0f;
	exist = true;
}

void CROW::PointerInit(DRAW* pdraw, PLAYER* pplayer, Ticket* pticket,MY_TIME* ptime) {
	this->pdraw = pdraw;
	this->pplayer = pplayer;
	this->pticket = pticket;
	this->ptime = ptime;
}

void CROW::Update() {
	rotate -= (ptime->GetTime() - time) / 25.0f;
	//radius += cosf(now);
	pos.x = cosf(rotate * PI) * (radius)+440;
	pos.y = sinf(rotate * PI) * (radius)+1278;
	//アニメーション
	if (time - anm_time > 0.1) {
		uv.u++;
		anm_time = time;
		if (uv.u == 4) {
			uv.u = 0;
		}
	}
	//障害物の各頂点の座標を求める
	n_vertex[0] = { cosf((1.25 + rotate) * PI) * ((float)hypot(size.u / 2,size.v / 2)) + pos.x,sinf((1.25 + rotate) * PI) * ((float)hypot(size.u / 2,size.v / 2)) + pos.y };
	n_vertex[1] = { cosf((1.75 + rotate) * PI) * ((float)hypot(size.u / 2,size.v / 2)) + pos.x,sinf((1.75 + rotate) * PI) * ((float)hypot(size.u / 2,size.v / 2)) + pos.y };
	n_vertex[2] = { cosf((0.25 + rotate) * PI) * ((float)hypot(size.u / 2,size.v / 2)) + pos.x,sinf((0.25 + rotate) * PI) * ((float)hypot(size.u / 2,size.v / 2)) + pos.y };
	n_vertex[3] = { cosf((0.75 + rotate) * PI) * ((float)hypot(size.u / 2,size.v / 2)) + pos.x,sinf((0.75 + rotate) * PI) * ((float)hypot(size.u / 2,size.v / 2)) + pos.y };
	//playerの各頂点の座標を求める
	p_vertex[3] = pplayer->GetPos();
	p_vertex[0] = { p_vertex[3].x - 10 / 2,p_vertex[3].y - G_SIZE / 2 };
	p_vertex[1] = { p_vertex[3].x + 10 / 2,p_vertex[3].y - G_SIZE / 2 };
	p_vertex[2] = { p_vertex[3].x + 10 / 2,p_vertex[3].y + G_SIZE / 2 };
	p_vertex[3] = { p_vertex[0].x ,p_vertex[2].y };
	//全ての辺とプレイヤーとの外積を求める
	for (int e = 0; e < 4; e++) {
		d_vertex[0] = HitDetection(n_vertex[0], n_vertex[1], p_vertex[e]);
		d_vertex[1] = HitDetection(n_vertex[1], n_vertex[2], p_vertex[e]);
		d_vertex[2] = HitDetection(n_vertex[2], n_vertex[3], p_vertex[e]);
		d_vertex[3] = HitDetection(n_vertex[3], n_vertex[0], p_vertex[e]);
		if (d_vertex[0] == true && d_vertex[1] == true && d_vertex[2] == true && d_vertex[3] == true) {
			pplayer->Hit();
			break;
		}
		DetectReset();
	}
	//弾との当たり判定

	for (int e = 0; e < bulletNum; e++) {
		if (pplayer->GetBulletUse(e) == true) {
			VECTOR2 bullet_pos = pplayer->GetBulletPos(e);
			bullet_pos = MakeVirtualPos(pos, bullet_pos, rotate);
			d_vertex[0] = HitDetection(n_vertex[0], n_vertex[1], pplayer->GetBulletPos(e));
			d_vertex[1] = HitDetection(n_vertex[1], n_vertex[2], pplayer->GetBulletPos(e));
			d_vertex[2] = HitDetection(n_vertex[2], n_vertex[3], pplayer->GetBulletPos(e));
			d_vertex[3] = HitDetection(n_vertex[3], n_vertex[0], pplayer->GetBulletPos(e));
			if (d_vertex[0] == true && d_vertex[1] == true && d_vertex[2] == true && d_vertex[3] == true) {
				pplayer->SetBulletUse(e);
				pticket->SetTicket();
				exist = false;
			}
			DetectReset();
		}
	}

	time = ptime->GetTime();
}

bool CROW::GetExist() {
	return exist;
}

void CROW::Draw(float camera) {
	this->camera = pos;
	this->camera.y += camera;
	
	pdraw->Enemy2Draw(rotate, this->camera, uv.u);
	
}
