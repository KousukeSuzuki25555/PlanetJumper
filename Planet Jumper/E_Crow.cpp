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

void CROW::PointerInit(DRAW* pdraw, PLAYER* pplayer, Ticket* pticket,MY_TIME* ptime, WEAPON* pweapon) {
	this->pdraw = pdraw;
	this->pplayer = pplayer;
	this->pticket = pticket;
	this->ptime = ptime;
	this->pweapon = pweapon;
}

void CROW::Update() {
	rotate -= (ptime->GetTime() - time) / 25.0f;
	//radius += cosf(now);
	pos.x = cosf(rotate * PI) * (radius)+440;
	pos.y = sinf(rotate * PI) * (radius)+1278;
	//アニメーション
	if (time - anmTime > 0.1) {
		uv.u++;
		anmTime = time;
		if (uv.u == 4) {
			uv.u = 0;
		}
	}
	//障害物の各頂点の座標を求める
	nVertex[0] = { cosf((1.25 + rotate) * PI) * ((float)hypot(size.u / 2,size.v / 2)) + pos.x,sinf((1.25 + rotate) * PI) * ((float)hypot(size.u / 2,size.v / 2)) + pos.y };
	nVertex[1] = { cosf((1.75 + rotate) * PI) * ((float)hypot(size.u / 2,size.v / 2)) + pos.x,sinf((1.75 + rotate) * PI) * ((float)hypot(size.u / 2,size.v / 2)) + pos.y };
	nVertex[2] = { cosf((0.25 + rotate) * PI) * ((float)hypot(size.u / 2,size.v / 2)) + pos.x,sinf((0.25 + rotate) * PI) * ((float)hypot(size.u / 2,size.v / 2)) + pos.y };
	nVertex[3] = { cosf((0.75 + rotate) * PI) * ((float)hypot(size.u / 2,size.v / 2)) + pos.x,sinf((0.75 + rotate) * PI) * ((float)hypot(size.u / 2,size.v / 2)) + pos.y };
	//playerの各頂点の座標を求める
	pVertex[3] = pplayer->GetPos();
	pVertex[0] = { pVertex[3].x - 10 / 2,pVertex[3].y - G_SIZE / 2 };
	pVertex[1] = { pVertex[3].x + 10 / 2,pVertex[3].y - G_SIZE / 2 };
	pVertex[2] = { pVertex[3].x + 10 / 2,pVertex[3].y + G_SIZE / 2 };
	pVertex[3] = { pVertex[0].x ,pVertex[2].y };
	//全ての辺とプレイヤーとの外積を求める
	for (int e = 0; e < 4; e++) {
		d_vertex[0] = HitDetection(nVertex[0], nVertex[1], pVertex[e]);
		d_vertex[1] = HitDetection(nVertex[1], nVertex[2], pVertex[e]);
		d_vertex[2] = HitDetection(nVertex[2], nVertex[3], pVertex[e]);
		d_vertex[3] = HitDetection(nVertex[3], nVertex[0], pVertex[e]);
		if (d_vertex[0] == true && d_vertex[1] == true && d_vertex[2] == true && d_vertex[3] == true) {
			pplayer->Hit();
			break;
		}
		DetectReset();
	}
	//弾との当たり判定

	for (int e = 0; e < bulletNum; e++) {
		if (pweapon->GetBulletUse(e) == true) {
			VECTOR2 bullet_pos = pweapon->GetBulletPos(e);
			bullet_pos = MakeVirtualPos(pos, bullet_pos, rotate);
			d_vertex[0] = HitDetection(nVertex[0], nVertex[1], pweapon->GetBulletPos(e));
			d_vertex[1] = HitDetection(nVertex[1], nVertex[2], pweapon->GetBulletPos(e));
			d_vertex[2] = HitDetection(nVertex[2], nVertex[3], pweapon->GetBulletPos(e));
			d_vertex[3] = HitDetection(nVertex[3], nVertex[0], pweapon->GetBulletPos(e));
			if (d_vertex[0] == true && d_vertex[1] == true && d_vertex[2] == true && d_vertex[3] == true) {
				pweapon->SetBulletUnuse(e);
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
