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
	//ç¿ïW
	EnemyPosX = 0.0f;
	EnemyPosY = 0.0f;
	//â~â^ìÆÇÃÇΩÇﬂÇÃïœêî
	x = 0.0f;
	y = 0.0f;
	EnemyRadius = 0.0f;
	//0Ç©ÇÁ360Ç‹Ç≈ÇÃâ~é¸
	EnemySpeed = 0.0f;
	//àÍé¸ÇµÇΩÇ©Ç«Ç§Ç©ÇÃîªíËÇéÊÇÈÇΩÇﬂÇÃâ~é¸
	EnemyRoundSpeed = 0.0f;
	EnemyScale = 500.0f;
	EnemyCircleX = 0.0f;
	EnemyCircleY = 0.0f;
	EnemyAdd = 0.0f;
	//ÉäÉXÉ|Å[Éìä÷åW
	EnemyAlive = false;
	EnemyMove = false;
	EnemySet = false;
	TargetLine = 0;
	//ìGÇ™é~Ç‹Ç¡ÇƒÇ¢ÇÈÇ©
	EnemyStop = false;
	EnemyStopTimer = 0;

	//ï€ë∂ópïœêî
	EnemySaveSpeed = 0.0f;
	//ÉvÉåÉCÉÑÅ[Ç∆ìGÇÃà íuÇÃãóó£
	DistanceScale = 0.0f;
	DistanceSpeed = 0.0f;
	//çUåÇîÕàÕ
	InAttackArea = false;
}

void Enemy::Update(Player* player) {

	ResPorn();
	Move(player);
	InArea(player);
	Stop(player);
	Collide(player);
	if (InAttackArea) {
		Target(player);
	}
	EnemyRadius = EnemySpeed * PI / 180.0f;
	EnemyCircleX = cosf(EnemyRadius) * EnemyScale;
	EnemyCircleY = sinf(EnemyRadius) * EnemyScale;
	EnemyPosX = EnemyCircleX + x;
	EnemyPosY = EnemyCircleY + y;
}

void Enemy::ResPorn() {
	//ÉäÉXÉ|Å[ÉìÇ∑ÇÈ
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

	//ë_Ç¢ÇÃÉâÉCÉìÇ‹Ç≈çsÇ≠(åªç›ç≈Ç‡äOë§)
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

void Enemy::Move(Player* player) {
	//çUåÇíÜÇÕìGÇ™é~Ç‹ÇÈ
	if (player->GetAttackStart()) {
		EnemyAdd = 0.0f;
	}
	else {
		EnemyAdd = 0.5f;
	}
	//ìGÇÃà⁄ìÆ
	if (EnemyMove && !EnemyStop) {
		EnemySpeed += EnemyAdd;
		EnemyRoundSpeed += EnemyAdd;
	}

	//0Ç©ÇÁ360Ç‹Ç≈îÕàÕÇéwíËÇ∑ÇÈ
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
	//ìGÇÃÉXÉgÉbÉv
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
	//ãóó£ÇéÊÇÈ(ê‚ëŒílÇ…Ç∑ÇÈ)
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
	//ãóó£Ç™ãﬂÇ©Ç¡ÇΩèÍçáÇªÇÃèÍèäÇ…ÉvÉåÉCÉÑÅ[à⁄ìÆ
	if (EnemyAlive) {
		//çUåÇàÍâÒñ⁄(ÉäÉìÉNénÇ‹ÇÈÇ∆Ç´ÇÕìØÇ∂ÉåÅ[ÉìÇÃÇ›)
		if (player->GetAttackCount() == 0) {
			if (player->GetAttack() && DistanceScale == 0.0f) {
				player->SetAttackStart(true);
				player->SetAfterScale(EnemyScale);
				player->SetAfterSpeed(EnemySpeed);
				player->SetFrame(0.0f);
				//player->SetLink(true);
			}
		}
		else if(player->GetAttackCount() >= 1) {
			//çUåÇìÒâÒñ⁄à»ç~(ÉäÉìÉNíÜÇÕìØÇ∂ÉåÅ[ÉìÇóDêÊÇµÇƒàÍå¬ì‡ë§Ç…Ç‡êˆÇÍÇÈ)
			if (player->GetAttackInterval() != 0 && DistanceScale == 0.0f) {
				player->SetAttackStart(true);
				player->SetAfterScale(EnemyScale);
				player->SetAfterSpeed(EnemySpeed);
				player->SetFrame(0.0f);
				//player->SetLink(true);
			}
			else if (player->GetAttackInterval() != 0 && DistanceScale == 80.0f) {
				player->SetAttackStart(true);
				player->SetAfterScale(EnemyScale);
				player->SetAfterSpeed(EnemySpeed);
				player->SetFrame(0.0f);
				//player->SetLink(true);
			}
			else {
				//player->SetLink(false);
			}
		}
	}
}

bool Enemy::Collide(Player* player) {
	//ìñÇΩÇËîªíË
	float plaPosX = player->GetPositionX();
	float plaPosY = player->GetPositionY();
	if (Collision::CircleCollision(EnemyPosX, EnemyPosY, 15.0f, plaPosX, plaPosY, 15.0f)
		&& (EnemyMove) && (EnemyAlive) && (player->GetScale() == EnemyScale) && (player->GetAttackStart())) {
		EnemyAlive = false;
		EnemyMove = false;
		EnemyScale = 500.0f;
		player->SetKnockCount(player->GetKnockCount() + 1);
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
	//é~Ç‹Ç¡ÇƒÇ¢ÇÈÇ©Ç«Ç§Ç©Ç≈êFÇ™ïœÇÌÇÈ
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
	//stringÇÃï`âÊ
	//DrawFormatString(0, (20 * EnemyCount) + 0, GetColor(0, 0, 0), "EnemyScale[%d]:%f", EnemyCount, EnemyScale);
	//DrawFormatString(0, (20 * EnemyCount) + 80, GetColor(0, 0, 0), "DistanceSpeed[%d]:%f", EnemyCount, DistanceSpeed);
	//DrawFormatString(0, (20 * EnemyCount) + 280, GetColor(0, 0, 0), "DistanceScale[%d]:%f", EnemyCount, DistanceScale);
}