#include "Title.h"
#include <DxLib.h>

Title::Title()
{
	TitleTex = LoadGraph("Resources/title1.png");
	TitleTex2 = LoadGraph("Resources/title2.png");
	TitleTex3 = LoadGraph("Resources/title3.png");
	TitleTex4 = LoadGraph("Resources/title4.png");
	TitleTex5 = LoadGraph("Resources/title5.png");
}

void Title::Initialize()
{
	curPosX = WIN_WIDTH / 2 - (300 * 0.5);
	curPosY = 380;
	scale1 = 0.5f;
	scale2 = 0.5f;
	scale3 = 0.5f;
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
			return true;
		}
	}
	if (curPosY == 500)
	{
		scale1 = 0.5f;
		scale2 = 0.7f;
		scale3 = 0.5f;
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

	return false;
}

void Title::Draw()
{
	DrawRotaGraph(WIN_WIDTH / 2, 380, scale1, 0.0f, TitleTex2, TRUE);
	DrawRotaGraph(WIN_WIDTH / 2, 500, scale2, 0.0f, TitleTex3, TRUE);
	DrawRotaGraph(WIN_WIDTH / 2, 620, scale3, 0.0f, TitleTex5, TRUE);
	DrawRotaGraph(curPosX, curPosY, 0.5f, 0.0f, TitleTex4, TRUE);
	DrawGraph(0, 0, TitleTex, TRUE);
}
