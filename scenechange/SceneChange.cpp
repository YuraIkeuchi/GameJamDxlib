#include "SceneChange.h"
#include "Easing.h"
SceneChange::SceneChange() {
	doorStart = false;
	doorEnd = false;
	Change = false;
	doorStopTimer = 0;
	doorframe = 0.0f;
	doorPosX1 = -320.0f;
	doorPosX2 = 1600.0f;
}

void SceneChange::Initialize() {
	doorTex = LoadGraph("Resources/tutorialdoor.png");
}

void SceneChange::Update() {

	if (doorStart) {
		if (doorframe < 1.0f) {
			doorframe += 0.025f;
		}
		else {
			doorframe = 1.0f;
			doorStopTimer++;

			if (doorStopTimer == 10) {
				Change = true;
				doorStart = false;
				doorEnd = true;
				doorframe = 0.0f;
				doorStopTimer = 0;
			}
		}
		doorPosX1 = Ease(In, Cubic, doorframe, doorPosX1, 320.0f);
		doorPosX2 = Ease(In, Cubic, doorframe, doorPosX2, 960.0f);
	}

	if (doorEnd) {
		if (doorframe < 1.0f) {
			doorframe += 0.025f;
		}
		else {
			doorEnd = false;
			doorframe = 1.0f;
		}
		doorPosX1 = Ease(In, Cubic, doorframe, doorPosX1, -320.0f);
		doorPosX2 = Ease(In, Cubic, doorframe, doorPosX2, 1600.0f);
	}
}

void SceneChange::Draw() {
	DrawRotaGraph(doorPosX1, 720 / 2, 1.0f, 0.0f, doorTex, TRUE);
	DrawRotaGraph(doorPosX2, 720 / 2, 1.0f, DX_PI_F, doorTex, TRUE);

	DrawFormatString(0, 460, GetColor(0, 0, 0), "doorframe %f", doorframe);
	DrawFormatString(0, 480, GetColor(0, 0, 0), "doorposX %f", doorPosX1);
	DrawFormatString(0, 500, GetColor(0, 0, 0), "doorpos2 %f", doorPosX2);
	DrawFormatString(0, 520, GetColor(0, 0, 0), "doorStart %d", doorStart);
	DrawFormatString(0, 540, GetColor(0, 0, 0), "doorEnd %d", doorEnd);
}