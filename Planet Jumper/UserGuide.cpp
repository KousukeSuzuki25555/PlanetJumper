#include "UserGuide.h"

#define TITLE_X		(32)
#define CURSOR_X	(166)
#define CONTENT_X	(198)
#define SENTENCE_X	(450)
#define GRAVITY_Y	(Y_MAX-64*4-32)
#define ATTACK_X	(X_MAX-64*4)

UserGuide::UserGuide() {
	time = 0.0f;
	cursor = U_JUMP;
	oldCursor = cursor;
	guideJump = true;
	pdraw = 0;
	pplayer = 0;
	pstatus = 0;
}

void UserGuide::PointerInit(GAME_STATUS* pstatus,DRAW* pdraw, PLAYER* pplayer) {
	this->pdraw = pdraw;
	this->pplayer = pplayer;
	pplayer->DrawPointerInit(pdraw);
	tiger.PointerInit(pdraw,pplayer);
	this->pstatus = pstatus;
	icon.PointerInit(pdraw);
}

void UserGuide::Init(float now) {
	pplayer->GuideInit(guideJump);
	time = now;
	pplayer->Init(pstatus);
	pplayer->GuideInit(true);
	icon.Init();
	icon.GuideInit();
	cursor = U_JUMP;
}

void UserGuide::Update(float now) {

	switch (cursor) {
	case U_JUMP:			//ジャンプ
		font32(U"Jを押す").draw(SENTENCE_X, U_JUMP);
		if (KeyDown.down()) {
			cursor = DOUBLE_JUMP;
		}
		else if (KeyUp.down()) {
			cursor = SLOW_RUN;
		}
		break;

	case DOUBLE_JUMP:	//二段ジャンプ
		font32(U"(ジャンプアクション中に)Jを押す").draw(SENTENCE_X, DOUBLE_JUMP);
		if (KeyDown.down()) {
			cursor = TRIPLE_JUMP;
		}
		else if (KeyUp.down()) {
			cursor = U_JUMP;
		}
		break;

	case TRIPLE_JUMP:	//三段ジャンプ
		font32(U"Nを押しアイコン変更 (二段ジャンプ中に)Jを押す").draw(SENTENCE_X, TRIPLE_JUMP);

		if (KeyDown.down()) {
			cursor = SINGLE_JUMP;
		}
		else if (KeyUp.down()) {
			cursor = DOUBLE_JUMP;
		}
		break;

	case SINGLE_JUMP:	//一段ジャンプ
		font32(U"ジャンプアイコンを選択しない").draw(SENTENCE_X, SINGLE_JUMP);
		if (KeyDown.down()) {
			cursor = STRONG_JUMP;
		}
		else if (KeyUp.down()) {
			cursor = TRIPLE_JUMP;
		}
		break;

	case STRONG_JUMP:	//高いジャンプ
		font32(U"Iを押し重力強化アイコン選択中に Jを押す").draw(SENTENCE_X, STRONG_JUMP);
		if (KeyDown.down()) {
			cursor = WEAK_JUMP;
		}
		else if (KeyUp.down()) {
			cursor = SINGLE_JUMP;
		}
		break;

	case WEAK_JUMP:		//低いジャンプ
		font32(U"重力アイコンを選択しない").draw(SENTENCE_X, WEAK_JUMP);
		if (KeyDown.down()) {
			cursor = DODGE_ENEMY;
		}
		else if (KeyUp.down()) {
			cursor = STRONG_JUMP;
		}
		break;

	case DODGE_ENEMY:	//敵をよける
		tiger.GuideUpdate(now);
		font32(U"敵をよけてみよう").draw(SENTENCE_X, DODGE_ENEMY);
		if (KeyDown.down()) {
			cursor = ATTACK;
		}
		else if (KeyUp.down()) {
			cursor = WEAK_JUMP;
		}
		break;

	case ATTACK:		//攻撃
		font32(U"Spaceを押す").draw(SENTENCE_X, ATTACK);
		if (KeyDown.down()) {
			cursor = STRONG_ATTACK;
		}
		else if (KeyUp.down()) {
			cursor = DODGE_ENEMY;
		}
		break;

	case STRONG_ATTACK:	//強い攻撃
		font32(U"Yを押す").draw(SENTENCE_X, STRONG_ATTACK);
		if (KeyDown.down()) {
			cursor = WEAK_ATTACK;
		}
		else if (KeyUp.down()) {
			cursor = ATTACK;
		}
		break;

	case WEAK_ATTACK:	//弱い攻撃
		font32(U"攻撃アイコンを選択しない").draw(SENTENCE_X, WEAK_ATTACK);
		if (KeyDown.down()) {
			cursor = SHOT_ENEMY;
		}
		else if (KeyUp.down()) {
			cursor = STRONG_ATTACK;
		}
		break;

	case SHOT_ENEMY:	//敵を打つ
		tiger.GuideUpdate(now);
		font32(U"敵を撃つ").draw(SENTENCE_X, SHOT_ENEMY);
		if (KeyDown.down()) {
			cursor = U_RUN;
		}
		else if (KeyUp.down()) {
			cursor = WEAK_ATTACK;
		}
		break;

	case U_RUN:			//走る
		font32(U"自動で走ります").draw(SENTENCE_X, U_RUN);
		if (KeyDown.down()) {
			cursor = FAST_RUN;
		}
		else if (KeyUp.down()) {
			cursor = SHOT_ENEMY;
		}
		break;

	case FAST_RUN:		//速く走る
		font32(U"<を押しアイコンを変更する").draw(SENTENCE_X, FAST_RUN);
		if (KeyDown.down()) {
			cursor = SLOW_RUN;
		}
		else if (KeyUp.down()) {
			cursor = U_RUN;
		}
		break;

	case SLOW_RUN:		//ゆっくり走る
		font32(U"スピードアイコンを選択しない").draw(SENTENCE_X, SLOW_RUN);
		if (KeyDown.down()) {
			cursor = U_JUMP;
		}
		else if (KeyUp.down()) {
			cursor = FAST_RUN;
		}
		break;
	}

	pplayer->Update(now);

	if (cursor < ATTACK) {
		guideJump = true;
	}
	else {
		guideJump = false;
	}

	if (cursor != oldCursor) {
		pplayer->GuideInit(guideJump);

		if (cursor == DODGE_ENEMY ||cursor == SHOT_ENEMY) {
			tiger.Init(0.0f, 0.0f, pstatus->GetBulletsNum());
			tiger.GuideInit(now, guideJump);
		}
	}

	icon.Update();
	pplayer->SetStageStatus(icon.GetWeapon(), icon.GetJump(), icon.GetGravity());	//playerにステージのステータスを入力


	Draw();

	oldCursor = cursor;
}

void UserGuide::Draw() {
	font64(U"操作説明").draw(TITLE_X, TITLE);
	font32(U"▶").draw(CURSOR_X, cursor);
	font32(U"ジャンプ").draw(TITLE_X, U_JUMP);
	font32(U"攻撃").draw(TITLE_X, ATTACK);
	font32(U"走る").draw(TITLE_X, U_RUN);
	font32(U"通常ジャンプ").draw(CONTENT_X, U_JUMP);
	font32(U"二段ジャンプ").draw(CONTENT_X, DOUBLE_JUMP);
	font32(U"三段ジャンプ").draw(CONTENT_X, TRIPLE_JUMP);
	font32(U"一段ジャンプ").draw(CONTENT_X, SINGLE_JUMP);
	font32(U"高いジャンプ").draw(CONTENT_X, STRONG_JUMP);
	font32(U"低いジャンプ").draw(CONTENT_X, WEAK_JUMP);
	font32(U"実践:敵をよける").draw(CONTENT_X, DODGE_ENEMY);
	font32(U"攻撃").draw(CONTENT_X, ATTACK);
	font32(U"強い攻撃").draw(CONTENT_X, STRONG_ATTACK);
	font32(U"弱い攻撃").draw(CONTENT_X, WEAK_ATTACK);
	font32(U"実践:敵を撃つ").draw(CONTENT_X, SHOT_ENEMY);
	font32(U"走る").draw(CONTENT_X, U_RUN);
	font32(U"速く走る").draw(CONTENT_X, FAST_RUN);
	font32(U"遅く走る").draw(CONTENT_X, SLOW_RUN);
	pdraw->GuideDraw(guideJump);
	pplayer->Draw();
	if ((cursor == DODGE_ENEMY || cursor == SHOT_ENEMY)&&tiger.GetExist()==true) {
		tiger.Draw();
	}
	icon.Draw();

	//アイコンのせつめい文字
	font32(U"攻撃力").draw(ATTACK_X, GRAVITY_Y - 40);
	font32(U"スピード").draw(ATTACK_X + 64, GRAVITY_Y+64*3);
	font32(U"ジ").draw(ATTACK_X - 32, GRAVITY_Y + 64);
	font32(U"ャ").draw(ATTACK_X - 32, GRAVITY_Y + 64 + 32 * 1);
	font32(U"ン").draw(ATTACK_X - 32, GRAVITY_Y + 64 + 32 * 2);
	font32(U"プ").draw(ATTACK_X - 32, GRAVITY_Y + 64 + 32 * 3);
	font32(U"回").draw(ATTACK_X - 32, GRAVITY_Y + 64 + 32 * 4);
	font32(U"数").draw(ATTACK_X - 32, GRAVITY_Y + 64 + 32 * 5);
	font32(U"重").draw(ATTACK_X+64*3, GRAVITY_Y);
	font32(U"力").draw(ATTACK_X+64*3, GRAVITY_Y + 32);
}

void UserGuide::GetCursor() {

}

