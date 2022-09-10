#include "Tutorial.h"
#include <DxLib.h>
#include "Easing.h"

Tutorial::Tutorial()
{
	
}

void Tutorial::Initialize()
{
	
}

bool Tutorial::Update(XINPUT_STATE input, XINPUT_STATE oldinput,int TutorialCount)
{
	//チュートリアルの進行状況を表している
	if (TutorialCount == 1 && !FirstTutorial) {
		TutorialNumber = 1;
		FirstTutorial = true;
	}
	else if (TutorialCount == 3 && !SecondTutorial) {
		TutorialNumber = 2;
		FirstTutorial = false;
	}

	else if (TutorialCount == 6 && !ThirdTutorial) {
		TutorialNumber = 3;
		ThirdTutorial = false;
	}

	if (TutorialNumber == 0 && TutorialTimer >= 300) {
		TutorialTimer--;
	}

	if (TutorialNumber == 1 && TutorialTimer >= 200) {
		TutorialTimer--;
	}

	if (TutorialNumber == 2 && TutorialTimer >= 100) {
		TutorialTimer--;
	}
	if (TutorialNumber == 3) {
		return true;
	}

	return false;
}

void Tutorial::Draw()
{
	DrawFormatString(0, 340, GetColor(0, 0, 0), "TutorialTimer %d", TutorialTimer);
}
