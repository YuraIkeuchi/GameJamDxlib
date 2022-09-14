#pragma once
#include "Share.h"
#include "Player.h"
#include "AttackEffect.h"
#include "BreakEffect.h"
#include "TimeEffect.h"
#include "Particle.h"
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
	//�`���[�g���A���X�V
	void TutorialUpdate(Player* player);
	//����
	void ResPorn();
	//�����ꏊ�ݒu
	void Pattern(float Speed, int TargetLine, int Dir);
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
	void VanishEnemy();
	//�`��
	void Draw(Player* player);
	//FormatString�p
	void FormatDraw(int EnemyCount);
public:
	//getter setter
	const float& GetScale() { return EnemyScale; }
	const float& GetPositionX() { return EnemyPosX; }
	const float& GetPositionY() { return EnemyPosY; }
	const bool& GetAttackArea() { return InAttackArea; }
	const bool& GetDeathEnemy() { return DeathEnemy; }
	void SetStop(bool Stop) { this->EnemyStop = Stop; }
	void SetDir(int Dir) { this->Dir = Dir; }
	void SetEnemyTimer(int EnemyTimer) { this->EnemyTimer = EnemyTimer; }
	void SetTutorialMove(bool TutorialMove) { this->TutorialMove = TutorialMove; }
	void SetSpeed(float EnemySpeed) { this->EnemySpeed = EnemySpeed; }
	void SetDeathEnemy(bool DeathEnemy) { this->DeathEnemy = DeathEnemy; }
	void SetTargetLine(int TargetLine) { this->TargetLine = TargetLine; }
	void SetEnemyTex(int tex) { this->texture = tex; }
	void SetRespornTex(int tex) { this->Resporntexture = tex; }
	void SetTargetEnemyTex(int tex) { this->Targettexture = tex; }
	void SetStopTex(int tex) { this->Stoptexture = tex; }
private:
	int texture = 0;
	int Resporntexture = 0;
	int Targettexture = 0;
	int Stoptexture = 0;
	//�����o�ϐ�
	//���W
	float EnemyPosX;
	float EnemyPosY;
	//�傫��
	float size;
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
	//�`���[�g���A���̕ϐ�
	bool TutorialMove;
	//���X�|�[���֌W
	bool EnemyAlive;
	bool DeathEnemy;
	int EnemyTimer;
	bool EnemyMove;
	bool EnemySet;
	int TargetLine;
	//�G���~�܂��Ă��邩
	bool EnemyStop;
	int EnemyStopTimer;
	float StopPos;
	float SizeAngle;
	float SizeAngle2;
	//�ۑ��p�ϐ�
	float EnemySaveSpeed;
	//�v���C���[�ƓG�̈ʒu�̋���
	float DistanceScale;
	float DistanceSpeed;
	//�U���͈�
	bool InAttackArea;

	int Dir;

	//�~�̔��a�̈ړ��֌W
	float AfterScale;
	bool MoveLine;
	bool Vanish;
	float frame;
	//�Ə��Ɋւ���ϐ�
	bool TargetShrink;
	float Targetframe;
	float TargetSize;
	//�p�[�e�B�N���֌W
	int ParticleCount;
	float ParticlePosX;
	float ParticlePosY;
	enum MoveDir {
		RIGHT,
		LEFT,
	};

	enum PlayerDir {
		PLAYERRIGHT,
		PLAYERLEFT,
	};
	unique_ptr<TimeEffect> timeEffects;
	unique_ptr<AttackEffect> effects;
	unique_ptr<BreakEffect> breakEffects;
	unique_ptr<Particle> particle;
};