#include "Bullet.h"
#include <time.h>

#define GROUND	(250)
#define GUIDE_JUMP	(Y_MAX - 32)
#define GUIDE_NOT_JUMP	(Y_MAX/2-32)

BULLET::BULLET() {
	pos = { 0.0f,0.0f };
	camera = { 0.0f,0.0f };	//cameraのpos
	ppos = { 440,0 };		//playerのpos
	pSize = { 20,G_SIZE };	//playerのboxのサイズ
	time = 0.0f;			//移動などに使う時間変数
	gravity = GRAVITY_NOR;	//弾の落ち方にかかわる変数
	use = false;			//使っているか
	useColision = false;	//playerとの当たり判定をつけるかどうか
	hit = false;			//playerに当たったらtrue
	rotate = 1.5f;			//回転
	jstrength = 0.0f;		//重力の実数値
	haight = 0.0f;			//地面からの高さ
	stHaight = 0.0f;		//撃ち出し時の地面からの高さ
	power = 0;
	pdraw = 0;
	ground = 0;
	guideFlag = false;
	pdraw = 0;
	//pplayer = 0;
}

void BULLET::PointerInit(DRAW* pdraw) {
	this->pdraw = pdraw;
}

void BULLET::Update(float now) {	//銃弾のアップデート
	/****************************************************************************
	回転処理
	****************************************************************************/
	rotate += (now - time)/4;

	/****************************************************************************
	簡易的な数値積分
	****************************************************************************/
	int repeat = (int)((now - time) / 0.01);
	for (int e = 0; e < repeat;e++) {
		haight -= jstrength;
		jstrength += (gravity*2/5);		//重力の合計
		if (guideFlag == true) {
			pos.x +=10;
		}
	}
	time = now;
	if (haight < 0) {		//地面についたら使わなくなる
		use = false;
	}


	/****************************************************************************
	座標の更新
	****************************************************************************/
	if (guideFlag == false) {
		pos.x = cosf(rotate * PI) * (1028 + haight) + 440;
		pos.y = sinf(rotate * PI) * (1028 + haight) + 1278;
	}
	else {
		pos.y = ground - haight;
	}
	/****************************************************************************
	ENEMYから呼び出された場合PLAYERとの当たり判定を行う
	****************************************************************************/
	if (useColision == true) {	//use_colisionがtrueならplayerとの当たり判定を行う
		PlayerHit();
	}
	//Draw();
}

void BULLET::Init(VECTOR2 pos,float gravity,int power) {
 	power /= 10;
	time = (float)clock() / 1000;
	use = true;
	rotate = 1.5f;
	this->pos = pos;
	jstrength = 0.0f;
	stHaight = pos.y;
	this->gravity = gravity;
	this->power = power;
	if (pos.x != PLAYER_POS_X) {
		if (pos.y > Y_MAX / 2) {
			ground = GUIDE_JUMP;
		}
		else if(pos.y<Y_MAX/2) {
			ground = GUIDE_NOT_JUMP;
		}
		guideFlag = true;
	}
	else {
		ground = GROUND;
	}
	haight = ground - pos.y;
}

void BULLET::Init(VECTOR2 pos, float gravity, float rotate) {	//enemyから使う時に
	time = (float)clock() / 1000;
	use = true;
	this->rotate = rotate;
	this->pos = pos;
	jstrength = 0.0f;
	haight = 16;	//ここを変える
	stHaight = 16;
	this->gravity = gravity;
	this->rotate = rotate;
	useColision = true;
	hit = false;
	ground = GROUND;
}

void BULLET::PlayerHit() {		//playerとの当たり判定
	if (PlayerHitDetection(ppos, pos, pSize) == true) {
		hit = true;
		use = false;
	}
}

bool BULLET::GetUse() {			//使っているかのゲッター
	return use;
}

void BULLET::Draw(float camera) {	//描画(float)
	this->camera = pos;
	this->camera.y += camera;
	pdraw->BulletDraw(rotate,this->camera);
}

void BULLET::Draw(VECTOR2 camera) {	//描画(VECTOR)
	this->camera = pos;
	this->camera = this->camera-camera;
	pdraw->BulletDraw(rotate, this->camera);
}

VECTOR2 BULLET::GetPos() {	//座標のゲッター
	return pos;
}

void BULLET::SetUse() {		//敵に当たってuseがfalseになる
	use = false;
}

void BULLET::SetPpos(float ppos) {	//player_pos_yのセッター
	this->ppos.y = ppos;
}

bool BULLET::GetHit() {		//ヒットしたかのゲッター
	return hit;
}

int BULLET::GetPower() {	//攻撃力のゲッター
	return power;
}

float BULLET::GetRot() {	//回転のゲッター
	return rotate;
}
