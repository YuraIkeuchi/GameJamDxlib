#pragma once
#include "DxLib.h"

class Tutorial
{
private:

public:
	Tutorial();
	void Initialize();
	bool Update(XINPUT_STATE input, XINPUT_STATE oldinput,int TutorialCount);
	void Draw();

};
