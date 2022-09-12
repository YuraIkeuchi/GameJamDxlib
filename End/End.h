#pragma once
#include "Share.h"
#include "DxLib.h"

//ランク分けのボーダーライン
#define S 200
#define A 120
#define B 70
#define C 20

class End
{
private:
	int EndTex;
	int EndTex6;
	int EndTex10[4];
	int EndTex11;

	float doorPosX1;
	float doorPosX2;

	bool moveFlag;

	float Speedframe;
	float AddSpeed;

	int timer;

	int alpha;

	bool endFlag;
	bool drawFlag;

	int endBgm;
	int endSe1;
public:
	End();
	void Initialize(int soundBolume);
	bool Update(XINPUT_STATE input, XINPUT_STATE oldinput);
	void Draw(int score);
};
