#pragma once
#include "Share.h"
#include "DxLib.h"

class Title
{
private:
	int TitleTex;
	int TitleTex2;
	int TitleTex3;
	int TitleTex4;
	int TitleTex5;
	int TitleTex6;
	int curPosX;
	int curPosY;

	float scale1;
	float scale2;
	float scale3;

	float doorPosX1;
	float doorPosX2;

	bool moveFlag;

	float Speedframe;
	float AddSpeed;

	int timer;

	int alpha;

	bool settingFlag;
public:
	Title();
	void Initialize();
	bool Update(XINPUT_STATE input, XINPUT_STATE oldinput);
	void Draw();
};
