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
	fopen_s(&save_file, file_name, "wb");
	if (save_file == NULL) {				//ファイルが開けないとき
		font(U"セーブファイルが開けませんでした");
	}
	else {
		fwrite(&status, sizeof(STATUS), 1, save_file);
		fwrite(&map_status, sizeof(MAP_STATUS), 1, save_file);
	}
	fclose(save_file);
}

void GAME_STATUS::LoadSave() {				//データをロードする関数
	fopen_s(&save_file, file_name, "rb");
	if (save_file == NULL) {				//ファイルが開けないとき　新しいセーブデータを生成する
		Init();
		SaveData();
	}
	else {
		fread(&status, sizeof(STATUS), 1, save_file);
		fread(&map_status, sizeof(MAP_STATUS), 1, save_file);
	}
	fclose(save_file);
}

void GAME_STATUS::Init() {					//初めてセーブデータを生成するときに呼び出す関数　
	status.player_hp = 3;					//playerのhp
	status.gravity = 0.25f;					//重力
	status.speed = 20.0f;					//スピード
	status.bullets_num = 1;					//playerが打つことができる弾の数
	status.bullets_power = 1;
	map_status.tutorial_flag = false;		//チュートリアルが終わっているかのフラグ
	for (int e = 0; e < 6; e++) {
		map_status.stage_flag[e] = false;		//ステージが解放されているかのフラグ
	}
	map_status.money = 0;					//所持金変数
}

void GAME_STATUS::SetHp(int hp) {			//player HPのセッター
	status.player_hp = hp;
}

int GAME_STATUS::GetHp() {					//player HPのゲッター
	return status.player_hp;
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

void GAME_STATUS::SetBulletsNum(int bullets_num) {	//playerの打てる銃弾の数のセッター
	status.bullets_num = bullets_num;
}

int GAME_STATUS::GetBulletsNum() {			//弾数のゲッター
	return status.bullets_num;
}

void GAME_STATUS::SetBulletPower(float power) {
	status.bullets_power = power;
}

float GAME_STATUS::GetBulletPower() {
	return status.bullets_power;
}

void GAME_STATUS::SetTicket(int money) {		//所持金のセッター
	map_status.money = money;
}

int GAME_STATUS::GetTicket() {				//所持金のゲッター
	return map_status.money;
}

void GAME_STATUS::SetTutorialFlag(bool tutorial_flag) {	//チュートリアルが終了しているかどうかのセッター
	map_status.tutorial_flag = tutorial_flag;
}

bool GAME_STATUS::getTutorialFlag() {		//チュートリアルのゲッター
	return map_status.tutorial_flag;
}

void GAME_STATUS::SetStageFlag(bool st_flag, int st_num) {	//どこのステージまで開放しているかのセッター
	map_status.stage_flag[st_num] = st_flag;
}

bool GAME_STATUS::GetStageFlag(int st_num) {	//ステージ解放のゲッター
	return map_status.stage_flag[st_num];
}
