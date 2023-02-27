#pragma once
#include "Main.h"
#include "Draw.h"


class MAP_ACT {
	const Font font64{ 64 };
	const Font font32{ 32 };
	int cursor;	//カーソルの位置

public:
	MAP_ACT();	//コンストラクタ
	void Init();	//初期化
	void Update();	//アップデート関数
	void KeyGet();	//キー受付
	void Draw();	//描画関数
	int GetStage();	//どこのステージか
};
