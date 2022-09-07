#pragma once
#include "Share.h"
#include "DxLib.h"
class Player {
public:
	//コンストラクタ
	Player();
	//デストラクタ
	~Player();

	//初期化
	void Initialize();
	//更新
	void Update(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput);
	//移動
	void Move(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput);
	//攻撃
	void AttackMove(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput);
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
	const bool& GetAttackStart() { return AttackStart; }
	const float& GetAttackCount() { return AttackCount; }
	const int& GetAttackInterval() { return AttackInterval; }
	const float& GetFrame() { return frame; }
	const float& GetPositionX() { return playerPosX; }
	const float& GetPositionY() { return playerPosY; }

	void SetAfterScale(float AfterScale) { this->AfterScale = AfterScale; }
	void SetAfterSpeed(float AfterSpeed) { this->AfterSpeed = AfterSpeed; }
	void SetStop(bool Stop) { this->Stop = Stop; }
	void SetAttack(bool Attack) { this->Attack = Attack; }
	void SetAttackStart(bool AttackStart) { this->AttackStart = AttackStart; }
	void SetAttackCount(int AttackCount) { this->AttackCount = AttackCount; }
	void SetAttackInterval(int AttackInterval) { this->AttackInterval = AttackInterval; }
	void SetFrame(float frame) { this->frame = frame; }
	void SetPlayer(int _player) { this->texture = _player; }

private:
	//メンバ変数
	int texture = 0;
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
	//攻撃関係
	bool Attack;
	bool AttackStart;
	float AfterScale;
	float AfterSpeed;
	float frame;
	int AttackTimer;
	//二回目以降
	int AttackCount;
	int AttackInterval;
	//敵を止めるための変数
	bool Stop;
	int StopInterval;
	//移動関係
	float AddSpeed;
	float Speedframe;
	bool ChangeDir;
	int Dir;
	enum MoveDir {
		RIGHT,
		LEFT,
	};
};