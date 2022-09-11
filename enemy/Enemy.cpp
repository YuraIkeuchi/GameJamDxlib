#include "Enemy.h"
#include "math.h"
#include "Collision.h"
#include "DxLib.h"
Enemy::Enemy() {
}

Enemy::~Enemy() {

}

void Enemy::Initialize() {
	EnemyTimer = 100;
	//座標
	EnemyPosX = 0.0f;
	EnemyPosY = 0.0f;
	//円運動のための変数
	x = 0.0f;
	y = 0.0f;
	EnemyRadius = 0.0f;
	//0から360までの円周
	EnemySpeed = 0.0f;
	//一周したかどうかの判定を取るための円周
	EnemyRoundSpeed = 0.0f;
	EnemyScale = 500.0f;
	EnemyCircleX = 0.0f;
	EnemyCircleY = 0.0f;
	EnemyAdd = 0.0f;
	//リスポーン関係
	EnemyAlive = false;
	DeathEnemy = false;
	EnemyMove = false;
	EnemySet = false;
	TargetLine = 0;
	//敵が止まっているか
	EnemyStop = false;
	EnemyStopTimer = 0;
	Dir = RIGHT;
	//保存用変数
	EnemySaveSpeed = 0.0f;
	//プレイヤーと敵の位置の距離
	DistanceScale = 0.0f;
	DistanceSpeed = 0.0f;
	//攻撃範囲
	InAttackArea = false;

	int EffectTex = LoadGraph("Resources/attackEffect.png");
	int breakEffectTex = LoadGraph("breakEffect.png");
	int TimeEffectTex = LoadGraph("TimeEffect.png");

	effects = new AttackEffect();
	effects->SetTexture(EffectTex);
	breakEffects = new BreakEffect();
	breakEffects->SetTexture(breakEffectTex);
	timeEffects = new TimeEffect();
	timeEffects->SetTexture(TimeEffectTex);

}

void Enemy::Update(Player* player) {

	ResPorn();
	Move(player);
	InArea(player);
	Stop(player);
	Collide(player);
	PlayerCollide(player);
	//if (InAttackArea) {
	//	Target(player);
	//}

	EnemyRadius = EnemySpeed * PI / 180.0f;
	EnemyCircleX = cosf(EnemyRadius) * EnemyScale;
	EnemyCircleY = sinf(EnemyRadius) * EnemyScale;
	EnemyPosX = EnemyCircleX + x;
	EnemyPosY = EnemyCircleY + y;

	effects->Update();
	breakEffects->Update();
	timeEffects->Update();
}

void Enemy::TutorialInitialize() {
	EnemyTimer = 100;
	//座標
	EnemyPosX = 0.0f;
	EnemyPosY = 0.0f;
	//円運動のための変数
	x = 0.0f;
	y = 0.0f;
	EnemyRadius = 0.0f;
	//0から360までの円周
	EnemySpeed = 0.0f;
	//一周したかどうかの判定を取るための円周
	EnemyRoundSpeed = 0.0f;
	EnemyScale = 500.0f;
	EnemyCircleX = 0.0f;
	EnemyCircleY = 0.0f;
	EnemyAdd = 0.0f;
	//チュートリアルの変数
	TutorialMove = false;
	//リスポーン関係
	EnemyAlive = false;
	DeathEnemy = false;
	EnemyMove = false;
	EnemySet = false;
	TargetLine = 0;
	//敵が止まっているか
	EnemyStop = false;
	EnemyStopTimer = 0;
	Dir = RIGHT;
	//保存用変数
	EnemySaveSpeed = 0.0f;
	//プレイヤーと敵の位置の距離
	DistanceScale = 0.0f;
	DistanceSpeed = 0.0f;
	//攻撃範囲
	InAttackArea = false;

	int EffectTex = LoadGraph("Resources/attackEffect.png");
	int breakEffectTex = LoadGraph("breakEffect.png");
	int TimeEffectTex = LoadGraph("TimeEffect.png");
	effects = new AttackEffect();
	effects->SetTexture(EffectTex);
	breakEffects = new BreakEffect();
	breakEffects->SetTexture(breakEffectTex);
	timeEffects = new TimeEffect();
	timeEffects->SetTexture(TimeEffectTex);
}

void Enemy::TutorialUpdate(Player* player) {

	ResPorn();
	if (TutorialMove) {
		Move(player);
	}
	InArea(player);
	Stop(player);
	Collide(player);
	PlayerCollide(player);
	//if (InAttackArea) {
	//	Target(player);
	//}

	EnemyRadius = EnemySpeed * PI / 180.0f;
	EnemyCircleX = cosf(EnemyRadius) * EnemyScale;
	EnemyCircleY = sinf(EnemyRadius) * EnemyScale;
	EnemyPosX = EnemyCircleX + x;
	EnemyPosY = EnemyCircleY + y;

	effects->Update();
	breakEffects->Update();
	timeEffects->Update();
}
void Enemy::ResPorn() {
	//リスポーンする
	if (!EnemyAlive) {
		EnemyTimer--;
		if (EnemyTimer == 0) {
			if (Dir == RIGHT) {
				EnemyAdd = 0.5f;
			}
			else {
				EnemyAdd = -0.5f;
			}
			EnemyAlive = true;
			EnemyTimer = -1;//2回目からはリスポーンしない
			EnemySet = true;
		}
	}

	//狙いのラインまで行く(現在最も外側)
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
	}
}

void Enemy::Move(Player* player) {
	//攻撃中は敵が止まる
	if (player->GetAttackStart()) {
		EnemyAdd = 0.0f;
	}
	else {
		if (Dir == RIGHT) {
			EnemyAdd = 0.5f;
		}
		else {
			EnemyAdd = -0.5f;
		}
	}

	//どのサークルにいるかで変更するものがある
	if (EnemyScale == 80.0f) {
		if (Dir == RIGHT) {
			AddVelocity = 0.75f;
		}
		else {
			AddVelocity = -0.75f;
		}
	}
	else if (EnemyScale == 160.0f) {
		if (Dir == RIGHT) {
			AddVelocity = 0.5f;
		}
		else {
			AddVelocity = -0.5f;
		}
	}
	else if (EnemyScale == 240.0f) {
		if (Dir == RIGHT) {
			AddVelocity = 0.25f;
		}
		else {
			AddVelocity = -0.25f;
		}
	}
	else if (EnemyScale == 320.0f) {
		if (Dir == RIGHT) {
			AddVelocity = 0.0f;
		}
		else {
			AddVelocity = 0.0f;
		}
	}

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
		if (Dir == RIGHT) {
			if (EnemyRoundSpeed == EnemySaveSpeed + 360.0f) {
				if (EnemyScale > 81.0f) {
					EnemyScale -= 80.0f;
				}
				EnemyRoundSpeed = EnemyRoundSpeed - 360.0f;
				EnemySaveSpeed = EnemyRoundSpeed;
			}
		}
		else {
			if (EnemyRoundSpeed == EnemySaveSpeed - 360.0f) {
				if (EnemyScale > 81.0f) {
					EnemyScale -= 80.0f;
				}
				EnemyRoundSpeed = EnemyRoundSpeed + 360.0f;
				EnemySaveSpeed = EnemyRoundSpeed;
			}
		}
	}
}

void Enemy::Stop(Player* player) {
	//敵のストップ
	if (player->GetStop()) {
		if (player->GetScale() == EnemyScale) {
			EnemyStop = true;
			timeEffects->active(VGet(EnemyPosX, EnemyPosY, 0));
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

	DistanceSpeed = fabs(DistanceSpeed);
	//一回目の攻撃のときと二回目のときの判定の広さが変わる
	if (player->GetKnockCount() == 0) {
		//一番中心の円とそれ以外の円で処理が別
		if (player->GetScale() != 80.0f) {
			if ((DistanceScale <= 80) && LockOnCollide(player) && (EnemyMove)) {
				InAttackArea = true;
			}
			else {
				InAttackArea = false;
			}
		}
		else {
			if ((DistanceScale >= -80) && LockOnCollide(player) && (EnemyMove)) {
				InAttackArea = true;
			}
			else {
				InAttackArea = false;
			}
		}
	}
	else {
		if (player->GetScale() != 80.0f) {
			if ((DistanceScale <= 80) && (DistanceSpeed <= 60) && (EnemyMove)) {
				InAttackArea = true;
			}
			else {
				InAttackArea = false;
			}
		}
		else {
			if ((DistanceScale >= -80) && (DistanceSpeed <= 60) && (EnemyMove)) {
				InAttackArea = true;
			}
			else {
				InAttackArea = false;
			}
		}
	}
}

void Enemy::Target(Player* player) {
	//距離が近かった場合その場所にプレイヤー移動
	if (EnemyAlive) {
		//一番中心の円とそれ以外の円で処理が別
		if (player->GetScale() != 80.0f) {
			//攻撃一回目(リンク始まるときは同じレーンのみ)
			if (player->GetKnockCount() == 0) {
				if (player->GetAttack() && DistanceScale == 0.0f) {
					//0度と360度の境目の差をなくす
					if (player->GetSpeed() <= 30.0f && EnemySpeed >= 330.0f) {
						player->SetAround(true);
						player->SetSpeed(player->GetSpeed() + 360.0f);
					}
					else if (EnemySpeed <= 30.0f && player->GetSpeed() >= 330.0f) {
						player->SetAround(true);
						player->SetSpeed(player->GetSpeed() - 360.0f);
					}
					player->SetAttackStart(true);
					player->SetAfterScale(EnemyScale);
					player->SetAfterSpeed(EnemySpeed);
					player->SetFrame(0.0f);
					
					//player->SetLink(true);
				}
			}
			else if (player->GetKnockCount() >= 1) {
				//攻撃二回目以降(リンク中は同じレーンを優先して一個内側にも潜れる)
				if (player->GetAttackInterval() != 0 && DistanceScale == 0.0f) {
					player->SetAttackStart(true);
					player->SetAfterScale(EnemyScale);
					player->SetAfterSpeed(EnemySpeed);
					player->SetFrame(0.0f);
					////0度と360度の境目の差をなくす
					//if (player->GetSpeed() <= 30.0f && EnemySpeed >= 330.0f) {
					//	player->SetAround(true);
					//	player->SetSpeed(player->GetSpeed() + 360.0f);
					//}
					//else if (EnemySpeed <= 30.0f && player->GetSpeed() >= 330.0f) {
					//	player->SetAround(true);
					//	player->SetSpeed(player->GetSpeed() - 360.0f);
					//}
					//player->SetLink(true);
				}
				else if (player->GetAttackInterval() != 0 && DistanceScale == 80.0f) {
					player->SetAttackStart(true);
					player->SetAfterScale(EnemyScale);
					player->SetAfterSpeed(EnemySpeed);
					player->SetFrame(0.0f);
					player->SetInAreaStart(true);
					////0度と360度の境目の差をなくす
					//if (player->GetSpeed() <= 30.0f && EnemySpeed >= 330.0f) {
					//	player->SetAround(true);
					//	player->SetSpeed(player->GetSpeed() + 360.0f);
					//}
					//else if (EnemySpeed <= 30.0f && player->GetSpeed() >= 330.0f) {
					//	player->SetAround(true);
					//	player->SetSpeed(player->GetSpeed() - 360.0f);
					//}
					//player->SetLink(true);
				}
				//一回も内側にいかなかった場合外側にも行ける
				else if (player->GetAttackInterval() != 0 && DistanceScale == -80.0f) {
					if (!player->GetInArea()) {
						player->SetAttackStart(true);
						player->SetAfterScale(EnemyScale);
						player->SetAfterSpeed(EnemySpeed);
						player->SetFrame(0.0f);
						////0度と360度の境目の差をなくす
						//if (player->GetSpeed() <= 30.0f && EnemySpeed >= 330.0f) {
						//	player->SetAround(true);
						//	player->SetSpeed(player->GetSpeed() + 360.0f);
						//}
						//else if (EnemySpeed <= 30.0f && player->GetSpeed() >= 330.0f) {
						//	player->SetAround(true);
						//	player->SetSpeed(player->GetSpeed() - 360.0f);
						//}
					}
				}
			}
		}
		else {
			//攻撃一回目(リンク始まるときは同じレーンのみ)
			if (player->GetKnockCount() == 0) {
				if (player->GetAttack() && DistanceScale == 0.0f) {
					player->SetAttackStart(true);
					player->SetAfterScale(EnemyScale);
					player->SetAfterSpeed(EnemySpeed);
					player->SetFrame(0.0f);
					//0度と360度の境目の差をなくす
					if (player->GetSpeed() <= 30.0f && EnemySpeed >= 330.0f) {
						player->SetAround(true);
						player->SetSpeed(player->GetSpeed() + 360.0f);
					}
					else if (EnemySpeed <= 30.0f && player->GetSpeed() >= 330.0f) {
						player->SetAround(true);
						player->SetSpeed(player->GetSpeed() - 360.0f);
					}
					//player->SetLink(true);
				}
			}
			else if (player->GetKnockCount() >= 1) {
				//攻撃二回目以降(リンク中は同じレーンを優先して一個内側にも潜れる)
				if (player->GetAttackInterval() != 0 && DistanceScale == 0.0f) {
					player->SetAttackStart(true);
					player->SetAfterScale(EnemyScale);
					player->SetAfterSpeed(EnemySpeed);
					player->SetFrame(0.0f);
					////0度と360度の境目の差をなくす
					//if (player->GetSpeed() <= 30.0f && EnemySpeed >= 330.0f) {
					//	player->SetAround(true);
					//	player->SetSpeed(player->GetSpeed() + 360.0f);
					//}
					//else if (EnemySpeed <= 30.0f && player->GetSpeed() >= 330.0f) {
					//	player->SetAround(true);
					//	player->SetSpeed(player->GetSpeed() - 360.0f);
					//}
					//player->SetLink(true);
				}
				else if (player->GetAttackInterval() != 0 && DistanceScale == -80.0f) {
					player->SetAttackStart(true);
					player->SetAfterScale(EnemyScale);
					player->SetAfterSpeed(EnemySpeed);
					player->SetFrame(0.0f);
					////0度と360度の境目の差をなくす
					//if (player->GetSpeed() <= 30.0f && EnemySpeed >= 330.0f) {
					//	player->SetAround(true);
					//	player->SetSpeed(player->GetSpeed() + 360.0f);
					//}
					//else if (EnemySpeed <= 30.0f && player->GetSpeed() >= 330.0f) {
					//	player->SetAround(true);
					//	player->SetSpeed(player->GetSpeed() - 360.0f);
					//}
					//player->SetLink(true);
				}
				else {
					//player->SetLink(false);
				}
			}
		}
	}
}



bool Enemy::Collide(Player* player) {
	//当たり判定
	float plaPosX = player->GetPositionX();
	float plaPosY = player->GetPositionY();
	if (Collision::CircleCollision(EnemyPosX, EnemyPosY, 15.0f, plaPosX, plaPosY, 15.0f)
		&& (EnemyMove) && (EnemyAlive) && (player->GetScale() == EnemyScale) && (player->GetAttackStart())) {
		EnemyAlive = false;
		EnemyMove = false;
		effects->active(FLOAT3{ EnemyPosX ,EnemyPosY ,0.0f });
		breakEffects->active(FLOAT3{ EnemyPosX ,EnemyPosY ,0.0f });
		EnemyScale = 500.0f;
		DeathEnemy = true;
		player->SetKnockCount(player->GetKnockCount() + 1);
		player->SetAttackInterval(10);
		/*player->SetAttackStart(false);
		player->SetFrame(0.0f);*/
		player->SetAround(false);
		if (player->GetInAreaStart()) {
			player->SetInArea(true);
		}
		return true;
	}
	else {
		return false;
	}

	return true;
}


bool Enemy::PlayerCollide(Player* player) {
	//当たり判定
	float plaPosX = player->GetPositionX();
	float plaPosY = player->GetPositionY();
	if (Collision::CircleCollision(EnemyPosX, EnemyPosY, 10.0f, plaPosX, plaPosY, 10.0f)
		&& (EnemyMove) && (EnemyAlive) && (player->GetScale() == EnemyScale)
		&& (player->GetKnockCount() == 0) && (!player->GetInvisible())) {
		player->SetStun(true);
		return true;
	}
	else {
		return false;
	}

	return true;
}

bool Enemy::LockOnCollide(Player* player) {
	//当たり判定
	float AttackPosX = player->GetAttackAreaX();
	float AttackPosY = player->GetAttackAreaY();
	if (Collision::CircleCollision(EnemyPosX, EnemyPosY, 30.0f, AttackPosX, AttackPosY, 30.0f)
		&& (EnemyMove) && (EnemyAlive)) {
		return true;
	}
	else {
		return false;
	}

	return true;
}

void Enemy::Draw() {
	//止まっているかどうかで色が変わる
//止まっているかどうかで色が変わる
	if (EnemyAlive) {
		DrawBillboard3D(VGet(EnemyPosX, EnemyPosY, 0), 0.5f, 0.5f, 50.0f, 0.0f, texture, true);
		if (InAttackArea) {
			DrawBillboard3D(VGet(EnemyPosX, EnemyPosY, 0), 0.5f, 0.5f, 50.0f, 0.0f, Targettexture, true);
		}
	}
	effects->Draw();
	breakEffects->Draw();
	//timeEffects->Draw();
}

void Enemy::FormatDraw(int EnemyCount) {
	//stringの描画
	//DrawFormatString(0, (20 * EnemyCount) + 0, GetColor(0, 0, 0), "EnemyScale[%d]:%f", EnemyCount, EnemyScale);
	//DrawFormatString(0, (20 * EnemyCount) + 120, GetColor(0, 0, 0), "Timer[%d]:%d", EnemyCount, EnemyTimer);
	DrawFormatString(0, (20 * EnemyCount) + 200, GetColor(0, 0, 0), "DistanceSpeed[%d]:%f", EnemyCount, EnemySpeed);
}