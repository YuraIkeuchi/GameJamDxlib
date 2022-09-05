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
	//�`��
	void Draw();
	//FormatString�p
	void FormatDraw();
public:
	//getter setter
	const float& GetScale() { return Playerscale; }
	const bool& GetStop() { return Stop; }
	void SetStop(bool Stop) { this->Stop = Stop; }
private:
	//�����o�ϐ�
	//���W
	float playerPosX = WIN_WIDTH / 2;
	float playerPosY = WIN_HEIGHT / 2;
	//�~�^���̂��߂̕ϐ�
	float x = WIN_WIDTH / 2;
	float y = WIN_HEIGHT / 2;
	float Playerradius = 0.0f;
	float PlayerSpeed = 0.0f;
	float Playerscale = 80.0f;// LaneNum�ƈꏏ�ɕς��邱��
	float PlayerCircleX = 0.0f;
	float PlayerCircleY = 0.0f;
	float add = 1.0f;

	//�G���~�߂邽�߂̕ϐ�
	bool Stop = false;
	int StopInterval = 5;
};