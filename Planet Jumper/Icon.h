#pragma once
#include "Main.h"
#include "Draw.h"

struct ICON_ST {	//アイコンの状態などを保存する
	VECTOR2 pos;
	I_VECTOR2 uv;
	I_VECTOR2 unuse_uv;
};

class ICON {	//ゲーム画面に表示するアイコンのclass
private:
	unsigned short int weapon;	//攻撃
	unsigned short int speed;	//スピード
	unsigned short int gravity;	//重力
	unsigned short int jump;	//ジャンプ
	ICON_ST weapon1;	//中攻撃
	ICON_ST weapon2;	//強攻撃
	ICON_ST speed1;	//中速
	ICON_ST speed2;	//高速
	ICON_ST gravity1;	//中重力
	ICON_ST gravity2;	//強重力
	ICON_ST jump1;	//２段
	ICON_ST jump2;	//	３段
	ICON_ST frame;	//フレーム
	DRAW* pdraw;
	//const Font font60{ 60 };
public:
	ICON();	//コンストラクタ
	void PointerInit(DRAW* pdraw);	//ポインタの初期化
	void GuideInit();	//ガイドの初期化
	void Init();	//使用時の初期化
	void Update();	//アップデート関数
	void Draw();	//描画関数
	void KeyGet();	//キー受付
	unsigned short int GetGravity();	//重力のゲッター
	unsigned short int GetJump();	//ジャンプのゲッター
	unsigned short int GetSpeed();	//スピードのゲッター
	unsigned short int GetWeapon();	//武器のゲッター
	unsigned short int GetSpeedValue();	//スピードの実数値のゲッター
};
