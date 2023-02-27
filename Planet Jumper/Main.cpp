# include <Siv3D.hpp> // OpenSiv3D v0.6.5
#include "Main.h"
#include "GAMEMANAGER.h"
#include <Math.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "Title.h"
#include "MyTime.h"
#include "Draw.h"
#include "Player.h"
#include "Ground.h"

void Main()
{
	GAME_STATUS* pstatus = new GAME_STATUS;
	Window::Resize(X_MAX, Y_MAX);		//画面サイズの変更
	srand((unsigned)time(NULL));
	/******************************************************************
	変数宣言
	******************************************************************/
	GAMEMANAGER gamemanager;
	GAME_TITLE title;
	MY_TIME time;
	DRAW* pdraw = new DRAW;
	//PLAYER player;
	PLAYER* pplayer = new PLAYER;
	GROUND ground;
	GROUND* pground = &ground;
	bool gameContinue = true;
	bool* pgameContinue = &gameContinue;
	gamemanager.PointerSet(pstatus,pdraw,pplayer,pground,pgameContinue);
	title.PointerSet(pdraw, pplayer, pground);
	ground.PointerInit(pdraw);
	unsigned short int scene_state=SCENE_TITLE;
	float now;

	/******************************************************************
	ゲームループ
	******************************************************************/
	while (System::Update())
	{
		time.Update();
		now = time.GetTime();
		switch (scene_state) {
		case SCENE_TITLE:	//タイトル画面
			title.Update(now);
			if (title.GetTitleFlag() == true) {
				scene_state = SCENE_STAGESELECT;
			}
			break;

		case SCENE_STAGESELECT:	//ステージセレクト画面
			gamemanager.Update(now);

			break;
		}
		if (gameContinue == false) {
			break;
		}
	}
	/******************************************************************
	ゲームループを抜けた後の処理
	******************************************************************/

	delete pstatus;
	delete pplayer;
	delete pdraw;
}

bool HitDetection(VECTOR2 a, VECTOR2 b, VECTOR2 c) {	//当たり判定を外積で求める a:始点 b:同矩形状の終点 c:player等の他矩形上の点
	VECTOR2 A, B;
	A = b - a;
	B = c - a;
	if ((B.x * A.y) - (A.x * B.y) < 0) {	
		return true;	//trueなら内側にある
	}
	else return false;
}

bool PlayerHitDetection(VECTOR2 ppos,VECTOR2 pos,I_VECTOR2 size) {	//player_box内に入っているかの判定
	VECTOR2 ppos1 = { ppos.x - size.u / 2, ppos.y - size.v / 2 };
	VECTOR2 ppos2 = { ppos.x + size.u / 2,ppos.y + size.v / 2 };
	//xが間にあるか
	if (ppos1.x < pos.x && pos.x < ppos2.x) {
		if (ppos.y < pos.y && pos.y < ppos2.y) {
			return true;
		}
	}
	return false;
}

VECTOR2 MakeVirtualPos(VECTOR2 start, VECTOR2 point, float rot) {	//当たり判定のために同一平面上に点を移動する関数
	VECTOR2 goal = start-point;	//減点からのそれぞれの距離を出す
	float distance = hypot(goal.x, goal.y);					//三平方の定理で斜めを出す
	goal.x = -(cosf(rot * PI)) * distance + start.x;		//それぞれのrotでの逆向きに回転した場所を出す
	goal.y = -(sinf(rot * PI)) * distance + start.y;
	return goal;
}

bool LineCollision(float x, float p1, float p2) {
	if ((p1<x && p2>x) || (p1 > x && p2 < x)) {	//x座標が交差している
		return true;
	}
	return false;
}

float Diagonal(VECTOR2 start, VECTOR2 goal) {	//三平方の定理
	return (float)hypot(goal.x - start.x, goal.y - start.y);
}

VECTOR2 VacNormalize(VECTOR2 start, VECTOR2 goal) {	//ベクトルの正規化
	VECTOR2 ans = { (goal.x - start.x) / Diagonal(start,goal) ,(goal.y - start.y) / Diagonal(start,goal) };
	return ans;
}

float Damage(unsigned short int power, GAME_STATUS* pstatus) {
	switch (power) {
	case 3:
		return pstatus->GetBulletPower() + 0.5f;
		break;

	case 2:
		return pstatus->GetBulletPower();
		break;

	case 1:
		return pstatus->GetBulletPower()+power - 0.5f;
		break;
	}
	return 0;
}
