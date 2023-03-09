#include "Cursor.h"

#define PLAYER_DISTANCE	(10.0f)

CURSOR::CURSOR() {
	pos = { 0.0f,0.0f };
	rot = 0.0f;
	posArray[0] = {  PLAYER_SIZE_Y / 2 + PLAYER_DISTANCE,0.0f };
	posArray[1] = { cosf(0.175f * PI) * (PLAYER_SIZE_Y / 2 + PLAYER_DISTANCE),
		sinf(0.175f * PI) * (PLAYER_SIZE_Y / 2 + PLAYER_DISTANCE) };
	posArray[2] = { 0.0f,PLAYER_SIZE_Y / 2 + PLAYER_DISTANCE };
	changeRot = false;
}

void CURSOR::Init() {
	rot = 0.0f;
	changeRot = false;
}

void CURSOR::Update(VECTOR2 ppos) {
	KeyGet();

	if (rot == 0.0f) {
		pos = ppos + posArray[0];
	}
	else if (rot == -0.25f) {
		pos = ppos + posArray[1];
	}
	else {
		pos = ppos + posArray[2];
	}
}

void CURSOR::KeyGet() {	//キー取得
	if (KeyD.down()) {
		rot += 0.25f;
		if (rot > 0) {
			rot = 0;
		}
		changeRot = true;
	}
	else if (KeyA.down()) {
		rot -= 0.25f;
		if (rot < -0.5f) {
			rot = -0.5f;
		}
		changeRot = true;
	}
}
