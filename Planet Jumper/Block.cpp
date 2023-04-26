#include "Block.h"
#include <cmath>

BLOCK::BLOCK() {
	//time = { (float)clock() / 1000,0  };
	rotate = 0.0f;
	rotateGap = 0.0f;					//speedの変化を記憶
	size = {0,0};						//ここを変更することで当たり判定のサイズを変更できる
	pos = { 0.0f,0.0f };
	radius = size.v / 2 + RADIUS;
	d_vertex[0] = false;
	d_vertex[1] = false;
	d_vertex[2] = false;
	d_vertex[3] = false;
	nVertex[0] = { 0,0 };
	nVertex[1] = { 0,0 };
	nVertex[2] = { 0,0 };
	nVertex[3] = { 0,0 };
	pSize = { 20,G_SIZE };
	speed = SPEED_NOR;
	ppos = { 0.0f,0.0f };
	uv = { 256,64 };
	pdraw = 0;
}

void BLOCK::PointerInit(DRAW* pdraw,PLAYER* pplayer, WEAPON* pweapon) {
	this->pdraw = pdraw;
	this->pplayer = pplayer;
	this->pweapon = pweapon;
}

void BLOCK::Update(float rot) {
	rotate = rotateGap+rot;
	pos.x = cosf(rotate * PI) * (radius) + 440;
	pos.y = sinf(rotate * PI) * (radius) + 1278;
	//障害物の各頂点の座標を求める
	nVertex[0] = { cosf((1.25f + rotate) * PI) * ((float)hypot(size.u / 2,size.v / 2)) + pos.x,sinf((1.25 + rotate) * PI) * ((float)hypot(size.u / 2,size.v / 2)) + pos.y };
	nVertex[1] = { cosf((1.75f + rotate) * PI) * ((float)hypot(size.u / 2,size.v / 2)) + pos.x,sinf((1.75 + rotate) * PI) * ((float)hypot(size.u / 2,size.v / 2)) + pos.y };
	nVertex[2] = { cosf((0.25f + rotate) * PI) * ((float)hypot(size.u / 2,size.v / 2)) + pos.x,sinf((0.25 + rotate) * PI) * ((float)hypot(size.u / 2,size.v / 2)) + pos.y };
	nVertex[3] = { cosf((0.75f + rotate) * PI) * ((float)hypot(size.u / 2,size.v / 2)) + pos.x,sinf((0.75 + rotate) * PI) * ((float)hypot(size.u / 2,size.v / 2)) + pos.y };
	//playerの各頂点の座標を求める
	pVertex[3] = pplayer->GetPos();
	pVertex[0] = { pVertex[3].x - PLAYER_SIZE_X / 2,pVertex[3].y - PLAYER_SIZE_Y / 2 };
	pVertex[1] = { pVertex[3].x + PLAYER_SIZE_X / 2,pVertex[3].y - PLAYER_SIZE_Y / 2 };
	pVertex[2] = { pVertex[3].x + PLAYER_SIZE_X / 2,pVertex[3].y + PLAYER_SIZE_Y / 2 };
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
		d_vertex[0] = HitDetection(nVertex[0], nVertex[1], pweapon->GetBulletPos(e));
		d_vertex[1] = HitDetection(nVertex[1], nVertex[2], pweapon->GetBulletPos(e));
		d_vertex[2] = HitDetection(nVertex[2], nVertex[3], pweapon->GetBulletPos(e));
		d_vertex[3] = HitDetection(nVertex[3], nVertex[0], pweapon->GetBulletPos(e));
		if (d_vertex[0] == true && d_vertex[1] == true && d_vertex[2] == true && d_vertex[3] == true) {
			pweapon->SetBulletUnuse(e);
		}
		DetectReset();
	}
}

void BLOCK::Draw(float camera) {
	this->camera = pos;
	this->camera.y += camera;
	pdraw->BlockDraw(rotate, this->camera, uv, size);
}

bool BLOCK::Hit() {
	return false;
}

void BLOCK::DetectReset() {
	for (int e = 0; e < 4; e++) {
		d_vertex[e] = false;
	}
}

void BLOCK::Init(float speed, float rotate,I_VECTOR2 size,int u,int v,int bulletNum) {	//この関数でオブジェクトの中身を作ることができる
	this->speed = speed;
	rotateGap = rotate;
	this->size = size;
	uv.u = u;
	uv.v = v;
	radius = size.v / 2 + 1020;
	this->bulletNum = bulletNum;
}

void BLOCK::Init(float speed, float rotate, I_VECTOR2 size, int bulletNum) {	//初期化をより楽に　uv値を入れなくても使用できるようにする
	switch (size.u) {
	case 128:
		switch (size.v) {
		case 128:
			uv.u = 0;
			uv.v = 0;
			break;
		case 64:
			int randam = rand() % 2;
			switch (randam) {
			case 0:
				uv.u = 128;
				uv.v = 0;
				break;

			case 1:
				uv.u = 128;
				uv.v = 64;
				break;
			}
			break;
		}
		break;

	case 64:
		uv.u = 256;
		uv.v = 0;
		break;

	case 32:
		int randam = rand() % 4;
		switch (randam) {
		case 0:
			uv.u = 256;
			uv.v = 64;
			break;

		case 1:
			uv.u = 288;
			uv.v = 64;
			break;

		case 2:
			uv.u = 256;
			uv.v = 96;
			break;

		case 3:
			uv.u = 288;
			uv.v = 96;
			break;
		}
		break;
	}
	this->speed = speed;
	rotateGap = rotate;
	this->size = size;
	radius = size.v / 2 + 1020;
	this->bulletNum = bulletNum;
}

void BLOCK::SetSpeed(float speed) {
	this->speed = speed;
}
