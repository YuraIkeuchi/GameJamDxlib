#include "Enemy.h"
#include "math.h"
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
	EnemyRadius = EnemySpeed * PI / 180.0f;
	EnemyCircleX = cosf(EnemyRadius) * EnemyScale;
	EnemyCircleY = sinf(EnemyRadius) * EnemyScale;
	EnemyPosX = EnemyCircleX + x;
	EnemyPosY = EnemyCircleY + y;
}

void Enemy::ResPorn() {
	//リスポーンする
	if (!EnemyAlive) {
		EnemyTimer--;
		if (EnemyTimer == 0) {
			EnemyScale = rand() % 400 + 200;
			EnemySpeed = rand() % 360;
			EnemyAdd = 1;
			TargetLine = 4;
			EnemyAlive = true;
			EnemyTimer = rand() % 800;
			EnemySet = true;
		}
	}

	//狙いのラインまで行く(現在最も外側)
	if (EnemySet) {
		if (TargetLine == 0) {
			if (EnemyScale >= 80.0f) {
				EnemyScale -= 5.0f;
			}
			else {
				EnemySet = false;
				EnemyMove = true;
				EnemyRoundSpeed = EnemySpeed;
				EnemySaveSpeed = EnemyRoundSpeed;
				EnemyScale = 80.0f;
			}
		}
		else if (TargetLine == 1) {
			if (EnemyScale >= 120.0f) {
				EnemyScale -= 5.0f;
			}
			else {
				EnemySet = false;
				EnemyMove = true;
				EnemyScale = 120.0f;
			}
		}
		else if (TargetLine == 2) {
			if (EnemyScale >= 160.0f) {
				EnemyScale -= 5.0f;
			}
			else {
				EnemySet = false;
				EnemyMove = true;
				EnemyRoundSpeed = EnemySpeed;
				EnemySaveSpeed = EnemyRoundSpeed;
				EnemyScale = 160.0f;
			}
		}
		else if (TargetLine == 3) {
			if (EnemyScale >= 200.0f) {
				EnemyScale -= 5.0f;
			}
			else {
				EnemySet = false;
				EnemyMove = true;
				EnemyRoundSpeed = EnemySpeed;
				EnemySaveSpeed = EnemyRoundSpeed;
				EnemyScale = 200.0f;
			}
		}
		else if (TargetLine == 4) {
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
	//敵の移動
	if (EnemyMove && !EnemyStop) {
		EnemySpeed += EnemyAdd;
		EnemyRoundSpeed += EnemyAdd;
	}

	//0から360まで範囲を指定する
	if (EnemySpeed > 360.0f) {
		EnemySpeed = 0.0f;
	}

	if (EnemySpeed < 0.0f) {
		EnemySpeed = 360.0f;
	}

	if (EnemyMove) {
		if (EnemyRoundSpeed == EnemySaveSpeed + 360.0f) {
			if (EnemyScale > 81.0f) {
				EnemyScale -= 40.0f;
			}
			EnemyRoundSpeed = EnemyRoundSpeed - 360.0f;
			EnemySaveSpeed = EnemyRoundSpeed;
		}
	}
}

void Enemy::Stop(Player* player) {
	//敵のストップ
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
	//距離を取る(絶対値にする)
	DistanceScale = player->GetScale() - EnemyScale;
	DistanceSpeed = player->GetSpeed() - EnemySpeed;

	DistanceScale = fabs(DistanceScale);
	DistanceSpeed = fabs(DistanceSpeed);

	if ((DistanceScale <= 40) && (DistanceSpeed <= 60) && (EnemyMove)) {
		InAttackArea = true;
	}
	else {
		InAttackArea = false;
	}

}
void Enemy::Target(Player* player) {
	
	//距離が近かった場合その場所にプレイヤー移動
	if (player->GetAttack()) {
		player->SetScale(EnemyScale);
		player->SetSpeed(EnemySpeed);
		EnemyAlive = false;
		EnemyMove = false;
	}
}

void Enemy::Draw() {
	//止まっているかどうかで色が変わる
	if (EnemyAlive) {
		if (!EnemyStop) {
			DrawCircle(EnemyPosX, EnemyPosY, 10, GetColor(255, 255, 0), true);
		}
		else {
			DrawCircle(EnemyPosX, EnemyPosY, 10, GetColor(0, 255, 255), true);
		}
	}
}

void Enemy::FormatDraw(int EnemyCount) {
	//stringの描画
	DrawFormatString(0, (20 * EnemyCount) + 0, GetColor(0, 0, 0), "Attack[%d]:%d", EnemyCount, InAttackArea);
	DrawFormatString(0, (20 * EnemyCount) + 100, GetColor(0, 0, 0), "DistanceSpeed[%d]:%f", EnemyCount, DistanceSpeed);
	DrawFormatString(0, (20 * EnemyCount) + 200, GetColor(0, 0, 0), "DistanceScale[%d]:%f", EnemyCount, DistanceScale);
}