#pragma once
#include "Main.h"
#include "MyTime.h"
#include "Player.h"
#include "Draw.h"

class LASER {
	VECTOR2 pos;
	VECTOR2 camera;
	VECTOR2 moveNormalize;	//移動時の基準となる数値
	VECTOR2 n_vertex[4];		//blockの頂点
	VECTOR2 p_vertex[4];	//playerの中心からの座標
	PLAYER* pplayer;
	MY_TIME* ptime;
	DRAW* pdraw;
	float rot;				//Laserの回転角度
	float time;
	float speedTime;	//speed更新するタイミング
	float initSpeed;	//初期化されたときのスピード　変更されたらLaserのrotが移動
	float speed;
	int anm;				//どっちの絵を使用するか
	bool exist;
	bool d_vertex[4];			//各頂点の外積が内側にあるか判定

public:
	LASER();	//コンストラクタ
	void PointerInit(PLAYER* pplayer,DRAW* pdraw,MY_TIME* ptime);	//ポインタの初期化関数
	void Init(VECTOR2 pos,float speed);	//初期化関数
	void Update();	//アップデート関数
	void PlayerHit();	//プレイヤーとの当たり判定
	void GroundHit();	//地面との当たり判定
	void Move();		//移動関数
	void SpeedChange();	//スピードが変更されたか
	void GetNormalize();	//移動際の正規化された値を作る
	void Draw(float camera);	//描画関数
	void DetectReset();
	void SetSpeed(float speed);
	bool GetExist();	//existのゲッター
};
