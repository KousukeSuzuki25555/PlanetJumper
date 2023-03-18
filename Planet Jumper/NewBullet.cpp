#include "NewBullet.h"
#include <Math.h>

#define MOVE_SPEED	(3.0f)

NEW_BULLET::NEW_BULLET() {
	pos = { 0.0f,0.0f };
	camera = { 0.0f,0.0f };
	pdraw = 0;
	//pplayer = 0;
	power = 0;
	time = 0.0f;
	rot = 0.0f;		//回転
	rotMs = 0.0f;	//毎秒の回転
	haight = 0.0f;	//地面からの高さ
	gravity = 0.0f;	//かかる重力
	gravityAdd = 0.0f;	//加算される重力
	exist = false;	//使用されているか
	//useColision = false;	//playerとの当たり判定を行うか
}

void NEW_BULLET::PointerInit(DRAW* pdraw, MY_TIME* ptime) {	//playerから呼び出すとき
	this->pdraw = pdraw;
	this->ptime = ptime;
	//useColision = false;
}

//void NEW_BULLET::PointerInit(DRAW* pdraw, PLAYER* pplayer, MY_TIME* ptime) {	//敵から呼ぶとき
//	this->pdraw = pdraw;
//	this->pplayer = pplayer;
//	this->ptime = ptime;
//	useColision = true;
//}

void NEW_BULLET::Init(VECTOR2 pos, float gravity, int power,float rot) {	//playerからの初期化関数
	this->pos = pos;
	this->gravity = gravity;
	this->power = power;
	//MakeRotMs(rot);	//発射角が渡されると毎秒どのくらい角度を更新するかを求める関数
	rotMs = 0.3f;
	this->rot = 1.5f;	//playerから呼ばれるときはrotが固定
	exist = true;
	haight = CENTER_Y - RADIUS - pos.y;
	gravityAdd = 0.0f;
	time = ptime->GetTime();
}

void NEW_BULLET::Init(VECTOR2 pos, float gravity) {	//enemyからの初期化
	this->pos = pos;
	this->gravity = gravity;
	VECTOR2 start = { CENTER_X,CENTER_Y };
	MakeRotMs();
	rot = atan2f(start.x - pos.x, start.y - pos.y);	//enemyから呼ばれる際は位置が毎回変わるため計算する
}

void NEW_BULLET::Update() {
	Move();	//移動
	LandHit();	//地面についたか
	time = ptime->GetTime();
}

void NEW_BULLET::Move() {	//移動の実働部
	rot -= rotMs * (time - ptime->GetTime());
	GravityAct();
	pos = { cosf(rot * PI) * (RADIUS + haight) + CENTER_X,sinf(rot * PI) * (RADIUS + haight) + CENTER_Y };
}

void NEW_BULLET::MakeRotMs() {	//発射角が渡されると毎秒どのくらい角度を更新するかを求める関数
	float ans = tan(1.0f);
	ans *= MOVE_SPEED;	//横への移動量を求める
	//一周が2πr r=RADIUS
	rotMs = ans / (2.0f * PI * RADIUS);
}

void NEW_BULLET::GravityAct() {		//重力の実働部
	//簡易的な積分で落ちるときの距離を求める
	int repeat = (ptime->GetTime()-time) / 0.005;
	for (int e = 0; e < repeat; e++) {
		gravityAdd += gravity;
		haight -= gravityAdd/10;
	}
}

//void NEW_BULLET::PlayerHit() {	//playerとの当たり判定
//	I_VECTOR2 size = { PLAYER_SIZE_X,PLAYER_SIZE_Y };
//	if (PlayerHitDetection(pplayer->GetPos(), pos, size)==true) {
//		pplayer->Hit(3);
//		exist = false;
//	}
//}

void NEW_BULLET::LandHit() {	//地面に接したかどうか
	VECTOR2 start = { CENTER_X,CENTER_Y };
	if (haight<0) {
		exist = false;
	}
}

VECTOR2 NEW_BULLET::GetPos() {	//ほかのclassから銃弾の座標を求めるときに使う
	return pos;
}

bool NEW_BULLET::GetExist() {	//existのゲッター
	return exist;
}

void NEW_BULLET::SetExist(bool state) {	//existが変化するとき
	exist = state;
}

int NEW_BULLET::GetPower() {	//powerのゲッター
	return power;
}

void NEW_BULLET::Draw(float camera) {	//描画(float)
	this->camera = pos;
	this->camera.y += camera;
	pdraw->BulletDraw(rot, this->camera);
}
