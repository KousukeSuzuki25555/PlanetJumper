#pragma once

#define STAGE_MAX	(4)

struct STATUS {				//セーブする項目の構造体
	int playerHp;			//playerのhp
	float gravity;			//重力
	float speed;			//スピード
	float bulletsPower;	//銃弾の攻撃力
	int bulletsNum;		//playerが打つことができる弾の数
	bool cursorGun;			//カーソル銃が解放されているか
};

struct MAP_STATUS {			//Map上で用いる変数の構造体
	bool tutorialFlag;		//チュートリアルが終わっているかのフラグ
	bool stageFlag[STAGE_MAX];		//ステージが解放されているかのフラグ
	int money;				//所持金変数
};

class GAME_STATUS {	
	//ゲーム中に値が変更される変数を格納するクラス
	//デストラクタ、SaveData()からclassの状態を保存することができる
private:
	STATUS status;
	MAP_STATUS map_status;
	FILE* saveFile;
	char fileName[13] = "SaveFile.bin";
	const Font font{ 32 };

public:
	GAME_STATUS();	//コンストラクタ
	~GAME_STATUS();	//デストラクタ
	void SaveData();	//セーブ
	void LoadSave();	//ロード
	void Init();	//初期化
	void SetHp(int hp);	//hpのセッター
	int GetHp();	//hpのゲッター
	void SetGravity(float gravity);	//重力のセッター
	float GetGravity();	//重力のゲッター
	void SetSpeed(float speed);	//スピードのセッター
	float GetSpeed();	//スピードのゲッター
	void SetBulletsNum(int bulletsNum);	//弾数のセッター
	int GetBulletsNum();	//弾数のゲッター
	void SetBulletPower(float power);	//銃弾の強さのセッター
	float GetBulletPower();	//銃弾の強さのゲッター
	void SetCursorGun();	//呼び出されたら銃をゲットできる
	bool GetCursorGun();	//カーソル銃のゲッター
	void SetTicket(int money);	//所持チケット数のセッター
	int GetTicket();	//所持チケット数のゲッター
	void SetTutorialFlag(bool tutorialFlag);	//チュートリアルをクリアしたかセッター
	bool getTutorialFlag();	//チュートリアルをクリアしたかのゲッター
	void SetStageFlag(bool st_flag,int st_num);	//ステージのフラグのセッター
	bool GetStageFlag(int st_num);	//ステージのフラグのゲッター
};
