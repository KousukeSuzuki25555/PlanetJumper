#include "E_Ufo.h"

UFO::UFO() {	//コンストラクタ
	pos = { 0.0f,0.0f };	//座標
	pplayer = 0;	//playerのポインタ
	pticket = 0;	//チケットのポインタ
	ptime = 0;
	pstatus = 0;
	drawNum = 0;
	camera = { 0.0f,0.0f };			//cameraのpos
	for (int e = 0; e < 4; e++) {
		n_vertex[e] = { 0.0f,0.0f };		//blockの頂点
		p_vertex[e] = { 0.0f,0.0f };	//playerの中心からの座標
		d_vertex[e] = false;			//各頂点の外積が内側にあるか判定
	}
	bulletPos = { 0.0f,0.0f };		//銃弾の座標
	bulletNum = 0;			//銃弾の使用できる最大数
	//hp = 0.0f;					//hp
	time = 0.0f;				//移動などに使う時間関数
	moveTime = 0.0f;			//移動するタイミング
	attackTime = 0.0f;		//攻撃するタイミング
	exist = false;				//存在するか
	hit = false;				//攻撃を食らったか
	speed = 0.0f;
}

void UFO::Init(int bulletNum) {	//初期化関数
	pos = { X_MAX - G_SIZE / 2,10.0 + G_SIZE / 2 };
	//hp = 1.0f;
	time = ptime->GetTime();
	exist = true;
	hit = false;
	bulletNum = pstatus->GetBulletsNum();
	MakeMoveTime();
	MakeAttackTime();
	speed = SPEED_NOR;
}

void UFO::PointerInit(PLAYER* pplayer, Ticket* pticket, MY_TIME* ptime,GAME_STATUS* pstatus,DRAW* pdraw) {	//ポインターの初期化
	this->pplayer = pplayer;	//playerのポインタ
	this->pticket = pticket;	//チケットのポインタ
	this->ptime = ptime;
	this->pstatus = pstatus;
	this->pdraw = pdraw;
	laser.PointerInit(pplayer, pdraw, ptime);
}

void UFO::Update() {	//アップデート関数
	Move();
	Attack();
	if (laser.GetExist() == true) {
		laser.Update();
	}
	//当たり判定
	PlayerHit();
	BulletHit();

	Anm();
	//時間をアップデート
	time = ptime->GetTime();
}

void UFO::Move() {	//移動関数
	if (moveTime < ptime->GetTime()) {
		pos.x = rand() % X_MAX;
		MakeMoveTime();
	}
}

void UFO::Attack() {	//攻撃関数
	if (attackTime < ptime->GetTime()) {
		pos = { PLAYER_POS_X,10.0f + G_SIZE / 2 };
		moveTime = ptime->GetTime() + 1.5f;
		//描画を攻撃描画に変更する
		drawNum = 2;
		MakeAttackTime();

		//ここにレーザーの初期化関数を入れる
		laser.Init(pos, speed);
	}
}

void UFO::Anm() {		//描画関数
	if (anmTime <ptime->GetTime()) {
		switch (drawNum) {
		case 0:
			drawNum = 1;
			break;

		case 1:
			drawNum = 0;
			break;

		case 2:
			drawNum = 0;
			break;
		}
		anmTime = ptime->GetTime()+0.3f;
	}
}

void UFO::MakeMoveTime() {	//移動する時間を作る
	moveTime = ptime->GetTime() + (rand() % 200)/100;	//2秒以内のランダムなタイミングで移動する
}

void UFO::MakeAttackTime() {	//攻撃する時間を作る
	attackTime = ptime->GetTime() + 5.0f;
}

void UFO::PlayerHit() {	//プレイヤー小野当たり判定
	//playerの各頂点の座標を取得
	p_vertex[3] = pplayer->GetPos();
	p_vertex[0] = { p_vertex[3].x - 10 / 2,p_vertex[3].y - G_SIZE / 2 };
	p_vertex[1] = { p_vertex[3].x + 10 / 2,p_vertex[3].y - G_SIZE / 2 };
	p_vertex[2] = { p_vertex[3].x + 10 / 2,p_vertex[3].y + G_SIZE / 2 };
	p_vertex[3] = { p_vertex[0].x ,p_vertex[2].y };

	//UFO自体の頂点座標
	n_vertex[0] = { pos.x - G_SIZE / 2,pos.y + G_SIZE / 2 };
	n_vertex[1] = { pos.x + G_SIZE / 2,pos.y + G_SIZE / 2 };
	n_vertex[2] = { pos.x + G_SIZE / 2,pos.y - G_SIZE / 2 };
	n_vertex[3] = { pos.x - G_SIZE / 2,pos.y - G_SIZE / 2 };

	for (int e = 0; e < 4; e++) {
		//外積での当たり判定
		d_vertex[0] = HitDetection(n_vertex[0], n_vertex[1], p_vertex[e]);
		d_vertex[1] = HitDetection(n_vertex[1], n_vertex[2], p_vertex[e]);
		d_vertex[2] = HitDetection(n_vertex[2], n_vertex[3], p_vertex[e]);
		d_vertex[3] = HitDetection(n_vertex[3], n_vertex[0], p_vertex[e]);

		//外積で求めたflagを用いて当たり判定を行う
		if (d_vertex[0] == true && d_vertex[1] == true && d_vertex[2] == true&&d_vertex[3]==true) {
			pplayer->Hit();
			//exist = false;
			break;
		}
		DetectReset();
	}
}

void UFO::BulletHit() {		//銃弾との当たり判定
	for (int e = 0; e < bulletNum; e++) {
		if (pplayer->GetBulletUse(e) == true) {
			bulletPos = pplayer->GetBulletPos(e);

			d_vertex[0] = HitDetection(n_vertex[0], n_vertex[1], bulletPos);
			d_vertex[1] = HitDetection(n_vertex[1], n_vertex[2], bulletPos);
			d_vertex[2] = HitDetection(n_vertex[2], n_vertex[0], bulletPos);
			//外積で求めたflagを用いて当たり判定を行う
			if (d_vertex[0] == true && d_vertex[1] == true && d_vertex[2] == true) {
				pplayer->SetBulletUse(e);
				exist = false;
				pticket->SetTicket();
			}
			DetectReset();
		}
	}
}

void UFO::Draw(float camera) {	//描画
	this->camera = pos;
	this->camera.y = this->camera.y+camera;

	//ここに描画を入れる
	pdraw->UfoDraw(drawNum, pos);
	if (laser.GetExist() == true) {
		laser.Draw(camera);
	}
}

bool UFO::GetExist() {		//existのゲッター
	if (exist == false && laser.GetExist() == false) {
		return false;
	}
	return true;
}

void UFO::DetectReset() {
	for (int e = 0; e < 4; e++) {
		d_vertex[e] = false;
	}
}

void UFO::SetSpeed(float speed) {		//speedのセッター
	this->speed = speed;
	laser.SetSpeed(speed);
}
