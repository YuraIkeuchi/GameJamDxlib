#pragma once
#include "Share.h"
#include "Player.h"
#include "AttackEffect.h"
#include "BreakEffect.h"

class Enemy {
public:
	//�R���X�g���N�^
	Enemy();
	//�f�X�g���N�^
	~Enemy();
	//������
	void Initialize();
	//�X�V
	void Update(Player* player);
	//����
	void ResPorn();
	//�ړ�
	void Move(Player* player);
	//�U���͈͓�
	void InArea(Player* player);
	//�W�I
	void Target(Player* player);
	//��~
	void Stop(Player* player);
	//�����蔻��(�G�l�~�[������)
	bool Collide(Player* player);
	//�����蔻��(�v���C���[���X�^������)
	bool PlayerCollide(Player* player);
	//���b�N�I�������蔻��(�v���C���[���X�^������)
	bool LockOnCollide(Player* player);
	//�`��
	void Draw();
	//FormatString�p
	void FormatDraw(int EnemyCount);
public:
	//getter setter
	const float& GetScale() { return EnemyScale; }
	const float& GetPositionX() { return EnemyPosX; }
	const float& GetPositionY() { return EnemyPosY; }
	const bool& GetAttackArea() { return InAttackArea; }
	void SetStop(bool Stop) { this->EnemyStop = Stop; }
	void SetEnemyTex(int tex) { this->texture = tex; }
	void SetEnemyStopTex(int tex) { this->Stoptexture = tex; }
	void SetLinkEnemyTex(int tex) { this->Linktexture = tex; }
	void SetTargetEnemyTex(int tex) { this->Targettexture = tex; }
private:
	int texture = 0;
	int Linktexture = 0;
	int Stoptexture = 0;
	int Targettexture = 0;
	//�����o�ϐ�
	//���W
	float EnemyPosX;
	float EnemyPosY;
	//�~�^���̂��߂̕ϐ�
	float x;
	float y;
	float EnemyRadius;
	//0����360�܂ł̉~��
	float EnemySpeed;
	//����������ǂ����̔������邽�߂̉~��
	float EnemyRoundSpeed;
	float EnemyScale;
	float EnemyCircleX;
	float EnemyCircleY;
	float EnemyAdd;
	float AddVelocity;
	//���X�|�[���֌W
	bool EnemyAlive;
	int EnemyTimer;
	bool EnemyMove;
	bool EnemySet;
	int TargetLine;
	//�G���~�܂��Ă��邩
	bool EnemyStop;
	int EnemyStopTimer;
	
	//�ۑ��p�ϐ�
	float EnemySaveSpeed;
	//�v���C���[�ƓG�̈ʒu�̋���
	float DistanceScale;
	float DistanceSpeed;
	//�U���͈�
	bool InAttackArea;

	int Dir;
	enum MoveDir {
		RIGHT,
		LEFT,
	};

	AttackEffect* effects = nullptr;
	BreakEffect* breakEffects = nullptr;
};