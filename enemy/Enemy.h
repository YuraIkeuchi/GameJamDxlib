#pragma once
#include "Share.h"
#include "Player.h"
class Enemy {
public:
	//コンストラクタ
	Enemy();
	//デストラクタ
	~Enemy();
	//初期化
	void Initialize();
	//更新
	void Update(Player* player);
	//生成
	void ResPorn();
	//移動
	void Move(Player* player);
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
	void SetEnemyStopTex(int tex) { this->Stoptexture = tex; }
	void SetLinkEnemyTex(int tex) { this->Linktexture = tex; }
private:
	int texture = 0;
	int Linktexture = 0;
	int Stoptexture = 0;
	//メンバ変数
	//座標
	float EnemyPosX;
	float EnemyPosY;
	//円運動のための変数
	float x;
	float y;
	float EnemyRadius;
	//0から360までの円周
	float EnemySpeed;
	//一周したかどうかの判定を取るための円周
	float EnemyRoundSpeed;
	float EnemyScale;
	float EnemyCircleX;
	float EnemyCircleY;
	float EnemyAdd;
	//リスポーン関係
	bool EnemyAlive;
	float EnemyTimer;
	bool EnemyMove;
	bool EnemySet;
	int TargetLine;
	//敵が止まっているか
	bool EnemyStop;
	int EnemyStopTimer;
	
	//保存用変数
	float EnemySaveSpeed;
	//プレイヤーと敵の位置の距離
	float DistanceScale;
	float DistanceSpeed;
	//攻撃範囲
	bool InAttackArea;
};