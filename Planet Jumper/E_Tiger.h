#pragma once
#include "Block.h"
#include "TicketPlayGame.h"
#include "MyTime.h"
#include "Weapon.h"

struct VECTOR3 {
	VECTOR2 p1;
	VECTOR2 p2;
	VECTOR2 p3;
};

class TIGER :public BLOCK {	//虎class
private:
	VECTOR3 point1;			//中心点から各頂点までの距離 []=v,[]=x
	VECTOR2 bullet_pos;		//座標
	VECTOR2 camera;			//cameraのpos
	VECTOR2 p_vertex[4];	//playerの中心からの座標
	MY_TIME* ptime;
	Ticket* pticket;
	WEAPON* pweapon;
	int move_speed[2];		//移動スピード
	int move_pt;			//歩いているかは知っているか　0=歩き　1=走り
	int hp;					//hp
	float time;				//移動などに使う時間関数
	float anm_time;			//アニメーションに用いる時間変数
	float hit_time;			//ヒット演出に用いる時間変数
	bool exist;				//存在するか
	bool hit;				//攻撃を食らったか

public:
	TIGER();				//コンストラクタ
	void PointerInit(DRAW* pdraw, PLAYER* pplayer,MY_TIME* ptime, WEAPON* pweapon);
	void PointerInit(DRAW* pdraw, PLAYER* pplayer,Ticket* pticket,MY_TIME* ptime, WEAPON* pweapon);
	void GuideInit(bool jump);	//Guideで使う際の初期化
	void Update();	//虎のアップデート関数
	void GuideUpdate();	//ガイドで使うアップデート関数
	void HitSet();	//Hitの動作に関する変数の初期化
	void HitUninit();		//Hitの抜け出す処理
	bool GetExist();		//existのゲッター
	void PlayerHit();		//playerとの当たり判定
	void BulletHit();		//銃弾との当たり判定
	void Init(float rotate,int bulletNum);	//使う際の初期化
	float GetRotate();		//回転のゲッター	
	VECTOR2 GetPos();		//posのゲッター
	I_VECTOR2 GetUv();		//uv値のゲッター
	void Draw(float camera);	//描画
	void Draw();
	void TicketGet();	//チケットを入手するかの関数
	//bool DDraw();
};
