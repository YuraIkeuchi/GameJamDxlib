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
	//停止
	void Stop(Player* player);
	//描画
	void Draw();
	//FormatString用
	void FormatDraw(int EnemyCount);
public:
	//getter setter
	const float& GetScale() { return Enemyscale; }
	void SetStop(bool Stop) { this->EnemyStop = Stop; }
private:
	//メンバ変数
	//座標
	float EnemyPosX = 0.0f;
	float EnemyPosY = 0.0f;
	//円運動のための変数
	float x = WIN_WIDTH / 2;
	float y = WIN_HEIGHT / 2;
	float Enemyradius = 0.0f;
	float EnemySpeed = 0.0f;
	float Enemyscale = 500.0f;
	float EnemyCircleX = 0.0f;
	float EnemyCircleY = 0.0f;
	float Enemyadd = 0.0f;
	//リスポーン関係
	float EnemyAlive = false;
	float EnemyTimer = 0;
	float EnemyMove = false;
	float EnemySet = false;
	float TargetLine = 0;
	//敵が止まっているか
	float EnemyStop = false;
	float EnemyStopTimer = 0;
	
	//保存用変数
	float EnemySaveSpeed = 0.0f;
};