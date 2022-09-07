#include "Score.h"

Score::Score() {

}

Score::~Score() {

}

void Score::Initialize() {
	ScorePoint = 0;
	GameTimer = 1500;
}

void Score::Update() {
	GameTimer--;
}

void Score::Draw() {

}

void Score::FormatDraw() {
	DrawFormatString(0, 80, GetColor(0, 0, 0), "GameTimer::%d",GameTimer);
}