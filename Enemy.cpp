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
	Stop(player);
	
	Enemyradius = EnemySpeed * PI / 180.0f;
	EnemyCircleX = cosf(Enemyradius) * Enemyscale;
	EnemyCircleY = sinf(Enemyradius) * Enemyscale;
	EnemyPosX = EnemyCircleX + x;
	EnemyPosY = EnemyCircleY + y;
}

void Enemy::ResPorn() {
	//リスポーンする
	if (!EnemyAlive) {
		EnemyTimer--;
		if (EnemyTimer == 0) {
			Enemyscale = rand() % 400 + 200;
			EnemySpeed = rand() % 360;
			Enemyadd = 1;
			TargetLine = 4;
			EnemyAlive = true;
			EnemyTimer = rand() % 800;
			EnemySet = true;
		}
	}

	//狙いのラインまで行く(現在最も外側)
	if (EnemySet) {
		if (TargetLine == 0) {
			if (Enemyscale >= 80.0f) {
				Enemyscale -= 5.0f;
			}
			else {
				EnemySet = false;
				EnemyMove = true;
				EnemySaveSpeed = EnemySpeed;
				Enemyscale = 80.0f;
			}
		}
		else if (TargetLine == 1) {
			if (Enemyscale >= 120.0f) {
				Enemyscale -= 5.0f;
			}
			else {
				EnemySet = false;
				EnemyMove = true;
				Enemyscale = 120.0f;
			}
		}
		else if (TargetLine == 2) {
			if (Enemyscale >= 160.0f) {
				Enemyscale -= 5.0f;
			}
			else {
				EnemySet = false;
				EnemyMove = true;
				EnemySaveSpeed = EnemySpeed;
				Enemyscale = 160.0f;
			}
		}
		else if (TargetLine == 3) {
			if (Enemyscale >= 200.0f) {
				Enemyscale -= 5.0f;
			}
			else {
				EnemySet = false;
				EnemyMove = true;
				EnemySaveSpeed = EnemySpeed;
				Enemyscale = 200.0f;
			}
		}
		else if (TargetLine == 4) {
			if (Enemyscale >= 240.0f) {
				Enemyscale -= 5.0f;
			}
			else {
				EnemySet = false;
				EnemyMove = true;
				EnemySaveSpeed = EnemySpeed;
				Enemyscale = 240.0f;
			}
		}
	}
}

void Enemy::Move() {
	//敵の移動
	if (EnemyMove && !EnemyStop) {
		EnemySpeed += Enemyadd;
	}

	if (EnemyMove) {
		if (EnemySpeed == EnemySaveSpeed + 360.0f) {
			if (Enemyscale > 81.0f) {
				Enemyscale -= 40.0f;
			}
			EnemySpeed = EnemySpeed - 360.0f;
			EnemySaveSpeed = EnemySpeed;
		}
	}
}

void Enemy::Stop(Player* player) {
	//敵のストップ
	if (player->GetStop()) {
		if (player->GetScale() == Enemyscale) {
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

void Enemy::Draw() {
	//止まっているかどうかで色が変わる
	if (!EnemyStop) {
		DrawCircle(EnemyPosX, EnemyPosY, 10, GetColor(255, 255, 0), true);
	}
	else {
		DrawCircle(EnemyPosX, EnemyPosY, 10, GetColor(0, 255, 255), true);
	}
}

void Enemy::FormatDraw(int EnemyCount) {
	//stringの描画
	//DrawFormatString(0, (20 * EnemyCount) + 40, GetColor(0, 0, 0), "Save[%d]:%f", EnemyCount, EnemySaveSpeed);
	//DrawFormatString(0, (20 * EnemyCount) + 100, GetColor(0, 0, 0), "Speed[%d]:%f", EnemyCount, EnemySpeed);
	//DrawFormatString(0, (20 * EnemyCount) + 180, GetColor(0, 0, 0), "Timer[%d]:%d", EnemyCount, EnemyStopTimer);
}