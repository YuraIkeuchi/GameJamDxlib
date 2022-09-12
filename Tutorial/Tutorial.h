#pragma once
#include "DxLib.h"
#include "Share.h"
class Tutorial
{
public:
	//getter setter
	const int& GetTutorialNumber() { return TutorialNumber; }
	const int& GetTutorialTimer() { return TutorialTimer; }
	const bool& GetDoorEnd() { return doorEnd; }
	void SetTutorialTimer(int TutorialTimer) { this->TutorialTimer = TutorialTimer; }
	void SetTutorialNumber(int TutorialNumber) { this->TutorialNumber = TutorialNumber; }
	void SetTutorialClear(bool TutorialClear) { this->TutorialClear = TutorialClear; }

private:
	int TutorialGraph;
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

	int TextNumber;
	enum TutorialTextNumber {
		TutorialTex0,
		TutorialTex1,
		TutorialTex2,
		TutorialTex3,
		TutorialTex4,
		TutorialTex5,
		TutorialTex6,
		TutorialTex7,
		TutorialTex8,
		TutorialTex9,
		TutorialTex10,
		TutorialTex11,
		TutorialTex12,
		TutorialTex13,
	};

	float TutorialPosX;
	float AfterTutorialPosX;
	float frame;
	bool TextStart;
	bool TextEnd;
	int TutorialStopTimer;
	int TextCount;
	bool TextCheck;
	bool TutorialCheck;
	int TextInterVal;

	int doorTex;
	bool doorStart;
	bool doorEnd;


	float doorPosX1;
	float doorPosX2;
	float doorframe;
	int doorStopTimer;
public:
	Tutorial();
	void Initialize();
	bool Update(XINPUT_STATE input, XINPUT_STATE oldinput,int TutorialCount);
	void Draw();

};
