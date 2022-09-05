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
	//描画
	void Draw();
	//FormatString用
	void FormatDraw();
public:
	//getter setter
	const float& GetScale() { return Playerscale; }
	const bool& GetStop() { return Stop; }
	void SetStop(bool Stop) { this->Stop = Stop; }
private:
	//メンバ変数
	//座標
	float playerPosX = WIN_WIDTH / 2;
	float playerPosY = WIN_HEIGHT / 2;
	//円運動のための変数
	float x = WIN_WIDTH / 2;
	float y = WIN_HEIGHT / 2;
	float Playerradius = 0.0f;
	float PlayerSpeed = 0.0f;
	float Playerscale = 80.0f;// LaneNumと一緒に変えること
	float PlayerCircleX = 0.0f;
	float PlayerCircleY = 0.0f;
	float add = 1.0f;

	//敵を止めるための変数
	bool Stop = false;
	int StopInterval = 5;
};