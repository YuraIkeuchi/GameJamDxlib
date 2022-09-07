#pragma once
#include "Share.h"
#include "Player.h"
class Enemy {
public:
	//コンストラクタ
	Enemy();
	//デストラクタ
	~Enemy();

	//更新
	void Update(Player* player);
	//生成
	void ResPorn();
	//移動
	void Move();
	//攻撃範囲内
	void InArea(Player* player);
	//標的
	void Target(Player* player);
	//停止
	void Stop(Player* player);
	//当たり判定
	bool Collide(Player* player);
	//描画
	void Draw();
	//FormatString用
	void FormatDraw(int EnemyCount);
public:
	//getter setter
	const float& GetScale() { return EnemyScale; }
	const bool& GetAttackArea() { return InAttackArea; }
	void SetStop(bool Stop) { this->EnemyStop = Stop; }
	void SetEnemyTex(int tex) { this->texture = tex; }
	void SetEnemyStopTex(int tex) { this->stoptexture = tex; }
private:
	int texture = 0;
	int stoptexture = 0;
	//メンバ変数
	//座標
	float EnemyPosX = 0.0f;
	float EnemyPosY = 0.0f;
	//円運動のための変数
	float x = 0;
	float y = 0;
	float EnemyRadius = 0.0f;
	//0から360までの円周
	float EnemySpeed = 0.0f;
	//一周したかどうかの判定を取るための円周
	float EnemyRoundSpeed = 0.0f;
	float EnemyScale = 500.0f;
	float EnemyCircleX = 0.0f;
	float EnemyCircleY = 0.0f;
	float EnemyAdd = 0.0f;
	//リスポーン関係
	bool EnemyAlive = false;
	float EnemyTimer = 0;
	bool EnemyMove = false;
	bool EnemySet = false;
	int TargetLine = 0;
	//敵が止まっているか
	bool EnemyStop = false;
	int EnemyStopTimer = 0;
	
	//保存用変数
	float EnemySaveSpeed = 0.0f;
	//プレイヤーと敵の位置の距離
	float DistanceScale = 0.0f;
	float DistanceSpeed = 0.0f;
	//攻撃範囲
	bool InAttackArea = false;
};