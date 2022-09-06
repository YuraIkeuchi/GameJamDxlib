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
	//�U���͈͓�
	void InArea(Player* player);
	//�W�I
	void Target(Player* player);
	//��~
	void Stop(Player* player);
	//�`��
	void Draw();
	//FormatString�p
	void FormatDraw(int EnemyCount);
public:
	//getter setter
	const float& GetScale() { return EnemyScale; }
	const bool& GetAttackArea() { return InAttackArea; }
	void SetStop(bool Stop) { this->EnemyStop = Stop; }
private:
	//�����o�ϐ�
	//���W
	float EnemyPosX = 0.0f;
	float EnemyPosY = 0.0f;
	//�~�^���̂��߂̕ϐ�
	float x = WIN_WIDTH / 2;
	float y = WIN_HEIGHT / 2;
	float EnemyRadius = 0.0f;
	//0����360�܂ł̉~��
	float EnemySpeed = 0.0f;
	//����������ǂ����̔������邽�߂̉~��
	float EnemyRoundSpeed = 0.0f;
	float EnemyScale = 500.0f;
	float EnemyCircleX = 0.0f;
	float EnemyCircleY = 0.0f;
	float EnemyAdd = 0.0f;
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
	//�v���C���[�ƓG�̈ʒu�̋���
	float DistanceScale = 0.0f;
	float DistanceSpeed = 0.0f;
	//�U���͈�
	bool InAttackArea = false;
};