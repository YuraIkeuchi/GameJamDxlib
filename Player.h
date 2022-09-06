#pragma once
#include "Share.h"

class Player {
public:
	//コンストラクタ
	Player();
	//デストラクタ
	~Player();

	//初期化
	void Initialize();
	//更新
	void Update(char keys[255], char oldkeys[255]);
	//移動
	void Move(char keys[255], char oldkeys[255]);
	//攻撃
	void AttackMove(char keys[255], char oldkeys[255]);
	//描画
	void Draw();
	//FormatString用
	void FormatDraw();
public:
	//getter setter（結構増えちゃうかも申し訳ない)
	const float& GetScale() { return PlayerScale; }
	const float& GetSpeed() { return PlayerSpeed; }
	const bool& GetStop() { return Stop; }
	const bool& GetAttack() { return Attack; }

	void SetScale(float PlayerScale) { this->PlayerScale = PlayerScale; }
	void SetSpeed(float PlayerSpeed) { this->PlayerSpeed = PlayerSpeed; }
	void SetStop(bool Stop) { this->Stop = Stop; }
	void SetAttack(bool Attack) { this->Attack = Attack; }
private:
	//メンバ変数
	//座標
	float playerPosX;
	float playerPosY;
	//円運動のための変数
	float x;
	float y;
	float PlayerRadius;
	float PlayerSpeed;
	float PlayerScale;// LaneNumと一緒に変えること
	float PlayerCircleX;
	float PlayerCircleY;
	float Add;
	bool Attack;
	int AttackTimer;
	//敵を止めるための変数
	bool Stop;
	int StopInterval;
};