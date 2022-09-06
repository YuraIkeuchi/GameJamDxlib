#pragma once
#include "Share.h"

class Player {
public:
	//コンストラクタ
	Player();
	//デストラクタ
	~Player();

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
	const float& GetPositionX() { return playerPosX; }
	const float& GetPositionY() { return playerPosY; }

	void SetScale(float PlayerScale) { this->PlayerScale = PlayerScale; }
	void SetSpeed(float PlayerSpeed) { this->PlayerSpeed = PlayerSpeed; }
	void SetStop(bool Stop) { this->Stop = Stop; }
	void SetAttack(bool Attack) { this->Attack = Attack; }

	void SetPlayer(int _player) { this->texture = _player; }
private:
	//メンバ変数
	int texture = 0;
	//座標
	float playerPosX = WIN_WIDTH / 2;
	float playerPosY = WIN_HEIGHT / 2;
	//円運動のための変数
	float x = 0;
	float y = 0;
	float z = 0;
	float PlayerRadius = 0.0f;
	float PlayerSpeed = 0.0f;
	float PlayerScale = 160.0f;// LaneNumと一緒に変えること
	float PlayerCircleX = 0.0f;
	float PlayerCircleY = 0.0f;
	float Add = 1.0f;
	bool Attack = false;
	int AttackTimer = 0;
	//敵を止めるための変数
	bool Stop = false;
	int StopInterval = 5;
};