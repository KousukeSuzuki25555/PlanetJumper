#include "Weapon.h"

WEAPON::WEAPON() {
	weaponNum=0;	//何番の銃を使うか　NORMAL_GUN MACHINE_GUN CURSOR_GUN
	bulletNum=0;	//使用できる銃弾の数
}

void WEAPON::Init(int weaponNum, int bulletNum) {	//初期化関数
	this->weaponNum = weaponNum;
	this->bulletNum = bulletNum;
	if (weaponNum == CURSOR_GUN) {
		cursor.Init();
	}
}

void WEAPON::PointerInit(PLAYER* pplayer, DRAW* pdraw,MY_TIME* ptime) {
	for (int e = 0; e < BULLETS_MAX; e++) {
		bullet[e].PointerInit(pdraw, ptime);
	}
	this->ptime = ptime;
}

void WEAPON::Update(float posY) {
	if (machineBulletNum != 0) {	//マシンガン攻撃の途中ならマシンガンを撃つ
		MachineShot(posY);
	}

	if (bulletNum == CURSOR_GUN) {	//カーソル銃の時アップデートする
		VECTOR2 ppos = { CENTER_X,posY };
		cursor.Update(ppos);
	}

	for (int e = 0; e < BULLETS_MAX; e++) {
		if (bullet[e].GetExist() == true) {
			bullet[e].Update();
		}
	}
}

void WEAPON::Shot(VECTOR2 pos, int power,float gravity) {				//他クラスから撃つとき
	int useBullet = SearchNotUseBullet();	//使う銃弾の番号を取得

	if (useBullet != BULLETS_MAX) {
		switch (weaponNum) {
		case NORMAL_GUN:
			bullet[useBullet].Init(pos, gravity, power, 0.0f);
			break;

		case MACHINE_GUN:
			bullet[useBullet].Init(pos, gravity, power, 0.0f);
			NotUseBulletNum();
			machineBulletNum--;
			this->power = power;
			this->gravity = gravity;
			break;

		case CURSOR_GUN:

			break;
		}
	}
}

void WEAPON::MachineShot(float posY) {	//マシンガンの2つ目以降を撃つときに用いる
	int useBullet = SearchNotUseBullet();	//使う銃弾の番号を取得
	VECTOR2 pos = { CENTER_X,posY };
	bullet[useBullet].Init(pos, gravity, power, 0.0f);
	machineBulletNum--;
}

int WEAPON::SearchNotUseBullet() {	//使われていない銃弾を探す
	for (int e = 0; e < bulletNum; e++) {
		if (bullet[e].GetExist() == false) {
			return e;
		}
	}
	//もし全部使用されていたらありえない数字を返す
	return BULLETS_MAX;
}

int WEAPON::NotUseBulletNum() {		//使われていない銃弾の数を返す
	machineBulletNum = 0;
	for (int e = 0; e < bulletNum; e++) {
		if (bullet[e].GetExist() == true) {
			machineBulletNum++;
		}
	}
}
