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
	//�|�����G�@* �ŏI�n�_�̃X�R�A���Z
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
		//�����N���r�؂ꂽ�Ƃ��Ƀ|�C���g�̉��Z�Ȃǂ����Ă���
		ScorePoint += player->GetKnockCount() * MultPoint;
		player->SetKnockCount(0);
		player->SetInArea(false);
		player->SetInAreaStart(false);
	}
}

void Score::Draw() {

}

void Score::FormatDraw() {
	DrawFormatString(0, 100, GetColor(0, 0, 0), "GameTimer::%d",GameTimer);
	DrawFormatString(0, 120, GetColor(0, 0, 0), "Score::%d", ScorePoint);
}