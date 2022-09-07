#include "Enemy.h"
#include "math.h"
#include "Collision.h"
#include "DxLib.h"
Enemy::Enemy() {
	EnemyTimer = rand() % 800 + 100;
}

Enemy::~Enemy() {

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
			/*if (EnemyScale > 81.0f) {
				EnemyScale -= 80.0f;
			}*/
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
	if (player->GetAttack() && DistanceScale == 0.0f) {
		player->SetAttackStart(true);
		player->SetAfterScale(EnemyScale);
		player->SetAfterSpeed(EnemySpeed);
	}
	else if (player->GetAttack() && DistanceScale == 80.0f) {
		player->SetAttackStart(true);
		player->SetAfterScale(EnemyScale);
		player->SetAfterSpeed(EnemySpeed);
	}
}

bool Enemy::Collide(Player* player) {
	float plaPosX = player->GetPositionX();
	float plaPosY = player->GetPositionY();
	if (Collision::CircleCollision(EnemyPosX, EnemyPosY, 5.0f, plaPosX, plaPosY, 5.0f)
		&& (EnemyMove) && (EnemyAlive)) {
		EnemyAlive = false;
		EnemyMove = false;
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
			DrawBillboard3D(VGet(EnemyPosX, EnemyPosY, 0), 0.5f, 0.5f, 50.0f, 0.0f, stoptexture, true);
		}
	}
}

void Enemy::FormatDraw(int EnemyCount) {
	//string�̕`��
	DrawFormatString(0, (20 * EnemyCount) + 0, GetColor(0, 0, 0), "Attack[%d]:%d", EnemyCount, EnemyAlive);
	//DrawFormatString(0, (20 * EnemyCount) + 100, GetColor(0, 0, 0), "DistanceSpeed[%d]:%f", EnemyCount, DistanceSpeed);
	//DrawFormatString(0, (20 * EnemyCount) + 200, GetColor(0, 0, 0), "DistanceScale[%d]:%f", EnemyCount, DistanceScale);
}