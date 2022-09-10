#include "Score.h"

Score::Score() {
}

Score::~Score() {

}

void Score::Initialize() {
	ScorePoint = 0;
	GameTimer = 100;
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
	//ì|ÇµÇΩìGÅ@* ç≈èIínì_ÇÃÉXÉRÉAâ¡éZ
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
		//ÉäÉìÉNÇ™ìrêÿÇÍÇΩÇ∆Ç´Ç…É|ÉCÉìÉgÇÃâ¡éZÇ»Ç«ÇÇµÇƒÇ¢ÇÈ
		ScorePoint += player->GetKnockCount() * MultPoint;
		player->SetKnockCount(0);
		player->SetInArea(false);
		player->SetInAreaStart(false);
	}

	return false;
}

void Score::Draw() {

}

void Score::FormatDraw() {
	//DrawFormatString(0, 100, GetColor(0, 0, 0), "GameTimer::%d",GameTimer);
	ChangeFont("ÇlÇr ñæí©");
	SetFontSize(64);
	DrawFormatString(scorePosX, scorePosY, GetColor(0, 0, 0), "ÉXÉRÉA %-10d", ScorePoint);
	SetFontSize(20);
}