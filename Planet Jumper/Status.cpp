#include "Status.h"

GAME_STATUS::GAME_STATUS() {				//ステータスのコンストラクタ
	status = { 0,0.0f,0.0f,0.0f,0 };
	map_status = { false,false,false,false,false,0 };
	LoadSave();
}

GAME_STATUS::~GAME_STATUS() {				//デストラクタ
	//SaveData();
}

void GAME_STATUS::SaveData() {				//データをセーブする関数
	fopen_s(&saveFile, fileName, "wb");
	if (saveFile == NULL) {				//ファイルが開けないとき
		font(U"セーブファイルが開けませんでした");
	}
	else {
		fwrite(&status, sizeof(STATUS), 1, saveFile);
		fwrite(&map_status, sizeof(MAP_STATUS), 1, saveFile);
	}
	fclose(saveFile);
}

void GAME_STATUS::LoadSave() {				//データをロードする関数
	fopen_s(&saveFile, fileName, "rb");
	if (saveFile == NULL) {				//ファイルが開けないとき　新しいセーブデータを生成する
		Init();
		SaveData();
	}
	else {
		fread(&status, sizeof(STATUS), 1, saveFile);
		fread(&map_status, sizeof(MAP_STATUS), 1, saveFile);
	}
	fclose(saveFile);
}

void GAME_STATUS::Init() {					//初めてセーブデータを生成するときに呼び出す関数　
	status.playerHp = 3;					//playerのhp
	status.gravity = 0.25f;					//重力
	status.speed = 20.0f;					//スピード
	status.bulletsNum = 1;					//playerが打つことができる弾の数
	status.bulletsPower = 1;
	status.cursorGun = false;			//カーソル銃が解放されているか
	map_status.tutorialFlag = false;		//チュートリアルが終わっているかのフラグ
	for (int e = 0; e < STAGE_MAX; e++) {
		map_status.stageFlag[e] = false;		//ステージが解放されているかのフラグ
	}
	map_status.money = 0;					//所持金変数
}

void GAME_STATUS::SetHp(int hp) {			//player HPのセッター
	status.playerHp = hp;
}

int GAME_STATUS::GetHp() {					//player HPのゲッター
	return status.playerHp;
}

void GAME_STATUS::SetGravity(float gravity) {	//ジャンプの際などに用いる重力のセッター
	status.gravity = gravity;
}

float GAME_STATUS::GetGravity() {			//重力のゲッター
	return status.gravity;
}

void GAME_STATUS::SetSpeed(float speed) {	//speedのセッター
	status.speed = speed;
}

float GAME_STATUS::GetSpeed() {				//speedのゲッター
	return status.speed;
}

void GAME_STATUS::SetBulletsNum(int bulletsNum) {	//playerの打てる銃弾の数のセッター
	status.bulletsNum = bulletsNum;
}

int GAME_STATUS::GetBulletsNum() {			//弾数のゲッター
	return status.bulletsNum;
}

void GAME_STATUS::SetBulletPower(float power) {
	status.bulletsPower = power;
}

void GAME_STATUS::SetCursorGun() {	//呼び出されたら銃をゲットできる
	status.cursorGun = true;
}

bool GAME_STATUS::GetCursorGun() {	//カーソル銃のゲッター
	return status.cursorGun;
}


float GAME_STATUS::GetBulletPower() {
	return status.bulletsPower;
}

void GAME_STATUS::SetTicket(int money) {		//所持金のセッター
	map_status.money = money;
}

int GAME_STATUS::GetTicket() {				//所持金のゲッター
	return map_status.money;
}

void GAME_STATUS::SetTutorialFlag(bool tutorialFlag) {	//チュートリアルが終了しているかどうかのセッター
	map_status.tutorialFlag = tutorialFlag;
}

bool GAME_STATUS::getTutorialFlag() {		//チュートリアルのゲッター
	return map_status.tutorialFlag;
}

void GAME_STATUS::SetStageFlag(bool stFlag, int stNum) {	//どこのステージまで開放しているかのセッター
	map_status.stageFlag[stNum] = stFlag;
}

bool GAME_STATUS::GetStageFlag(int st_num) {	//ステージ解放のゲッター
	return map_status.stageFlag[st_num];
}
