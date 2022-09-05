#pragma once
#include "Share.h"
#include "Player.h"
class Enemy {
public:
	//�R���X�g���N�^
	Enemy();
	//�f�X�g���N�^
	~Enemy();

	//�X�V
	void Update(Player* player);
	//����
	void ResPorn();
	//�ړ�
	void Move();
	//��~
	void Stop(Player* player);
	//�`��
	void Draw();
	//FormatString�p
	void FormatDraw(int EnemyCount);
public:
	//getter setter
	const float& GetScale() { return Enemyscale; }
	void SetStop(bool Stop) { this->EnemyStop = Stop; }
private:
	//�����o�ϐ�
	//���W
	float EnemyPosX = 0.0f;
	float EnemyPosY = 0.0f;
	//�~�^���̂��߂̕ϐ�
	float x = WIN_WIDTH / 2;
	float y = WIN_HEIGHT / 2;
	float Enemyradius = 0.0f;
	float EnemySpeed = 0.0f;
	float Enemyscale = 500.0f;
	float EnemyCircleX = 0.0f;
	float EnemyCircleY = 0.0f;
	float Enemyadd = 0.0f;
	//���X�|�[���֌W
	float EnemyAlive = false;
	float EnemyTimer = 0;
	float EnemyMove = false;
	float EnemySet = false;
	float TargetLine = 0;
	//�G���~�܂��Ă��邩
	float EnemyStop = false;
	float EnemyStopTimer = 0;
	
	//�ۑ��p�ϐ�
	float EnemySaveSpeed = 0.0f;
};