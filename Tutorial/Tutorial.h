#pragma once
#include "DxLib.h"

class Tutorial
{
public:
	//getter setter
	const int& GetTutorialNumber() { return TutorialNumber; }
	const int& GetTutorialTimer() { return TutorialTimer; }

	void SetTutorialNumber(int TutorialNumber) { this->TutorialNumber = TutorialNumber; }

private:
	int TutorialNumber = 0;
	int TutorialTimer = 400;

	bool FirstTutorial = false;
	bool SecondTutorial = false;
	bool ThirdTutorial = false;
public:
	Tutorial();
	void Initialize();
	bool Update(XINPUT_STATE input, XINPUT_STATE oldinput,int TutorialCount);
	void Draw();

};
