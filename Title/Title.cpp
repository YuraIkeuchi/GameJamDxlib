#include "Title.h"
#include <DxLib.h>
#include "Easing.h"

Title::Title()
{
	TitleTex = LoadGraph("Resources/title1.png");
	TitleTex2 = LoadGraph("Resources/title2.png");
	TitleTex3 = LoadGraph("Resources/title3.png");
	TitleTex4 = LoadGraph("Resources/title4.png");
	TitleTex5 = LoadGraph("Resources/title5.png");
	TitleTex6 = LoadGraph("Resources/title6.png");
}

void Title::Initialize()
{
	curPosX = WIN_WIDTH / 2 - (300 * 0.5);
	curPosY = 380;
	scale1 = 0.5f;
	scale2 = 0.5f;
	scale3 = 0.5f;
	doorPosX1 = WIN_WIDTH / 2 - 592 / 2;
	doorPosX2 = WIN_WIDTH / 2 + 592 / 2;
	moveFlag = false;
	AddSpeed = 1.0f;
	Speedframe = 0.0f;
	timer = 0;
	alpha = 255;
	settingFlag = false;
}

bool Title::Update(XINPUT_STATE input, XINPUT_STATE oldinput)
{
	if (input.Buttons[XINPUT_BUTTON_DPAD_UP] && !oldinput.Buttons[XINPUT_BUTTON_DPAD_UP] && curPosY >= 500) {
		curPosY -= 120;
	}

	if (input.Buttons[XINPUT_BUTTON_DPAD_DOWN] && !oldinput.Buttons[XINPUT_BUTTON_DPAD_DOWN] && curPosY <= 500) {
		curPosY += 120;
	}

	if (curPosY == 380)
	{
		scale1 = 0.7f;
		scale2 = 0.5f;
		scale3 = 0.5f;

		if (input.Buttons[XINPUT_BUTTON_A] && !oldinput.Buttons[XINPUT_BUTTON_A]) {
			moveFlag = true;
		}
	}
	if (curPosY == 500)
	{
		scale1 = 0.5f;
		scale2 = 0.7f;
		scale3 = 0.5f;
		if (input.Buttons[XINPUT_BUTTON_A] && !oldinput.Buttons[XINPUT_BUTTON_A]) {

		}
	}
	if (curPosY == 620)
	{
		scale1 = 0.5f;
		scale2 = 0.5f;
		scale3 = 0.7f;

		if (input.Buttons[XINPUT_BUTTON_A] && !oldinput.Buttons[XINPUT_BUTTON_A]) {
			exit(0);
		}
	}

	if (moveFlag == true)
	{
		if (Speedframe < 1.0f) {
			Speedframe += 0.025f;
		}

		AddSpeed = Ease(InOut, Cubic, Speedframe, AddSpeed, 8.0f);

		doorPosX1 -= AddSpeed;
		doorPosX2 += AddSpeed;
	}
	if (doorPosX1 <= -140)
	{
		moveFlag = false;
		timer++;
		alpha-=2;
		if (timer > 120)
		{
			Speedframe = 0.0f;
			return true;
		}
	}
	return false;
}

void Title::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawRotaGraph(doorPosX1, 720 / 2, 1.0f, 0.0f, TitleTex6, TRUE);
	DrawRotaGraph(doorPosX2, 720 / 2, 1.0f, DX_PI_F, TitleTex6, TRUE);
	DrawRotaGraph(WIN_WIDTH / 2, 380, scale1, 0.0f, TitleTex2, TRUE);
	DrawRotaGraph(WIN_WIDTH / 2, 500, scale2, 0.0f, TitleTex3, TRUE);
	DrawRotaGraph(WIN_WIDTH / 2, 620, scale3, 0.0f, TitleTex5, TRUE);
	DrawRotaGraph(curPosX, curPosY, 0.5f, 0.0f, TitleTex4, TRUE);
	DrawGraph(0, 0, TitleTex, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
