#include "Score.h"

Score::Score() {
}

Score::~Score() {

}

void Score::Initialize() {
	ScorePoint = 0;
	GameTimer = 60 * 60;
	MultPoint = 0;
	scorePosX = 900;
	scorePosY = 600;
}

bool Score::Update(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput) {
	GameTimer--;
	if (GameTimer <= 0)
	{
		return true;
	}
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

	return false;
}

void Score::Draw() {
	ChangeFont("�l�r ����");
	SetFontSize(64);
	DrawFormatString(scorePosX, scorePosY - 64, GetColor(0, 0, 0), "�W�J�� %-10d", GameTimer / 60);
	DrawFormatString(scorePosX, scorePosY, GetColor(0, 0, 0), "�X�R�A %-10d", ScorePoint - 1);
	SetFontSize(20);
}

void Score::FormatDraw() {
	//DrawFormatString(0, 100, GetColor(0, 0, 0), "GameTimer::%d",GameTimer);
	//ChangeFont("�l�r ����");
	//SetFontSize(64);
	//DrawFormatString(scorePosX, scorePosY-64, GetColor(0, 0, 0), "�W�J�� %-10d", GameTimer / 60);
	//DrawFormatString(scorePosX, scorePosY, GetColor(0, 0, 0), "�X�R�A %-10d", ScorePoint - 1);
	//SetFontSize(20);
}