#include "TestStage.h"

TEST_STAGE::TEST_STAGE() {
	now = time.GetTime();
	jump = NORMAL;
	gravity = NORMAL;
	pplayer = &player;
	speed = NORMAL;
	speed_value = SPEED_NOR;
	size[0] = { 128,128 };
	size[1] = { 128,64 };
	size[2] = { 64,64 };
	size[3] = { 32,32 };
	block[0].Init(speed, 1.7, size[3], 256, 64);
	block[1].Init(speed, 1.8, size[0], 0, 0);
	block[2].Init(speed, 1.9, size[1], 128, 0);
	block[3].Init(speed, 2.0, size[1], 128, 64);
	block[4].Init(speed, 2.1, size[2], 256, 0);
	rotate = 0.0f;
	for (int e = 0; e < 4; e++) {
		tiger[e].Init(0.2 + e * 0.5,now);
	}
}

void TEST_STAGE::Update() {
	time.Update();
	rotate -= (time.GetTime()-now) / speed_value;
	now = time.GetTime();
	draw.BackDraw(rotate);
	ground.Update();

	icon.Update();
	gravity = icon.GetGravity();
	if(icon.GetSpeed() != speed){
		speed = icon.GetSpeed();
		if (speed == STRONG) {
			speed_value = SPEED_FAST;
		}
		else if (speed == NORMAL) {
			speed_value = SPEED_NOR;
		}
		else {
			speed_value = SPEED_SLOW;
		}
		for (int e = 0; e < 5; e++) {
			block[e].SetSpeed(speed_value);
		}
	}
	player.SetGravity(gravity);
	jump = icon.GetJump();
	player.SetJumpLimit(jump);

	player.Update(now);
	/*for (int e = 0; e < 5; e++) {
		block[e].Update(rotate, pplayer);
	}*/
	
	police.Update(now,speed_value);

	if (crow.GetExist() == true) {
		crow.Update(now, pplayer);
	}
	for (int e = 0; e < 4; e++) {
		if (tiger[e].GetExsist() == true) {
			tiger[e].Update(now, pplayer);
		}
	}
	/*if (e_canon.GetHit() == false) {
		e_canon.Update(now, pplayer);
	}*/
	//draw.WindowDraw();
}
