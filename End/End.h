#pragma once
#include "Share.h"
#include "DxLib.h"

//�����N�����̃{�[�_�[���C��
#define S 100
#define A 80
#define B 50
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
public:
	End();
	void Initialize();
	bool Update(XINPUT_STATE input, XINPUT_STATE oldinput);
	void Draw(int score);
};