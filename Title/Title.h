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
	int TitleTex7;
	int TitleTex8;
	int TitleTex9[6];
	int tex9Num;
	int TitleTex10;
	int soundBolume = 50;

	int TitleSound1;
	int TitleSe1;
	int TitleSe2;

	int curPosX;
	int curPosY;

	int SelectPos[3];
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
	bool endFlag;
public:
	Title();
	void Initialize();
	bool Update(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput);
	void Draw();

	//ê›íËÇ≈í≤êﬂÇµÇΩâπó ÇéÊìæ
	int &GetVolume() { return soundBolume; }
};
