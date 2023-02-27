#include "Block.h"
#include <cmath>

BLOCK::BLOCK() {
	//time = { (float)clock() / 1000,0  };
	rotate = 0.0f;
	rotate_gap = 0.0f;					//speedの変化を記憶
	size = {0,0};						//ここを変更することで当たり判定のサイズを変更できる
	pos = { 0.0f,0.0f };
	radius = size.v / 2 + RADIUS;
	d_vertex[0] = false;
	d_vertex[1] = false;
	d_vertex[2] = false;
	d_vertex[3] = false;
	n_vertex[0] = { 0,0 };
	n_vertex[1] = { 0,0 };
	n_vertex[2] = { 0,0 };
	n_vertex[3] = { 0,0 };
	p_size = { 20,G_SIZE };
	speed = SPEED_NOR;
	ppos = { 0.0f,0.0f };
	uv = { 256,64 };
	pdraw = 0;
}

void BLOCK::PointerInit(DRAW* pdraw,PLAYER* pplayer) {
	this->pdraw = pdraw;
	this->pplayer = pplayer;
}

void BLOCK::Update(float rot) {
	rotate = rotate_gap+rot;
	pos.x = cosf(rotate * PI) * (radius) + 440;
	pos.y = sinf(rotate * PI) * (radius) + 1278;
	//障害物の各頂点の座標を求める
	n_vertex[0] = { cosf((1.25f + rotate) * PI) * ((float)hypot(size.u / 2,size.v / 2)) + pos.x,sinf((1.25 + rotate) * PI) * ((float)hypot(size.u / 2,size.v / 2)) + pos.y };
	n_vertex[1] = { cosf((1.75f + rotate) * PI) * ((float)hypot(size.u / 2,size.v / 2)) + pos.x,sinf((1.75 + rotate) * PI) * ((float)hypot(size.u / 2,size.v / 2)) + pos.y };
	n_vertex[2] = { cosf((0.25f + rotate) * PI) * ((float)hypot(size.u / 2,size.v / 2)) + pos.x,sinf((0.25 + rotate) * PI) * ((float)hypot(size.u / 2,size.v / 2)) + pos.y };
	n_vertex[3] = { cosf((0.75f + rotate) * PI) * ((float)hypot(size.u / 2,size.v / 2)) + pos.x,sinf((0.75 + rotate) * PI) * ((float)hypot(size.u / 2,size.v / 2)) + pos.y };
	//playerの各頂点の座標を求める
	p_vertex[3] = pplayer->GetPos();
	p_vertex[0] = { p_vertex[3].x - PLAYER_SIZE_X / 2,p_vertex[3].y - PLAYER_SIZE_Y / 2 };
	p_vertex[1] = { p_vertex[3].x + PLAYER_SIZE_X / 2,p_vertex[3].y - PLAYER_SIZE_Y / 2 };
	p_vertex[2] = { p_vertex[3].x + PLAYER_SIZE_X / 2,p_vertex[3].y + PLAYER_SIZE_Y / 2 };
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
		d_vertex[0] = HitDetection(n_vertex[0], n_vertex[1], pplayer->GetBulletPos(e));
		d_vertex[1] = HitDetection(n_vertex[1], n_vertex[2], pplayer->GetBulletPos(e));
		d_vertex[2] = HitDetection(n_vertex[2], n_vertex[3], pplayer->GetBulletPos(e));
		d_vertex[3] = HitDetection(n_vertex[3], n_vertex[0], pplayer->GetBulletPos(e));
		if (d_vertex[0] == true && d_vertex[1] == true && d_vertex[2] == true && d_vertex[3] == true) {
			pplayer->SetBulletUse(e);
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
	rotate_gap = rotate;
	this->size = size;
	uv.u = u;
	uv.v = v;
	radius = size.v / 2 + 1020;
	this->bulletNum = bulletNum;
}

void BLOCK::SetSpeed(float speed) {
	this->speed = speed;
}
