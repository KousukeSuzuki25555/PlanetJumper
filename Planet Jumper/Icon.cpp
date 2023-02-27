#include "Icon.h"

ICON::ICON() {
	weapon = NORMAL;
	speed = NORMAL;
	gravity = NORMAL;
	jump = NORMAL;

	weapon1.pos = { 630,540 };		//普通
	weapon2.pos = { 566,540 };		//強い
	speed1.pos = { 630,668 };		//普通
	speed2.pos = { 692,668 };		//早い
	gravity1.pos = { 692,604 };		//普通
	gravity2.pos = { 692,540 };		//強い
	jump1.pos = { 566,604 };		//2段
	jump2.pos = { 566,668 };		//3段
	frame.pos = { 0,0 };

	weapon1.uv = { 1,0 };
	weapon2.uv = { 0,0 };
	speed1.uv = { 1,2 };
	speed2.uv = { 2,2 };
	gravity1.uv = { 2,1 };
	gravity2.uv = { 2,0 };
	jump1.uv = { 0,1 };
	jump2.uv = { 0,2 };
	frame.uv = { 1,1 };

	weapon1.unuse_uv = { 4,0 };
	weapon2.unuse_uv = { 3,0 };
	speed1.unuse_uv = { 4,2 };
	speed2.unuse_uv = { 5,2 };
	gravity1.unuse_uv = { 5,1 };
	gravity2.unuse_uv = { 5,0 };
	jump1.unuse_uv = { 3,1 };
	jump2.unuse_uv = { 3,2 };
	frame.unuse_uv = { 4,1 };

	pdraw = 0;
}

void ICON::Init() {
	weapon = NORMAL;
	speed = NORMAL;
	gravity = NORMAL;
	jump = NORMAL;
}

void ICON::PointerInit(DRAW* pdraw) {
	this->pdraw = pdraw;
}

void ICON::GuideInit() {
	weapon1.pos = { X_MAX - 64 * 3+32,Y_MAX - 64 * 4  };		//普通
	weapon2.pos = { X_MAX - 64 * 4 + 32,Y_MAX - 64 * 4  };		//強い
	speed1.pos = { X_MAX - 64 * 3 + 32,Y_MAX - 64 * 2  };		//普通
	speed2.pos = { X_MAX - 64 * 2 + 32,Y_MAX - 64 * 2  };		//早い
	gravity1.pos = { X_MAX - 64 * 2 + 32,Y_MAX - 64 * 3  };		//普通
	gravity2.pos = { X_MAX - 64 * 2 + 32,Y_MAX - 64 * 4  };		//強い
	jump1.pos = { X_MAX - 64 * 4 + 32,Y_MAX - 64 * 3  };	//2段
	jump2.pos = { X_MAX - 64 * 4 + 32,Y_MAX - 64 * 2 };		//3段
	frame.unuse_uv = { 1,1 };
	frame.uv = { 4,1 };
}

void ICON::Update() {
	KeyGet();
}

unsigned short int ICON::GetGravity() {
	return gravity;
}

unsigned short int ICON::GetJump() {
	return jump;
}

unsigned short int ICON::GetSpeed() {
	return speed;
}

unsigned short int ICON::GetWeapon() {
	return weapon;
}

unsigned short int ICON::GetSpeedValue() {
	switch (speed) {
	case NORMAL:
		return (unsigned short int)SPEED_NOR;
		break;

	case STRONG:
		return (unsigned short int)SPEED_FAST;
		break;

	case WEAK:
		return (unsigned short int)SPEED_SLOW;
		break;
	}
}

void ICON::KeyGet() {
	/*-----------------------------------------------------
	入力受付
	-----------------------------------------------------*/
	if (KeyY.down()) {	//武器:強い
		weapon = STRONG;
		if (gravity == STRONG) {
			gravity = WEAK;
		}
		if (jump != WEAK) {
			jump = WEAK;
		}
	}
	if (KeyU.down()) {
		weapon = NORMAL;
		if (gravity == STRONG) {
			gravity = WEAK;
		}
		if (gravity == WEAK && speed != STRONG) {
			gravity = NORMAL;
		}
		if (jump == WEAK) {
			jump = NORMAL;
		}
	}
	if (KeyI.down()) {	//重力:弱い
		gravity = STRONG;
		if (speed == STRONG) {
			speed = WEAK;
		}
		if (weapon != WEAK) {
			weapon = WEAK;
		}
	}
	if (KeyK.down()) {
		gravity = NORMAL;
		if (speed == STRONG) {
			speed = WEAK;
		}
		if (weapon == WEAK) {
			weapon = NORMAL;
		}
		if (speed == WEAK && jump != STRONG) {
			speed = NORMAL;
		}
	}
	if (KeyN.down()) {
		jump = STRONG;
		if (weapon == STRONG) {
			weapon = WEAK;
		}
		if (speed != WEAK) {
			speed = WEAK;
		}
	}
	if (KeyH.down()) {
		jump = NORMAL;
		if (weapon == STRONG) {
			weapon = WEAK;
		}
		if (weapon == WEAK && gravity != STRONG) {
			weapon = NORMAL;
		}
		if (speed == WEAK) {
			speed = NORMAL;
		}
	}
	if (KeyComma.down()) {
		speed = STRONG;
		if (jump == STRONG) {
			jump = WEAK;
		}
		if (gravity != WEAK) {
			gravity = WEAK;
		}
	}
	if (KeyM.down()) {
		speed = NORMAL;
		if (jump == STRONG) {
			jump = WEAK;
		}
		if (jump == WEAK && weapon != STRONG) {
			jump = NORMAL;
		}
		if (gravity == WEAK) {
			gravity = NORMAL;
		}
	}
	//辺で何も選択されていないときの処理
	if (weapon == WEAK && gravity != STRONG) {
		weapon = NORMAL;
	}
	if (gravity == WEAK && speed != STRONG) {
		gravity = NORMAL;
	}
	if (speed == WEAK && jump != STRONG) {
		speed = NORMAL;
	}
	if (jump == WEAK && weapon != STRONG) {
		jump = NORMAL;
	}
}

void ICON:: Draw() {
	/*-----------------------------------------------------
	描画
	-----------------------------------------------------*/
	switch (weapon) {
	case STRONG:
		pdraw->IconDraw(weapon2.uv, weapon2.pos);
		pdraw->IconDraw(frame.uv, weapon2.pos);
		pdraw->IconDraw(weapon1.unuse_uv, weapon1.pos);
		pdraw->IconDraw(frame.unuse_uv, weapon1.pos);
		break;

	case NORMAL:
		pdraw->IconDraw(weapon2.unuse_uv, weapon2.pos);
		pdraw->IconDraw(frame.unuse_uv, weapon2.pos);
		pdraw->IconDraw(weapon1.uv, weapon1.pos);
		pdraw->IconDraw(frame.uv, weapon1.pos);
		break;

	case WEAK:
		pdraw->IconDraw(weapon2.unuse_uv, weapon2.pos);
		pdraw->IconDraw(frame.unuse_uv, weapon2.pos);
		pdraw->IconDraw(weapon1.unuse_uv, weapon1.pos);
		pdraw->IconDraw(frame.unuse_uv, weapon1.pos);
		break;
	}

	switch (speed) {
	case STRONG:
		pdraw->IconDraw(speed2.uv, speed2.pos);
		pdraw->IconDraw(frame.uv, speed2.pos);
		pdraw->IconDraw(speed1.unuse_uv, speed1.pos);
		pdraw->IconDraw(frame.unuse_uv, speed1.pos);
		break;

	case NORMAL:
		pdraw->IconDraw(speed2.unuse_uv, speed2.pos);
		pdraw->IconDraw(frame.unuse_uv, speed2.pos);
		pdraw->IconDraw(speed1.uv, speed1.pos);
		pdraw->IconDraw(frame.uv, speed1.pos);
		break;

	case WEAK:
		pdraw->IconDraw(speed2.unuse_uv, speed2.pos);
		pdraw->IconDraw(frame.unuse_uv, speed2.pos);
		pdraw->IconDraw(speed1.unuse_uv, speed1.pos);
		pdraw->IconDraw(frame.unuse_uv, speed1.pos);
		break;
	}

	switch (gravity) {
	case STRONG:	//重力が弱い状態なので注意
		pdraw->IconDraw(gravity2.uv, gravity2.pos);
		pdraw->IconDraw(frame.uv, gravity2.pos);
		pdraw->IconDraw(gravity1.unuse_uv, gravity1.pos);
		pdraw->IconDraw(frame.unuse_uv, gravity1.pos);
		break;

	case NORMAL:
		pdraw->IconDraw(gravity2.unuse_uv, gravity2.pos);
		pdraw->IconDraw(frame.unuse_uv, gravity2.pos);
		pdraw->IconDraw(gravity1.uv, gravity1.pos);
		pdraw->IconDraw(frame.uv, gravity1.pos);
		break;

	case WEAK:
		pdraw->IconDraw(gravity2.unuse_uv, gravity2.pos);
		pdraw->IconDraw(frame.unuse_uv, gravity2.pos);
		pdraw->IconDraw(gravity1.unuse_uv, gravity1.pos);
		pdraw->IconDraw(frame.unuse_uv, gravity1.pos);
		break;
	}

	switch (jump) {
	case STRONG:
		pdraw->IconDraw(jump2.uv, jump2.pos);
		pdraw->IconDraw(frame.uv, jump2.pos);
		pdraw->IconDraw(jump1.unuse_uv, jump1.pos);
		pdraw->IconDraw(frame.unuse_uv, jump1.pos);
		break;

	case NORMAL:
		pdraw->IconDraw(jump2.unuse_uv, jump2.pos);
		pdraw->IconDraw(frame.unuse_uv, jump2.pos);
		pdraw->IconDraw(jump1.uv, jump1.pos);
		pdraw->IconDraw(frame.uv, jump1.pos);
		break;

	case WEAK:
		pdraw->IconDraw(jump2.unuse_uv, jump2.pos);
		pdraw->IconDraw(frame.unuse_uv, jump2.pos);
		pdraw->IconDraw(jump1.unuse_uv, jump1.pos);
		pdraw->IconDraw(frame.unuse_uv, jump1.pos);
		break;
	}
}
