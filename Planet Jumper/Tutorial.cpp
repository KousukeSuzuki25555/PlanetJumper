#include "Tutorial.h"

TUTORIAL::TUTORIAL() {		//チュートリアルのコンストラクタ
	now = 0.0f;					//プログラム内の時間を入れる
	rot = 0.0f;					//ステージ内の回転を入れる
	speed = NORMAL;				//ステージのスピード(iconから変更できる)
	//gravity = NORMAL;			//ステージの重力(iconから変更できる)
	//jump = NORMAL;				//ステージのジャンプ(iconから変更できる)
	speedValue = SPEED_NOR;	//スピードの実数値を入れる
	meterTime = (float)clock() / 1000;	//メーターのアニメーションに使う時間を入れる
	meterAnm = true;			//メーターのアニメーションに使う
	text = START;
	tTime= (float)clock() / 1000;
	key_get = false;
	buildSize[0] = {64,64};
	buildSize[1] = { 128,128 };
	buildInitFlag = false;
	//pplayer = &player;
	enemyInitFlag = false;
	bulletHit = false;
	usePolice = false;
	useTiger = false;
	useBlock = false;
	tFlag = true;
	//cloud.Init(1, 1200, 1.6);
}

void TUTORIAL::PointerInit(GAME_STATUS* pstatus,DRAW* pdraw,PLAYER* pplayer,MY_TIME* ptime) {
	this->pplayer = pplayer;
	this->pdraw = pdraw;
	this->pstatus = pstatus;
	this->ptime = ptime;
	pplayer->PointerInit(pstatus, pdraw/*, pplayer*/, ptime);
	pweapon = pplayer->GetPweapon();
	icon.PointerInit(pdraw);
	block.PointerInit(pdraw,pplayer,pweapon);
	tiger.PointerInit(pdraw,pplayer,ptime,pweapon);
	ground.PointerInit(pdraw);
	pplayer->Init(0);
}

void TUTORIAL::Update() {
	if (KeyEnter.down()) {
		tFlag = false;
	}
	/******************************************************************************
	ICONの処理
	*******************************************************************************/
	icon.Update();						//アイコンのアップデート
	//jump = icon.GetJump();				//jumpにplayerのジャンプ力を入れる
	//gravity = icon.GetGravity();		//gravityにステージの重力を入力
	if (icon.GetSpeed() != speed) {		//speedが異なったらspeedValueにスピードの値を入れる
		speed = icon.GetSpeed();
		if (speed == STRONG) {
			speedValue = SPEED_FAST;
		}
		else if (speed == NORMAL) {
			speedValue = SPEED_NOR;
		}
		else {
			speedValue = SPEED_SLOW;
		}
	}

	/******************************************************************************
	PLAYERの処理
	*******************************************************************************/
	pplayer->SetGravity(icon.GetGravity());		//playerに重力をセット
	pplayer->SetJumpLimit(icon.GetJump());		//playerにジャンプをセット
	pplayer->SetWeaponPower(icon.GetWeapon());
	pplayer->Update(now);				//playerのアップデート

	/******************************************************************************
	POLICEの処理
	*******************************************************************************/
	police.SetGravity(icon.GetGravity());
	police.SetPpos(pplayer->GetPos_y());
	if (usePolice == true) {
		police.Update(speedValue);
	}
	bulletHit=police.GetBulletHit();
	if (bulletHit == true) {
		pplayer->Hit();
		bulletHit = false;
	}

	//police.BulletDraw();

	/******************************************************************************
	フレームごとのステージの標準的な処理
	*******************************************************************************/
	ptime->Update();				//時間の更新
	rot -= (ptime->GetTime() - now) / speedValue;		//ステージで使う回転の基準
	now = ptime->GetTime();		//変数に今の時間を保存

	/******************************************************************************
	WINDOWの処理
	*******************************************************************************/
	if (now - meterTime > 0.5f) {
		switch (meterAnm) {
		case true:
			meterAnm = false;
			break;

		case false:
			meterAnm = true;
			break;
		}
		meterTime = now;
	}

	//tdraw.Update();
	Draw();
	TutorialAct();
}

void TUTORIAL::T_BlockInit1() {
	block.Init(speedValue, 1.7f, buildSize[0], 256, 0, pstatus->GetBulletsNum());
	buildInitFlag = true;
	useBlock = true;
	rot = 0.0f;
}

void TUTORIAL::T_BlockInit2() {
	block.Init(speedValue, 1.7f, buildSize[1],0, 0, pstatus->GetBulletsNum());
	useBlock = true;
	buildInitFlag = true;
	rot = 0.0f;
}

void TUTORIAL::T_EnemyInit() {
	enemyTime = now;
	tiger.Init(1.65f/*,now-enemy_time*/, pstatus->GetBulletsNum());
	enemyInitFlag = true;
	useTiger = true;
	//tdraw.TigerUse();
}

void TUTORIAL::Draw() {
	if (pplayer->GetPos_y() < 64.0f) {
		camera = 64 - pplayer->GetPos_y();
	}
	else {
		camera = 0.0f;
	}
	pdraw->BackDraw();
	ground.Draw(camera);
	pplayer->Draw(camera);
	//player.BulletDraw();
	if (usePolice == true) {
		police.Draw(camera);
		//police.BulletDraw();
	}
	if (useTiger == true) {
		tiger.Draw(camera);
	}
	if (useBlock == true) {
		block.Draw(camera);
	}
	pplayer->HartDraw();
	//cloud.Draw(camera);
	pdraw->WindowDraw(meterAnm, police.GetRot());			//ウィンドウの描画
	icon.Draw();
}

void TUTORIAL::Init() {
	pplayer->Init(0);
}

void TUTORIAL::TutorialAct() {
	/******************************************************************************
	チュートリアルの処理
	*******************************************************************************/
	pdraw->TutorialBackDraw(0.0f,0.0f);
	switch (text) {
	case START:
		font(U"これからチュートリアルを始めるよ").draw(0, 0);
		if (now - tTime > 2) {
			text = EXP_JUMP;
			tTime = now;
		}
		break;

	case EXP_JUMP:
		switch (key_get) {
		case false:
			font(U"まずはJを押してくれるかな？ジャンプができるよ").draw(0, 0);
			if (KeyJ.down()) {
				key_get = true;
				tTime = now;
			}
			break;

		case true:
			if (now - tTime < 2.0f) {
				font(U"よくできたね").draw(0, 0);
			}
			else if (now - tTime < 4.0f) {
				font(U"前から建物が近づいてくるよ!ジャンプしてよけてみよう").draw(0, 0);
			}
			else {
				font(U"空中でもう一度Jを押すことで二段ジャンプができるよ").draw(0, 0);
			}
			switch (buildInitFlag) {
			case false:	//blockのInit
				T_BlockInit1();
				break;

			case true:	//blockをジャンプでよける
				block.Update(rot);
				if (pplayer->GetHitFlag() == true) {
					buildInitFlag = false;
				}
				if (1.8f + rot < 1.47) {	//playerがよけれたら次のチュートリアルへ移る
					text = EXP_ATTACK;
					tTime = now;
					key_get = false;
					buildInitFlag = false;
					useBlock = false;
				}

				break;
			}
		}
		break;
	case EXP_ATTACK:	//ATTACKのチュートリアル
	{
		switch (key_get) {
		case false:

			font(U"次は攻撃だよ！SPACEを押してみてね").draw(0, 0);
			if (KeySpace.down()) {
				key_get = true;
				tTime = now;
			}
			break;

		case true:
			font(U"前から敵が来るから倒してみよう 2回攻撃を充てると倒せるよ").draw(0, 0);

			switch (enemyInitFlag) {
			case false:
				T_EnemyInit();
				break;

			case true:
				if (tiger.GetExist() == true) {
					tiger.Update(/*now - enemy_time*/);
				}
			}
			if (tiger.GetRotate() < 1.45) {
				enemyInitFlag = false;
			}
			else if (tiger.GetExist() == false) {	//倒すことができたら
				text = EXP_ICON;
				tTime = now;
				key_get = false;
				enemyInitFlag = false;
				useTiger = false;
				//tdraw.TigerUse();
			}

			break;
		}
		break;
	}
	case EXP_ICON:	//アイコンの説明
	{

		if (now - tTime < 3) {
			font(U"次は外面下の説明をするね").draw(0, 0);
		}
		else if (now - tTime < 7.5) {
			font(U"まずは右下のアイコンからだよ").draw(0, 0);
		}

		if (now - tTime > 6 && now - tTime < 6.5) {
			pdraw->TutorialHighlight();
		}
		else if (now - tTime > 7 && now - tTime < 7.5) {
			pdraw->TutorialHighlight();
		}
		else if (now - tTime > 7.5 && now - tTime < 10.5) {
			font(U"アイコンはプレイヤーのステータスを変化させるよ").draw(0, 0);
		}
		else if (now - tTime > 10.5) {
			text = EXP_Y;
			tTime = now;
		}
		break;
	}
	case EXP_Y:
	{
		switch (key_get)
		{
		case false:
			font(U"まずは攻撃力だよ!Yを押してみてね").draw(0, 0);

			if (KeyY.down()) {
				key_get = true;
				tTime = now;
			}
			break;
		case true:
			if (now - tTime < 3) {
				font(U"このアイコンは攻撃力を上げる力を持っているよ").draw(0, 0);
			}
			else {
				font(U"前から敵が来るよ!攻撃力を上げて倒してみよう").draw(0, 0);
			}
			switch (enemyInitFlag) {
			case false:
				T_EnemyInit();
				break;

			case true:
				if (tiger.GetExist() == true) {
					tiger.Update(/*now - enemy_time*/);
					/*tdraw.SetTigerPos(tiger.GetPos());
					tdraw.SetTigerUv(tiger.GetUv());
					tdraw.SetTigerRot(tiger.GetRotate());
					tdraw.TigerDDraw(tiger.DDraw());*/
				}

				if (tiger.GetExist() == false && icon.GetWeapon() == STRONG) {	//playerがよけれたら次のチュートリアルへ移る
					text = EXP_U;
					tTime = now;
					key_get = false;
					useTiger = false;
					//tdraw.TigerUse();
				}

				if (tiger.GetRotate() < 1.45) {	//倒すことができなかったらもう一度
					enemyInitFlag = false;
					//tdraw.TigerUse();
				}

				break;
			}
			break;
		}
		break;
	}
	case EXP_U:
		switch (key_get)
		{
		case false:
			font(U"次にUを押してみてね").draw(0, 0);

			if (KeyU.down()) {
				key_get = true;
				tTime = now;
			}
			break;
		case true:
			if (now - tTime < 3) {
				font(U"このアイコンは攻撃力を通常通りにするよ").draw(0, 0);
			}
			else {
				text = EXP_I;
				key_get = false;
				tTime = now;
			}
			break;
		}
		break;
	case EXP_I:
	{
		switch (key_get)
		{
		case false:
			font(U"次は重力だよ!Iを押してみてね").draw(0, 0);

			if (KeyI.down()) {
				key_get = true;
				tTime = now;
			}
			break;
		case true:
			if (now - tTime < 3) {
				font(U"このアイコンは重力を弱める力を持っているよ").draw(0, 0);
			}
			else if (/*now - tTime > 3 &&*/ now - tTime < 6) {
				font(U"ジャンプして体感してみよう").draw(0, 0);
			}
			switch (buildInitFlag) {
			case false:	//blockのInit
				T_BlockInit2();
				break;

			case true:	//blockをジャンプでよける
				block.Update(rot);
				if (pplayer->GetHitFlag() == true) {
					buildInitFlag = false;
				}
				if (1.8f + rot < 1.47) {	//playerがよけれたら次のチュートリアルへ移る
					text = EXP_K;
					tTime = now;
					key_get = false;
					buildInitFlag = false;
					useBlock = false;
				}

				break;
			}
			break;
		}
		break;
	}
	case EXP_K:
	{
		switch (key_get)
		{
		case false:
			font(U"次にKを押してみてね").draw(0, 0);

			if (KeyK.down()) {
				key_get = true;
				tTime = now;
			}
			break;
		case true:
			if (now - tTime < 3) {
				font(U"このアイコンは重力をを通常通りにするよ").draw(0, 0);
			}
			else {
				text = EXP_N;
				key_get = false;
				tTime = now;
			}
			break;
		}
		break;

	case EXP_N:
	{
		switch (key_get)
		{
		case false:
			font(U"次はジャンプ回数だよ!Nを押してみてね").draw(0, 0);

			if (KeyN.down()) {
				key_get = true;
				tTime = now;
			}
			break;
		case true:
			if (now - tTime < 3) {
				font(U"このアイコンはジャンプ回数を3回にする力を持っているよ").draw(0, 0);
			}
			else if (/*now - tTime > 3 &&*/ now - tTime < 6) {
				font(U"ジャンプ中にJボタンを2回押してみよう").draw(0, 0);
			}
			else {
				text = EXP_H;
				key_get = false;
				tTime = now;
			}
			break;
		}
		break;
	}
	case EXP_H: {
		switch (key_get)
		{
		case false:
			font(U"次にHを押してみてね").draw(0, 0);

			if (KeyH.down()) {
				key_get = true;
				tTime = now;
			}
			break;
		case true:
			if (now - tTime < 3) {
				font(U"このアイコンは二段ジャンプにするよ").draw(0, 0);
			}
			else {
				text = EXP_COMMA;
				key_get = false;
				tTime = now;
			}
			break;
		}
		break;
	}
	case EXP_COMMA:
	{
		switch (key_get)
		{
		case false:
			font(U"次は走るスピードだよ!コンマを押してみてね").draw(0, 0);

			if (KeyComma.down()) {
				key_get = true;
				tTime = now;
			}
			break;
		case true:
			if (now - tTime < 3) {
				font(U"このアイコンは走るスピードを速くする力を持っているよ").draw(0, 0);
			}
			else if (/*now - tTime > 3 &&*/ now - tTime < 6) {
				font(U"後ろから追いかけてくる敵から逃げてみよう").draw(0, 0);
				usePolice = true;
				//tdraw.PoliceUse();
				police.PointerInit(pdraw, pplayer,ptime);
				police.RotInit();
			}
			else {
				text = EXP_M;
				key_get = false;
				tTime = now;
			}
			break;
		}
		break;
	}
	case EXP_M: {
		switch (key_get)
		{
		case false:
			font(U"次にMを押してみてね").draw(0, 0);

			if (KeyM.down()) {
				key_get = true;
				tTime = now;
			}
			break;
		case true:
			if (now - tTime < 3) {
				font(U"このアイコンは普通のスピードにするよ").draw(0, 0);
			}
			else {
				text = EXP_CNC;
				key_get = false;
				tTime = now;
			}
			break;
		}
		break;
	}
	case EXP_CNC: {	//iconまとめ

		if (now - tTime < 3) {
			font(U"実はアイコンは一つの列に一つしか選択できないんだ...").draw(0, 0);
		}
		else if (now - tTime < 6) {
			font(U"もし選択されていないステータスがあるとそのステータスは弱体化されるよ").draw(0, 0);
		}
		else {
			font(U"Nを押してみて!スピードが弱体化して後ろにいる敵に追いつかれるよ").draw(0, 0);
			if (KeyN.down()) {
				text = EXP_METER;
				tTime = now;
			}
		}
		break;
	}
	case EXP_METER: {
		if (now - tTime < 3) {
			font(U"次に左下のメーターについて説明するね").draw(0, 0);
		}
		else if (now - tTime < 8) {
			font(U"このメーターは後ろの敵との距離を表しているよ").draw(0, 0);
		}
		else if (now - tTime < 13) {
			font(U"主人公は後ろの敵から攻撃を食らうとHPが減ってしまうよ").draw(0, 0);
		}
		else if (now - tTime < 18) {
			font(U"あと後ろの敵から追いつかれてしまうとその時点でゲームオーバーだよ!").draw(0, 0);
		}
		else {
			font(U"これでチュートリアルは終了だよ!終了する場合はEnterを押してね");
			if (KeyEnter.down()) {
				tFlag = false;
			}
		}

		break;
	}
	}

	}
}

bool TUTORIAL::GetContinue() {
	return tFlag;
}
