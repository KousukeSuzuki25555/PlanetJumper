#include "Laser.h"

#define LASER_SIZE_Y	(32)
#define LASER_SIZE_X	(8)
#define ATTACK_TIME	(3.0f)

LASER::LASER() {	//コンストラクタ
	pos = { 0.0f,0.0f };
	camera = { 0.0f,0.0f };
	pplayer = 0;
	ptime = 0;
	pdraw = 0;
	time = 0.0f;
	speed = 0.0f;
	rot = 0.0f;
	moveNormalize = { 0.0f,0.0f };
	exist = false;
	anm = false;
	for (int e = 0; e < 4; e++) {
		n_vertex[e] = { 0.0f,0.0f };
		p_vertex[e] = { 0.0f,0.0f };
		d_vertex[e] = false;
	}
	speedTime = 0.0f;
	initSpeed = 0.0f;
}

void LASER::PointerInit(PLAYER* pplayer,DRAW* pdraw, MY_TIME* ptime) {	//ポインタの初期化関数
	this->pplayer = pplayer;
	this->pdraw = pdraw;
	this->ptime = ptime;	
}

void LASER::Init(VECTOR2 pos,float speed) {	//初期化関数
	this->pos = pos;
	time = ptime->GetTime();
	this->speed = speed;
	initSpeed = speed;
	exist = true;
	speedTime = 0.0f;
	VECTOR2 start = { CENTER_X,CENTER_Y };	//円の中心　ここでのみ使うためここで生成
	moveNormalize = VacNormalize(start, pos);
	GetNormalize();
}

void LASER::Update() {	//アップデート関数
	SpeedChange();
	Move();
	PlayerHit();
	GroundHit();
	time = ptime->GetTime();
}

void LASER::PlayerHit() {	//プレイヤーとの当たり判定
	//playerの各頂点の座標を取得
	p_vertex[3] = pplayer->GetPos();
	p_vertex[0] = { p_vertex[3].x - 10 / 2,p_vertex[3].y - G_SIZE / 2 };
	p_vertex[1] = { p_vertex[3].x + 10 / 2,p_vertex[3].y - G_SIZE / 2 };
	p_vertex[2] = { p_vertex[3].x + 10 / 2,p_vertex[3].y + G_SIZE / 2 };
	p_vertex[3] = { p_vertex[0].x ,p_vertex[2].y };

	//UFO自体の頂点座標
	n_vertex[0] = { pos.x - LASER_SIZE_X / 2,pos.y - LASER_SIZE_Y / 2 };
	n_vertex[1] = { pos.x + LASER_SIZE_X / 2,pos.y - LASER_SIZE_Y / 2 };
	n_vertex[2] = { pos.x + LASER_SIZE_X / 2,pos.y + LASER_SIZE_Y / 2 };
	n_vertex[3] = { pos.x - LASER_SIZE_X / 2,pos.y + LASER_SIZE_Y / 2 };

	for (int e = 0; e < 4; e++) {
		//外積での当たり判定
		d_vertex[0] = HitDetection(p_vertex[0],p_vertex[1],n_vertex[e]);
		d_vertex[1] = HitDetection(p_vertex[1], p_vertex[2], n_vertex[e]);
		d_vertex[2] = HitDetection(p_vertex[2], p_vertex[3], n_vertex[e]);
		d_vertex[3] = HitDetection(p_vertex[3], p_vertex[0], n_vertex[e]);

		//外積で求めたflagを用いて当たり判定を行う
		if (d_vertex[0] == true && d_vertex[1] == true && d_vertex[2] == true && d_vertex[3] == true) {
			pplayer->Hit(0.2f);
			exist = false;
			break;
		}
		DetectReset();
	}
}

void LASER::GroundHit() {	//地面との当たり判定
	VECTOR2 groundPos = { CENTER_X,CENTER_Y };
	if (Diagonal(groundPos, pos) < LASER_SIZE_Y + RADIUS) {
		exist = false;
	}
}

void LASER::Move() {		//移動関数
	pos = pos - moveNormalize * 3;
}

void LASER::SpeedChange() {
	if (initSpeed != speed&&speedTime<ptime->GetTime()) {
		if (initSpeed == SPEED_SLOW) {
			if (speed == SPEED_NOR) {
				rot = 1.48f;
			}
			else {
				rot = 1.48f;
			}
		}
		else if(initSpeed == SPEED_NOR) {
			if (speed == SPEED_SLOW) {
				rot = 1.52f;
			}
			else {
				rot = 1.48f;
			}
		}
		else {
			if (speed == SPEED_SLOW) {
				rot = 1.52f;
			}
			else {
				rot = 1.52f;
			}
		}
		VECTOR2 start = { CENTER_X,CENTER_Y };
		//rot = 1.52f;
		pos.x = cosf(rot * PI) * Diagonal(start, pos) + CENTER_X;
		pos.y = sinf(rot * PI) * Diagonal(start, pos) + CENTER_Y;
		GetNormalize();
		speedTime = ptime->GetTime() + 0.01f;
	}
	else if (speedTime < ptime->GetTime()) {
		rot = 1.5f;
		GetNormalize();
		speedTime = ptime->GetTime() + 0.01f;
	}
}

void LASER::GetNormalize() {	//移動際の正規化された値を作る
	rot = atan2f(CENTER_Y - pos.y, CENTER_X - pos.x);
}

void LASER::Draw(float camera) {	//描画関数
	this->camera = pos;
	this->camera.y = this->camera.y + camera;
	//ここに描画
	if (anm == true)	pdraw->LaserDraw(0, pos);
	else				pdraw->LaserDraw(1, pos);
}

bool LASER::GetExist() {	//existのゲッター
	return exist;
}

void LASER::DetectReset() {
	for (int e = 0; e < 4; e++) {
		d_vertex[e] = false;
	}
}

void LASER::SetSpeed(float speed) {		//speedのセッター
	this->speed = speed;
}
