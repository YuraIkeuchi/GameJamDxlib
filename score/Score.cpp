#include "Score.h"

Score::Score() {
	scoreTex = LoadGraph("Resources/score.png");
	timeTex = LoadGraph("Resources/time.png");
}

Score::~Score() {

}

void Score::Initialize() {
	ScorePoint = 0;
	GameTimer = 100 * 60;
	MultPoint = 1;
	scorePosX = 900;
	scorePosY = 100;
	scorePosX2 = 1075;
	scorePosY2 = 180;
	knockCount = 0;
	alphaCount = 0;
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
		knockCount = player->GetKnockCount();
		alphaCount = 255;
		scorePosY2 = 180;
		player->SetKnockCount(0);
		player->SetInArea(false);
		player->SetInAreaStart(false);
	}

	if (alphaCount > 0)
	{
		scorePosY2 += 0.5f;
		alphaCount -= 5;
	}


	//ダメージを食らったときにスコアが減る
	if (player->GetStunTimer() == 100 && player->GetStun()) {

		ScorePoint -= 5;

	}

	//スコアは0以下にならない
	if (ScorePoint < 0) {
		ScorePoint = 0;
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
		knockCount = player->GetKnockCount();
		alphaCount = 255;
		scorePosY2 = 180;
		knockCount = player->GetKnockCount();
		player->SetKnockCount(0);
		player->SetInArea(false);
		player->SetInAreaStart(false);
	}

	if (alphaCount > 0)
	{
		scorePosY2 += 0.5f;
		alphaCount -= 5;
	}

	//ダメージを食らったときにスコアが減る
	if (player->GetStunTimer() == 100 && player->GetStun()) {

		ScorePoint -= 5;

	}

	//スコアは0以下にならない
	if (ScorePoint < 0) {
		ScorePoint = 0;
	}

	return false;
}

void Score::Draw() {
	SetFontSize(30);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alphaCount);
	AddFontResourceEx("Resources/HOKKORI.ttf", FR_PRIVATE, NULL);
	ChangeFont("HOKKORI");
	SetFontThickness(9);
	DrawFormatString(scorePosX2, scorePosY2, GetColor(0, 0, 0), "%d * %d", knockCount,MultPoint);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetFontSize(64);
	DrawRotaGraph(1050, 80, 0.65f, 0.0f, timeTex, TRUE);
	DrawFormatString(scorePosX - 30, scorePosY + 18 - 64, GetColor(0, 0, 0), "%10d", GameTimer / 60);
	//DrawFormatString(scorePosX, scorePosY + 64, GetColor(0, 0, 0), "frame %-10d", GameTimer);
	DrawRotaGraph(1050, 150, 0.65f, 0.0f, scoreTex, TRUE);
	DrawFormatString(scorePosX- 30, scorePosY+18, GetColor(0, 0, 0), "%10d", ScorePoint);
	//DrawFormatString(scorePosX - 30, scorePosY + 70, GetColor(0, 0, 0), "%-10d", GameTimer);
	SetFontSize(20);
}

void Score::FormatDraw() {
	//ChangeFont("ＭＳ 明朝");
	//SetFontSize(64);
	//DrawFormatString(scorePosX, scorePosY, GetColor(0, 0, 0), "スコア %-10d", ScorePoint);
	//SetFontSize(20);
	//DrawFormatString(0, 500, GetColor(0, 0, 0), "スコア %-10d", GameTimer);
}