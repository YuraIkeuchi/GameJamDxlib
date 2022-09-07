#include "Score.h"

Score::Score() {

}

Score::~Score() {

}

void Score::Initialize() {
	ScorePoint = 0;
	GameTimer = 5000;
	MultPoint = 0;
}

void Score::Update() {
	GameTimer--;
	//倒した敵　* 最終地点のスコア加算
	if (!player->GetAttackStart() && player->GetKnockCount() != 0) {
		if (player->GetScale() == 80.0f) {
			MultPoint = 10;
		}
		else if (player->GetScale() == 160.0f) {
			MultPoint = 5;
		}
		else if (player->GetScale() == 240.0f) {
			MultPoint = 2;
		}
		else{
			MultPoint = 1;
		}

		ScorePoint += player->GetKnockCount() * MultPoint;
		player->SetKnockCount(0);
	}
}

void Score::Draw() {

}

void Score::FormatDraw() {
	DrawFormatString(0, 100, GetColor(0, 0, 0), "GameTimer::%d",GameTimer);
	DrawFormatString(0, 120, GetColor(0, 0, 0), "Score::%d", ScorePoint);
}