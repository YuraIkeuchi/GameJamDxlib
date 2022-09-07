#include "Enemy.h"
#include "math.h"
#include "Collision.h"
#include "DxLib.h"
Enemy::Enemy() {
	EnemyTimer = rand() % 800 + 100;
}

Enemy::~Enemy() {

}

void Enemy::Initialize() {
	//���W
	EnemyPosX = 0.0f;
	EnemyPosY = 0.0f;
	//�~�^���̂��߂̕ϐ�
	x = 0.0f;
	y = 0.0f;
	EnemyRadius = 0.0f;
	//0����360�܂ł̉~��
	EnemySpeed = 0.0f;
	//����������ǂ����̔������邽�߂̉~��
	EnemyRoundSpeed = 0.0f;
	EnemyScale = 500.0f;
	EnemyCircleX = 0.0f;
	EnemyCircleY = 0.0f;
	EnemyAdd = 0.0f;
	//���X�|�[���֌W
	EnemyAlive = false;
	EnemyMove = false;
	EnemySet = false;
	TargetLine = 0;
	//�G���~�܂��Ă��邩
	EnemyStop = false;
	EnemyStopTimer = 0;

	//�ۑ��p�ϐ�
	EnemySaveSpeed = 0.0f;
	//�v���C���[�ƓG�̈ʒu�̋���
	DistanceScale = 0.0f;
	DistanceSpeed = 0.0f;
	//�U���͈�
	InAttackArea = false;
}

void Enemy::Update(Player* player) {

	ResPorn();
	Move();
	InArea(player);
	Stop(player);
	Collide(player);
	EnemyRadius = EnemySpeed * PI / 180.0f;
	EnemyCircleX = cosf(EnemyRadius) * EnemyScale;
	EnemyCircleY = sinf(EnemyRadius) * EnemyScale;
	EnemyPosX = EnemyCircleX + x;
	EnemyPosY = EnemyCircleY + y;
}

void Enemy::ResPorn() {
	//���X�|�[������
	if (!EnemyAlive) {
		EnemyTimer--;
		if (EnemyTimer == 0) {
			EnemyScale = rand() % 400 + 200;
			EnemySpeed = rand() % 360;
			EnemyAdd = 0.5f;
			TargetLine = rand() % 2;
			EnemyAlive = true;
			EnemyTimer = rand() % 800;
			EnemySet = true;
		}
	}

	//�_���̃��C���܂ōs��(���ݍł��O��)
	if (EnemySet) {
		if (TargetLine == 0) {
			if (EnemyScale >= 320.0f) {
				EnemyScale -= 5.0f;
			}
			else {
				EnemySet = false;
				EnemyMove = true;
				EnemyRoundSpeed = EnemySpeed;
				EnemySaveSpeed = EnemyRoundSpeed;
				EnemyScale = 320.0f;
			}
		}
		else if (TargetLine == 1) {
			if (EnemyScale >= 240.0f) {
				EnemyScale -= 5.0f;
			}
			else {
				EnemySet = false;
				EnemyMove = true;
				EnemyRoundSpeed = EnemySpeed;
				EnemySaveSpeed = EnemyRoundSpeed;
				EnemyScale = 240.0f;
			}
		}
	}
}

void Enemy::Move() {
	//�G�̈ړ�
	if (EnemyMove && !EnemyStop) {
		EnemySpeed += EnemyAdd;
		EnemyRoundSpeed += EnemyAdd;
	}

	//0����360�܂Ŕ͈͂��w�肷��
	if (EnemySpeed > 360.0f) {
		EnemySpeed = 0.0f;
	}

	if (EnemySpeed < 0.0f) {
		EnemySpeed = 360.0f;
	}

	if (EnemyMove) {
		if (EnemyRoundSpeed == EnemySaveSpeed + 360.0f) {
			if (EnemyScale > 81.0f) {
				EnemyScale -= 80.0f;
			}
			EnemyRoundSpeed = EnemyRoundSpeed - 360.0f;
			EnemySaveSpeed = EnemyRoundSpeed;
		}
	}
}

void Enemy::Stop(Player* player) {
	//�G�̃X�g�b�v
	if (player->GetStop()) {
		if (player->GetScale() == EnemyScale) {
			EnemyStop = true;
		}
	}

	if (EnemyStop) {
		EnemyStopTimer++;

		if (EnemyStopTimer == 200) {
			EnemyStop = false;
			EnemyStopTimer = 0;
		}
	}
}

void Enemy::InArea(Player* player) {
	//���������(��Βl�ɂ���)
	DistanceScale = player->GetScale() - EnemyScale;
	DistanceSpeed = player->GetSpeed() - EnemySpeed;

	DistanceSpeed = fabs(DistanceSpeed);

	if ((DistanceScale <= 80) && (DistanceSpeed <= 60) && (EnemyMove)) {
		InAttackArea = true;
	}
	else {
		InAttackArea = false;
	}

}
void Enemy::Target(Player* player) {

	//�������߂������ꍇ���̏ꏊ�Ƀv���C���[�ړ�
	if (EnemyAlive) {
		if (player->GetAttackCount() == 0) {
			if (player->GetAttack() && DistanceScale == 0.0f) {
				player->SetAttackStart(true);
				player->SetAfterScale(EnemyScale);
				player->SetAfterSpeed(EnemySpeed);
				player->SetFrame(0.0f);
			}
			else if (player->GetAttack() && DistanceScale == 80.0f) {
				player->SetAttackStart(true);
				player->SetAfterScale(EnemyScale);
				player->SetAfterSpeed(EnemySpeed);
				player->SetFrame(0.0f);
			}
		}
		else {
			if (player->GetAttackInterval() != 0 && DistanceScale == 0.0f) {

				player->SetAttackStart(true);
				player->SetAfterScale(EnemyScale);
				player->SetAfterSpeed(EnemySpeed);
				player->SetFrame(0.0f);
			}
			else if (player->GetAttackInterval() != 0 && DistanceScale == 80.0f) {
				player->SetAttackStart(true);
				player->SetAfterScale(EnemyScale);
				player->SetAfterSpeed(EnemySpeed);
				player->SetFrame(0.0f);
			}
		}
	}
}

bool Enemy::Collide(Player* player) {
	//�����蔻��
	float plaPosX = player->GetPositionX();
	float plaPosY = player->GetPositionY();
	if (Collision::CircleCollision(EnemyPosX, EnemyPosY, 15.0f, plaPosX, plaPosY, 15.0f)
		&& (EnemyMove) && (EnemyAlive) && (player->GetScale() == EnemyScale) && (player->GetAttackStart())) {
		EnemyAlive = false;
		EnemyMove = false;
		EnemyScale = 500.0f;
		player->SetAttackCount(player->GetAttackCount() + 1);
		player->SetAttackInterval(10);
		return true;
	}
	else {
		return false;
	}

	return true;
}

void Enemy::Draw() {
	//�~�܂��Ă��邩�ǂ����ŐF���ς��
	if (EnemyAlive) {
		if (!EnemyStop) {
			//DrawCircle(EnemyPosX, EnemyPosY, 20, GetColor(255, 255, 0), true);
			DrawBillboard3D(VGet(EnemyPosX, EnemyPosY, 0), 0.5f, 0.5f, 50.0f, 0.0f, texture, true);
		}
		else {
			DrawBillboard3D(VGet(EnemyPosX, EnemyPosY, 0), 0.5f, 0.5f, 50.0f, 0.0f, Stoptexture, true);
		}
		DrawBillboard3D(VGet(EnemyPosX, EnemyPosY, 0), 0.5f, 0.5f, 200.0f, 0.0f, Linktexture, true);
	}
}

void Enemy::FormatDraw(int EnemyCount) {
	//string�̕`��
	DrawFormatString(0, (20 * EnemyCount) + 0, GetColor(0, 0, 0), "EnemyScale[%d]:%f", EnemyCount, EnemyScale);
	//DrawFormatString(0, (20 * EnemyCount) + 100, GetColor(0, 0, 0), "DistanceSpeed[%d]:%f", EnemyCount, DistanceSpeed);
	//DrawFormatString(0, (20 * EnemyCount) + 200, GetColor(0, 0, 0), "DistanceScale[%d]:%f", EnemyCount, DistanceScale);
}