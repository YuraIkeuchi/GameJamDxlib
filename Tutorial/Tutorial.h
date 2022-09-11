#pragma once
#include "DxLib.h"

class Tutorial
{
public:
	//getter setter
	const int& GetTutorialNumber() { return TutorialNumber; }
	const int& GetTutorialTimer() { return TutorialTimer; }

	void SetTutorialTimer(int TutorialTimer) { this->TutorialTimer = TutorialTimer; }
	void SetTutorialNumber(int TutorialNumber) { this->TutorialNumber = TutorialNumber; }
	void SetTutorialClear(bool TutorialClear) { this->TutorialClear = TutorialClear; }

private:
	int TutorialNumber;
	int TutorialTimer;

	bool TutorialClear;
	enum NowTuTorial {
		Tutorial0,
		Tutorial1,
		Tutorial2,
		Tutorial3,
		Tutorial4,
		Tutorial5,
	};

	int FirstTutorialTex;
	int SecondTutorialTex;
	int ThirdTutorialTex;
public:
	Tutorial();
	void Initialize();
	bool Update(XINPUT_STATE input, XINPUT_STATE oldinput,int TutorialCount);
	void Draw();

};
