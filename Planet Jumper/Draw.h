#pragma once
#include "Main.h"

class DRAW {
protected:
	const Texture g_police{ Resource(U"rom/EdogSeat.png") };
	const Texture g_back{ Resource(U"rom/TentativeBack.png") };
	const Texture g_circle{ Resource(U"rom/Circle1.png" )};
	const Texture g_player{ Resource(U"rom/PlayerSeat.png") };
	const Texture g_window{ Resource(U"rom/Window.png" )};
	const Texture g_block{ Resource(U"rom/BillSeat.png" )};
	const Texture g_bullet{ Resource(U"rom/Bulllet8.png")};
	const Texture g_icon{ Resource(U"rom/Icon.png" )};
	const Texture g_enemy1{ Resource(U"rom/Enemy1Seat.png" )};
	const Texture g_enemy2{ Resource(U"rom/Enemy2Seat.png" )};
	const Texture g_enemy3{ Resource(U"rom/TigerSeat.png" )};
	const Texture meter{ Resource(U"rom/256_8.png" )};
	const Texture Tutorial_back{ Resource(U"rom/TutorialText.png" )};
	const Texture tutorialhighlight{ Resource(U"rom/64_64.png" )};
	const Texture g_hart{ Resource(U"rom/hart1.png" )};
	const Texture g_cloud{ Resource(U"rom/cloud.png" )};
	const Texture g_map{ Resource(U"rom/Map.png" )};
	const Texture g_dragon{ Resource(U"rom/Dragon.png") };
	const Texture g_bossback{ Resource(U"rom/BossBack.png") };
	const Texture g_bossHp{ Resource(U"rom/DragonHp.png" )};
	const Texture g_bossSpine{ Resource(U"rom/DragonBUllet10_18.png" )};
	const Texture g_titleBack{ Resource(U"rom/titleBack.png" )};
	const Texture g_guideBack{ Resource(U"rom/Guide.png" )};
	const Texture g_ticket{ Resource(U"rom/ticket32_16.png") };
	const Texture g_ticketGame{ Resource(U"rom/ticketSmall.png") };
	const Texture g_bulletDisp{ Resource(U"rom/bullet20_32.png" )};

public:
	void PoliceDraw(I_VECTOR2 uv,VECTOR2 pos);
	void BackDraw();
	void TitleBackDraw(float rot);
	void CircleDraw(VECTOR2 pos);
	void PlayerDraw(I_VECTOR2 uv, VECTOR2 pos);
	void WindowDraw(bool anm,float rot);
	void WindowDraw();
	void BossBackDraw();
	void BlockDraw(float rotate,VECTOR2 pos, I_VECTOR2 uv,I_VECTOR2 size);
	void IconDraw(I_VECTOR2 uv, VECTOR2 pos);
	void BulletDraw(float rotate,VECTOR2 pos);
	void Enemy1Draw(float rotate,VECTOR2 pos);
	void Enemy2Draw(float rotate, VECTOR2 pos, int u);
	void Enemy3Draw(float rotate, VECTOR2 pos, I_VECTOR2 uv);
	void TutorialBackDraw(float x,float y);
	void TutorialHighlight();
	void HartDraw(float num);
	void HartdrawBoss(float num);
	void CloudDraw(I_VECTOR2 uv, VECTOR2 pos, float rot, int size);
	void MapDraw(I_VECTOR2 flamepos);
	void StageSt(float x);
	void DragonDraw(VECTOR2 pos,I_VECTOR2 uv, int num, float rot,int v);
	void DragonHpDraw(float hp,int hpMax);
	void DragonSpineDraw(VECTOR2 pos, float rot);
	void GuideDraw(bool jump);
	void TicketDraw(VECTOR2 pos,bool shop);
	void TicketSmallDraw(bool boss);
	void BulletDisp(int num);
};
