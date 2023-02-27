#pragma once
#include "E_Police.h"
#include "Draw.h"
#include "Ground.h"
#include "Player.h"
#include "Block.h"
#include "Icon.h"
#include "MyTime.h"
#include "E_Canon.h"
#include "E_Crow.h"
#include "E_Tiger.h"

class TEST_STAGE {
public:
	POLICE police;
	DRAW draw;
	GROUND ground;
	PLAYER player;
	PLAYER* pplayer;
	BLOCK block[5];
	ICON icon;
	MY_TIME time;
	E_CANON e_canon;
	G_VECTOR2 size[4];
	CROW crow;
	TIGER tiger[4];
	float now;
	int speed;
	float speed_value;
	float rotate;
	unsigned short int gravity;
	unsigned short int jump;
public:
	TEST_STAGE();
	void Update();
};
