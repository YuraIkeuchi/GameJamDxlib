#pragma once
#include "Share.h"

class Player {
public:
	//�R���X�g���N�^
	Player();
	//�f�X�g���N�^
	~Player();

	//������
	void Initialize();
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
	float playerPosX;
	float playerPosY;
	//�~�^���̂��߂̕ϐ�
	float x;
	float y;
	float PlayerRadius;
	float PlayerSpeed;
	float PlayerScale;// LaneNum�ƈꏏ�ɕς��邱��
	float PlayerCircleX;
	float PlayerCircleY;
	float Add;
	bool Attack;
	int AttackTimer;
	//�G���~�߂邽�߂̕ϐ�
	bool Stop;
	int StopInterval;
};