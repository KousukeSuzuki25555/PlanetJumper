#pragma once
#include "Main.h"
#include "Bullet.h"

class GuidePlayer {
	VECTOR2 pos;
	I_VECTOR2 uv;
	int ground;
	float time;
	float gravity;
	float jstrength;	//ジャンプの力	
	bool guideJump;		//ジャンプの説明中か
	bool attackFlag;
	bool hitFlag;

public:
	GuidePlayer();
	void Init();
	void Update(float now);
	void HitSet();
	void HitAct();
	void AttackSet();
	void AttackAct();
	void Draw();
};
