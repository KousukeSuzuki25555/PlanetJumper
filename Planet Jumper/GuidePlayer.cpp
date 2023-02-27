#include "GuidePlayer.h"

GuidePlayer::GuidePlayer() {
	pos = { 0.0f,0.0f };
	//uv = {0,0}
	int ground;
	float time;
	float gravity;
	float jstrength;	//ジャンプの力	
	bool guideJump;		//ジャンプの説明中か
	bool attackFlag;
	bool hitFlag;
}
void Init();
void Update(float now);
void HitSet();
void HitAct();
void AttackSet();
void AttackAct();
void Draw();
