#pragma once
#include "Share.h"

class Player {
public:
	//�R���X�g���N�^
	Player();
	//�f�X�g���N�^
	~Player();

	//�X�V
	void Update(char keys[255], char oldkeys[255]);
	//�ړ�
	void Move(char keys[255], char oldkeys[255]);
	//�U��
	void AttackMove(char keys[255], char oldkeys[255]);
	//�`��
	void Draw();
	//FormatString�p
	void FormatDraw();
public:
	//getter setter�i���\�������Ⴄ�����\����Ȃ�)
	const float& GetScale() { return PlayerScale; }
	const float& GetSpeed() { return PlayerSpeed; }
	const bool& GetStop() { return Stop; }
	const bool& GetAttack() { return Attack; }

	void SetScale(float PlayerScale) { this->PlayerScale = PlayerScale; }
	void SetSpeed(float PlayerSpeed) { this->PlayerSpeed = PlayerSpeed; }
	void SetStop(bool Stop) { this->Stop = Stop; }
	void SetAttack(bool Attack) { this->Attack = Attack; }
private:
	//�����o�ϐ�
	//���W
	float playerPosX = WIN_WIDTH / 2;
	float playerPosY = WIN_HEIGHT / 2;
	//�~�^���̂��߂̕ϐ�
	float x = WIN_WIDTH / 2;
	float y = WIN_HEIGHT / 2;
	float PlayerRadius = 0.0f;
	float PlayerSpeed = 0.0f;
	float PlayerScale = 80.0f;// LaneNum�ƈꏏ�ɕς��邱��
	float PlayerCircleX = 0.0f;
	float PlayerCircleY = 0.0f;
	float Add = 1.0f;
	bool Attack = false;
	int AttackTimer = 0;
	//�G���~�߂邽�߂̕ϐ�
	bool Stop = false;
	int StopInterval = 5;
};