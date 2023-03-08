#include "Draw.h"

void DRAW::PoliceDraw(I_VECTOR2 uv,VECTOR2 pos) {
	g_police(uv.u * G_SIZE, uv.v * G_SIZE, G_SIZE, G_SIZE).resized(G_SIZE).drawAt(pos.x, pos.y);
}

void DRAW::BackDraw() {
	g_back(0, 0, 16, 9).scaled(80).draw(0, 0);
}

void DRAW::TitleBackDraw(float rot) {
	g_titleBack(0, 0, 766, 766).scaled(4.0f).rotated(rot).drawAt(CENTER_X, CENTER_Y);
}

void DRAW::BossBackDraw() {
	g_bossback(0, 0, 16, 9).scaled(80).draw(0, 0);
}

void DRAW::CircleDraw(VECTOR2 pos) {
	g_circle(0, 0, RADIUS*2+8, RADIUS * 2 +8).drawAt(pos.x , pos.y);
}

void DRAW::PlayerDraw(I_VECTOR2 uv, VECTOR2 pos) {
	g_player(uv.u * G_SIZE, uv.v * G_SIZE, G_SIZE, G_SIZE).resized(G_SIZE).drawAt(pos.x, pos.y);
}

void DRAW::WindowDraw(bool anm,float rot) {		//window内の描画
	//1.2~1.4	rot-1.2  3=256 256*(rot-1.2)/0.3
	int anm_uv = 0;
	if (anm == false) {
		anm_uv = 1;
	}
	g_window(0, 0, 750, 360).draw(0, Y_MAX - 360);
	meter(0, 0, 256, 8).draw(G_SIZE, Y_MAX - 48);
	g_player((3 + anm_uv) * G_SIZE, 2* G_SIZE, G_SIZE, G_SIZE).drawAt(288, Y_MAX - 64);
	g_police((0 + anm_uv) * G_SIZE, 1* G_SIZE, G_SIZE, G_SIZE).drawAt(32+ (256 * (rot - 1.3) / 0.2), Y_MAX - 64);
}

void DRAW::WindowDraw() {
	g_window(0, 0, 750, 360).draw( 0, Y_MAX - 360, ColorF{1.0f,1.0f,1.0f,0.5f});
}

void DRAW::BlockDraw(float rotate,VECTOR2 pos, I_VECTOR2 uv, I_VECTOR2 size) {
	g_block(uv.u, uv.v, size.u, size.v).rotated((rotate + 0.5) * PI).drawAt(pos.x, pos.y);
}

void DRAW::IconDraw(I_VECTOR2 uv, VECTOR2 pos) {
	g_icon(uv.u * 64, uv.v * 64, 64, 64).drawAt(pos.x, pos.y);
}

void DRAW::BulletDraw(float rotate,VECTOR2 pos) {
	g_bullet(0, 1, 8, 7).rotated((rotate + 0.5) * PI).drawAt(pos.x, pos.y);
}

void DRAW::Enemy1Draw(float rotate,VECTOR2 pos) {
	g_enemy1(0, 0, G_SIZE, G_SIZE).rotated((rotate + 0.5) * PI).drawAt(pos.x, pos.y);
}

void DRAW::Enemy2Draw(float rotate, VECTOR2 pos, int u) {
	g_enemy2(u*32, 0, 32, 32).rotated((rotate + 0.5) * PI).drawAt(pos.x, pos.y);
}

void DRAW::Enemy3Draw(float rotate, VECTOR2 pos, I_VECTOR2 uv) {
	g_enemy3(uv.u * 64.0f, uv.v * 64.0f, 64, 64).rotated((rotate + 0.5) * PI).drawAt(pos.x, pos.y);
}

void DRAW::TutorialBackDraw(float x,float y) {
	Tutorial_back(0,0,X_MAX,38).draw(x, y);
}

void DRAW::TutorialHighlight() {
	tutorialhighlight(0, 0, 64, 64).resized(192).draw(566-32, 540-32);
}

void DRAW::HartDraw(float num) {
	int a=0;
	int b = (int)num + 1;
	for (int e = 0; e < b; e++) {
		if (num >= 1) {
			g_hart(0, 0, G_SIZE, G_SIZE).draw(32+a*32, Y_MAX-200);
		}
		else {
			g_hart(0, 0, G_SIZE * num, G_SIZE).draw(32+a*32, Y_MAX-200);
		}
		num--;
		a++;
	}
}

void DRAW::HartdrawBoss(float num) {
	int a = 0;
	int b = (int)num + 1;
	for (int e = 0; e < b; e++) {
		if (num >= 1) {
			g_hart(0, 0, G_SIZE, G_SIZE).draw(32 + a * 32, Y_MAX - 62);
		}
		else {
			g_hart(0, 0, G_SIZE * num, G_SIZE).draw(32 + a * 32, Y_MAX - 62);
		}
		num--;
		a++;
	}
}

void DRAW::CloudDraw(I_VECTOR2 uv, VECTOR2 pos, float rot, int size) {
	g_cloud(uv.u, uv.v, size, size).rotated((rot+0.5) * PI).drawAt(pos.x, pos.y);
}

void DRAW::MapDraw(I_VECTOR2 flamepos) {
	g_map(0, 0, 320, 180).scaled(4.0).draw(0, 0);
	//枠の描画
	g_map(320, 0, 16, 16).scaled(4).draw(flamepos.u, flamepos.v);
}

void DRAW::StageSt(float x) {
	TutorialBackDraw(x, Y_MAX / 2 - 64);
}

void DRAW::DragonDraw(VECTOR2 pos,I_VECTOR2 uv, int num, float rot,int v) {
	if (num == 0)
	{
		g_dragon(0, v*D_GRA_SIZE, uv.u, D_GRA_SIZE-1).rotated((rot + 0.5) * PI).drawAt(pos.x, pos.y);
	}
	else {
		g_dragon(D_GRA_SIZE +(num-1)* D_GRA_SIZE/2, v * D_GRA_SIZE, uv.u, D_GRA_SIZE-1).rotated((rot+0.5f) * PI).drawAt(pos.x, pos.y);
	}
}

void DRAW::DragonHpDraw(float hp,int hpMax) {
	float hpGuage = (10.0f / (float)hpMax) * hp;
	g_bossHp(0, 0, hpGuage, 0.5).scaled(64).draw(X_MAX / 2 - 5 * 64, 0);
}

void DRAW::DragonSpineDraw(VECTOR2 pos, float rot) {
	g_bossSpine(0, 0, 18, 10).rotated((rot + 0.5f) * PI).drawAt(pos.x, pos.y);
}

void DRAW::GuideDraw(bool jump) {
	if (jump == true) {
		g_guideBack(0, 0, 7, 6).scaled(60).draw(X_MAX - 840, Y_MAX - 360);
	}
	else {
		g_guideBack(0, 0, 7, 6).scaled(60).draw(X_MAX - 840, 0);
	}
}

void DRAW::TicketDraw(VECTOR2 pos,bool shop) {
	if (shop == true) {
		g_ticket(61, 41, 200, 90).draw(pos.x, pos.y);
	}
	else {
		g_ticket(0, 0, 320, 160).drawAt(pos.x, pos.y);
	}
}

void DRAW::TicketSmallDraw(bool boss) {
	if (boss == false) {
		g_ticketGame(0, 0, 100, 45).draw(550, Y_MAX - 328);
	}
	else {
		g_ticketGame(0, 0, 100, 45).draw(250, Y_MAX-64);
	}
}

void DRAW::BulletDisp(int num) {
	for (int e = 0; e < num; e++) {
		g_bulletDisp(0, 0, 20, 32).draw(32+32*e, Y_MAX - 150);
	}
}

void DRAW::UfoDraw(int num, VECTOR2 pos) {
	g_Ufo(num * 64, 0, 64, 64).drawAt(pos.x, pos.y);
}

void DRAW::LaserDraw(int num, VECTOR2 pos) {
	g_Laser(num * 32, 0, 32, 32).drawAt(pos.x, pos.y);
}
