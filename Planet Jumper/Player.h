#pragma once
#include "Main.h"
#include "Draw.h"
#include "Bullet.h"
#include "Status.h"
#include "Weapon.h"
#include "MyTime.h"

enum ACTION {
	RUN,
	JUMP
};

class PLAYER {	//playerclass
private:
	VECTOR2 pos;	//座標
	VECTOR2 camera;	//カメラ
	I_VECTOR2 uv;	//g_v 0:上半身以外 1:歩き上半身
	I_VECTOR2 bust_uv;	//上半身のuv値
	CLOCK2 anm_time;	//アニメーションに用いる時間変数
	CLOCK2 attack_time;	//攻撃アニメーションに用いる時間変数
	DRAW* pdraw;	
	//BULLET bullet[BULLETS_MAX];	//銃弾　上限:5
	WEAPON weapon;
	GAME_STATUS* pstatus;
	float power;	//攻撃力　銃弾に渡す
	int ground;	//地面の高さ
	int bulletNum;	//銃弾の使用できる最大数
	//int newBullet;	//新しい銃弾を記憶する
	unsigned short int jump_limit;	////ジャンプできる回数
	unsigned short int jump_limit_define;	//地面着地時にjump_limitの初期化に用いる変数
	unsigned short int action;	//playerが何をしているか
	unsigned short int hit_num;	//ヒットしたときに描画するかを決める
	float gravity;	//ジャンプの抵抗
	float jstrength;	//ジャンプの力
	float hit_time;	//ヒット演出に使う
	float g_time;	//アニメーションに使う時間変数
	float hp;	//hp
	float gravity_source;	//重力のもとにになる値
	float speed_source;	//スピードのもとになる値
	bool attack_flag;		//球を打っているかの判定に使う　ダン数を増やす場合配列にする
	bool hit_flag;	//ヒットしたか
	bool draw_flag;	//描画するか
	bool anm_flag;	//アニメーションのフラグ
	bool bossFlag;	//ボス戦かどうか

public:
	PLAYER();	//コンストラクタ
	void PointerInit(GAME_STATUS* pstatus,DRAW* pdraw/*,PLAYER* pplayer*/,MY_TIME* ptime);	//ポインタの初期化
	WEAPON* GetPweapon();	//武器クラスのゲッター
	void Init(int weaponNum);	//初期化
	void BossInit();	//ボスステージで使うとき
	void BossUninit();	//簿p巣戦から抜けるとき
	void GuideInit(bool jump);	//ガイドで使うとき
	void GuideUninit();	//ガイドから抜けるとき
	void Update(float now);	//アップデート関数
	void Draw();	//描画関数
	void Draw(float camera);	//描画関数(float)
	void Draw(VECTOR2 camera);	//描画関数(VECTOR2)
	void Anm();	//アニメーション
	void AttackSet(float now);	//攻撃のセッター
	void AttackUninit();	//攻撃から抜ける関数
	void JumpSet();	//ジャンプのセッター
	void Land();	//地面についたか
	void HartDraw();	//Hpを描画する
	void HartDrawBoss();	//ボス戦で
	void SetStageStatus(int power, unsigned short int jump_limit, unsigned short int strength);	//ステージで用いるステータスの初期化
	void SetGravity(unsigned short int strength);	//重力のセッター
	void SetJumpLimit(unsigned short int strength);	//ジャンプの上限回数のセッター
	void SetWeaponPower(unsigned short int strength);	//銃の攻撃力のセッター
	float GetGrvity();	//重力のゲッター
	float GetPos_y();	//y座標を返す
	VECTOR2 GetPos();	//座標を返す
	I_VECTOR2 GetUv();	//uv値を返す
	I_VECTOR2 GetBustUv();	//上半身のuv値を返す
	void Hit();	//他オブジェクトと当たったら
	void Hit(float atk);	//他オブジェクトと当たったら atk分hpが減る
	void BossstHit(float atk,float now);	//ボス戦で当たったら
	void HitAct(float now);	//hitの実働
	void BossstHitAct(float now);	//ボス戦でのhitの実働
	//VECTOR2 GetBulletPos(int e);	//銃弾の座標のゲッター
	bool GetHitFlag();	//ヒットしているかのゲッター
	//int GetBulletPower(int e);		//銃弾の攻撃力
	//void SetBulletUse(int e);		//弾が当たった際に呼ばれuseを解除する
	float GetHp();	//hpを返す
	//int GetUnuseBullet();	//使っていない銃弾を返す
	//bool GetBulletUse(int e);	//その銃弾が使われているか
	//int BulletNotUse();	//何個銃弾が使われていないか
};
