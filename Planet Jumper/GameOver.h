#pragma once
#include "Main.h"

#define F_GAMEOVER	(Y_MAX/2-60)
#define CONTINUE	(Y_MAX/2)
#define MAP			(Y_MAX/2+32)
#define CURSOR_X	(X_MAX/2-(32*4.5))

class GAMEOVER {	//ゲームオーバーclass
protected:
	const Font font32{ 32 };
	const Font font48{ 48 };
	bool cursor;	//trueでcontinue

public:
	GAMEOVER();	//コンストラクタ
	void Update();	//アップデート関数
	bool GetCursor();	//カーソルの位置のゲッター
};
