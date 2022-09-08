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
	//À•W
	EnemyPosX = 0.0f;
	EnemyPosY = 0.0f;
	//‰~‰^“®‚Ì‚½‚ß‚Ì•Ï”
	x = 0.0f;
	y = 0.0f;
	EnemyRadius = 0.0f;
	//0‚©‚ç360‚Ü‚Å‚Ì‰~Žü
	EnemySpeed = 0.0f;
	//ˆêŽü‚µ‚½‚©‚Ç‚¤‚©‚Ì”»’è‚ðŽæ‚é‚½‚ß‚Ì‰~Žü
	EnemyRoundSpeed = 0.0f;
	EnemyScale = 500.0f;
	EnemyCircleX = 0.0f;
	EnemyCircleY = 0.0f;
	EnemyAdd = 0.0f;
	//ƒŠƒXƒ|[ƒ“ŠÖŒW
	EnemyAlive = false;
	EnemyMove = false;
	EnemySet = false;
	TargetLine = 0;
	//“G‚ªŽ~‚Ü‚Á‚Ä‚¢‚é‚©
	EnemyStop = false;
	EnemyStopTimer = 0;

	//•Û‘¶—p•Ï”
	EnemySaveSpeed = 0.0f;
	//ƒvƒŒƒCƒ„[‚Æ“G‚ÌˆÊ’u‚Ì‹——£
	DistanceScale = 0.0f;
	DistanceSpeed = 0.0f;
	//UŒ‚”ÍˆÍ
	InAttackArea = false;

	int EffectTex = LoadGraph("Resources/attackEffect.png");

	effects = new AttackEffect();
	effects->SetTexture(EffectTex);
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

	effects->Update();
}

void Enemy::ResPorn() {
	//ƒŠƒXƒ|[ƒ“‚·‚é
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

	//‘_‚¢‚Ìƒ‰ƒCƒ“‚Ü‚Ås‚­(Œ»ÝÅ‚àŠO‘¤)
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
	//UŒ‚’†‚Í“G‚ªŽ~‚Ü‚é
	if (player->GetAttackStart()) {
		EnemyAdd = 0.0f;
	}
	else {
		EnemyAdd = 0.5f;
	}
	//“G‚ÌˆÚ“®
	if (EnemyMove && !EnemyStop) {
		EnemySpeed += EnemyAdd;
		EnemyRoundSpeed += EnemyAdd;
	}

	//0‚©‚ç360‚Ü‚Å”ÍˆÍ‚ðŽw’è‚·‚é
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
	//“G‚ÌƒXƒgƒbƒv
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
	//‹——£‚ðŽæ‚é(â‘Î’l‚É‚·‚é)
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
	//‹——£‚ª‹ß‚©‚Á‚½ê‡‚»‚ÌêŠ‚ÉƒvƒŒƒCƒ„[ˆÚ“®
	if (EnemyAlive) {
		//UŒ‚ˆê‰ñ–Ú(ƒŠƒ“ƒNŽn‚Ü‚é‚Æ‚«‚Í“¯‚¶ƒŒ[ƒ“‚Ì‚Ý)
		if (player->GetAttackCount() == 0) {
			if (player->GetAttack() && DistanceScale == 0.0f) {
				player->SetAttackStart(true);
				player->SetAfterScale(EnemyScale);
				player->SetAfterSpeed(EnemySpeed);
				player->SetFrame(0.0f);
				//player->SetLink(true);
			}
		}
		else if (player->GetAttackCount() >= 1) {
			//UŒ‚“ñ‰ñ–ÚˆÈ~(ƒŠƒ“ƒN’†‚Í“¯‚¶ƒŒ[ƒ“‚ð—Dæ‚µ‚ÄˆêŒÂ“à‘¤‚É‚àö‚ê‚é)
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
	//“–‚½‚è”»’è
	float plaPosX = player->GetPositionX();
	float plaPosY = player->GetPositionY();
	if (Collision::CircleCollision(EnemyPosX, EnemyPosY, 15.0f, plaPosX, plaPosY, 15.0f)
		&& (EnemyMove) && (EnemyAlive) && (player->GetScale() == EnemyScale) && (player->GetAttackStart())) {
		EnemyAlive = false;
		EnemyMove = false;
		effects->active(FLOAT3{ EnemyPosX ,EnemyPosY ,0.0f });
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
	//Ž~‚Ü‚Á‚Ä‚¢‚é‚©‚Ç‚¤‚©‚ÅF‚ª•Ï‚í‚é
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
	effects->Draw();
}

void Enemy::FormatDraw(int EnemyCount) {
	//string‚Ì•`‰æ
	//DrawFormatString(0, (20 * EnemyCount) + 0, GetColor(0, 0, 0), "EnemyScale[%d]:%f", EnemyCount, EnemyScale);
	//DrawFormatString(0, (20 * EnemyCount) + 80, GetColor(0, 0, 0), "DistanceSpeed[%d]:%f", EnemyCount, DistanceSpeed);
	//DrawFormatString(0, (20 * EnemyCount) + 280, GetColor(0, 0, 0), "DistanceScale[%d]:%f", EnemyCount, DistanceScale);
}