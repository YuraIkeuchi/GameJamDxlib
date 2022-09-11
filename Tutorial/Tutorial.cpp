#include "Tutorial.h"
#include <DxLib.h>
#include "Easing.h"

Tutorial::Tutorial()
{
	
}

void Tutorial::Initialize()
{
	TutorialNumber = Tutorial0;
	TutorialTimer = 600;
	TutorialClear = false;
}

bool Tutorial::Update(XINPUT_STATE input, XINPUT_STATE oldinput,int TutorialCount)
{
	//チュートリアルの進行状況を表している
	if (TutorialNumber == Tutorial0) {
		if ((input.LeftTrigger && !oldinput.LeftTrigger) || (input.RightTrigger && !oldinput.RightTrigger)) {
			TutorialNumber = Tutorial1;
		}
	}
	else if (TutorialNumber == Tutorial1) {
		if (TutorialTimer >= 500) {
			TutorialTimer--;
		}
		else {
			TutorialTimer = 500;
		}

		if (TutorialCount == 1) {
			TutorialNumber = Tutorial2;
		}
	}
	else if (TutorialNumber == Tutorial2) {
		if (TutorialTimer >= 400) {
			TutorialTimer--;
		}
		else {
			TutorialTimer = 400;
		}
		if (TutorialCount == 3) {
			TutorialNumber = Tutorial3;
		}
	}
	else if (TutorialNumber == Tutorial3) {
		if (TutorialTimer >= 300) {
			TutorialTimer--;
		}
		else {
			TutorialTimer = 300;
		}
		if (TutorialCount == 6) {
			TutorialNumber = Tutorial4;
		}
	}
	else if (TutorialNumber == Tutorial4) {
		if (TutorialTimer >= 200) {
			TutorialTimer--;
		}
		else {
			TutorialTimer = 200;
		}
		if (TutorialCount == 8 && TutorialClear) {
			TutorialNumber = Tutorial5;
		}
	}
	else {
		TutorialTimer--;
		if (TutorialTimer == 0) {
			return true;
		}
	}

	return false;
}

void Tutorial::Draw()
{
	DrawFormatString(0, 360, GetColor(0, 0, 0), "TutorialTimer %d", TutorialTimer);
	DrawFormatString(0, 380, GetColor(0, 0, 0), "TutorialNumber %d", TutorialNumber);
}
