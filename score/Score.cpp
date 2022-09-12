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
	scorePosY = 100;
}

bool Score::Update(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput) {
	GameTimer--;
	if (GameTimer <= 0)
	{
		return true;
	}
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
		//リンクが途切れたときにポイントの加算などをしている
		ScorePoint += player->GetKnockCount() * MultPoint;
		player->SetKnockCount(0);
		player->SetInArea(false);
		player->SetInAreaStart(false);
	}

	return false;
}

bool Score::TutorialUpdate(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput) {
	//GameTimer--;
	if (GameTimer <= 0)
	{
		return true;
	}
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
		else {
			MultPoint = 1;
		}
		//リンクが途切れたときにポイントの加算などをしている
		ScorePoint += player->GetKnockCount() * MultPoint;
		player->SetKnockCount(0);
		player->SetInArea(false);
		player->SetInAreaStart(false);
	}

	return false;
}

void Score::Draw() {
	ChangeFont("ＭＳ 明朝");
	SetFontSize(64);
	DrawFormatString(scorePosX, scorePosY - 64, GetColor(0, 0, 0), "Timer %-10d", GameTimer / 60);
	//DrawFormatString(scorePosX, scorePosY + 64, GetColor(0, 0, 0), "frame %-10d", GameTimer);
	DrawFormatString(scorePosX, scorePosY, GetColor(0, 0, 0), "Score %-10d", ScorePoint);
	SetFontSize(20);
}

void Score::FormatDraw() {
	//ChangeFont("ＭＳ 明朝");
	//SetFontSize(64);
	//DrawFormatString(scorePosX, scorePosY, GetColor(0, 0, 0), "スコア %-10d", ScorePoint);
	//SetFontSize(20);
	//DrawFormatString(0, 500, GetColor(0, 0, 0), "スコア %-10d", GameTimer);
}