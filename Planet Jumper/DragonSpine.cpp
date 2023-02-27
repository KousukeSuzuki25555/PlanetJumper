#include "DragonSpine.h"

SPINE::SPINE() {								//棘のコンストラクタ
	pos = { 0.0f,0.0f };		
	camera = { 0.0f,0.0f };		//カメラのpos
	size = { 18,10 };			//描画サイズ
	rot = 0.0f;					//棘の回転
	time = 0.0f;				//移動量の計算などに用いる時間
	atk = 0.1f;					//攻撃力
	vertex = { 0.0f,0.0f };		//棘の頂点	
	p_size = { 20,G_SIZE };		//playerのボックスサイズ
	exist = false;				//存在しているか
	/*d_vertex[0] = false;
	d_vertex[1] = false;
	d_vertex[2] = false;
	d_vertex[3] = false;*/
}

void SPINE::PointerInit(DRAW* pdraw) {
	this->pdraw = pdraw;
}

void SPINE::Update(float now,PLAYER* pplayer) {	//棘のアップデート
	target = pplayer->GetPos();
	rot = atan2f(pos.y - target.y, pos.x - target.x);
	VECTOR2 a = VacNormalize(pos, target) * (now - time)*500;
	pos = pos + VacNormalize(pos, target) * (now - time)*500;
	time = now;
	PlayerHit(pplayer,now);
}

void SPINE::Reset() {							//棘をリセットする関数 
	exist = false;
	//DetectReset();
}

void SPINE::Init(VECTOR2 pos,float now) {		//棘を使うときの初期化
	this->pos = pos;
	exist = true;
	time = now;
}

void SPINE::Draw(VECTOR2 camera) {				//棘の描画
	this->camera = pos;
	this->camera = this->camera - camera;
	pdraw->DragonSpineDraw(this->camera, rot);
}

void SPINE::PlayerHit(PLAYER* pplayer,float now) {	//playerとの当たり判定
	//棘の頂点座標を入れる
	vertex = { cosf((1+rot) * PI) * size.u / 2+pos.x,sinf((1*rot) * PI) * size.u / 2+pos.y };
	//当たり判定
	if (PlayerHitDetection(pplayer->GetPos(),vertex,p_size)==true) {
		pplayer->BossstHit(atk,now);

		exist = false;
	}
}

bool SPINE::GetExist() {					//存在しているかのゲッター
	return exist;
}

//void SPINE::DetectReset() {						
//	for (int e = 0; e < 3; e++) {
//		d_vertex[e] = false;
//	}
//}
