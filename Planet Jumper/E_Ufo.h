#pragma once
#include "Main.h"
#include "Player.h"
#include "MyTime.h"
#include "Status.h"
#include "TicketPlayGame.h"
#include "Laser.h"

class UFO {
	VECTOR2 pos;	//座標
	PLAYER* pplayer;	//playerのポインタ
	Ticket* pticket;	//チケットのポインタ
	MY_TIME* ptime;
	DRAW* pdraw;
	GAME_STATUS* pstatus;
	VECTOR2 camera;			//cameraのpos
	VECTOR2 n_vertex[4];		//blockの頂点
	VECTOR2 p_vertex[4];	//playerの中心からの座標
	VECTOR2 bulletPos;		//銃弾の座標
	LASER laser;
	//float hp;					//hp
	int bulletNum;			//銃弾の使用できる最大数
	int drawNum;			//何番目の画像を表示するか
	float time;				//移動などに使う時間関数
	float moveTime;			//移動するタイミング
	float attackTime;		//攻撃するタイミング
	float anmTime;			//描画を切り替えるタイミング
	float speed;			//移動スピード
	bool exist;				//存在するか
	bool hit;				//攻撃を食らったか
	bool d_vertex[4];			//各頂点の外積が内側にあるか判定

public:
	UFO();
	void Init(int bulletNum);
	void PointerInit(PLAYER* pplayer, Ticket* pticket,MY_TIME* ptime,GAME_STATUS* pstatus,DRAW* pdraw);
	void Update();
	void Move();	//移動関数
	void Attack();	//攻撃関数
	void Anm();		//描画関数
	void MakeMoveTime();	//移動する時間を作る
	void MakeAttackTime();	//攻撃する時間を作る
	void PlayerHit();
	void BulletHit();		//銃弾との当たり判定
	void Draw(float camera);	//描画
	bool GetExist();		//existのゲッター
	void DetectReset();
	void SetSpeed(float speed);		//speedのセッター
};
