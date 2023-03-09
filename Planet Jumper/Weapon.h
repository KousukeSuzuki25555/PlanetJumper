#pragma once
#include "Main.h"
#include "NewBullet.h"
#include "Draw.h"
#include "MyTime.h"
#include "Cursor.h"

class WEAPON {
	int weaponNum;	//何番の銃を使うか　NORMAL_GUN MACHINE_GUN CURSOR_GUN
	int bulletNum;	//使用できる銃弾の数
	int machineBulletNum;
	int power;		//MACHINE_GUNで用いる
	float gravity;	//MACHINE_GUNで用いる
	NEW_BULLET bullet[BULLETS_MAX];
	CURSOR cursor;
	MY_TIME* ptime;

public:
	WEAPON();
	void PointerInit(PLAYER* pplayer,DRAW* pdraw,MY_TIME* ptime);
	void Init(int weaponNum, int bulletNum);	//初期化関数
	void Update(float posY);
	void Shot(VECTOR2 pos, int power, float gravity);				//他クラスから撃つとき
	void MachineShot(float posY);	//マシンガンの2つ目以降を撃つときに用いる
	int SearchNotUseBullet();	//使われていない銃弾を探す
	int NotUseBulletNum();		//使われていない銃弾の数を返す
};
