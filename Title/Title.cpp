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
	TitleSound1 = LoadSoundMem("Resources/sound/titleSound.mp3");
	TitleTex7 = LoadGraph("Resources/title7.png");
	TitleTex8 = LoadGraph("Resources/title8.png");
	LoadDivGraph("Resources/title9.png", 6, 6, 1, 288, 112, TitleTex9);
	TitleSe1 = LoadSoundMem("Resources/sound/titleSound2.mp3");
	TitleSe2 = LoadSoundMem("Resources/sound/titleSound3.mp3");
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
	tex9Num = 2;
	endFlag = false;
	ChangeVolumeSoundMem(soundBolume, TitleSound1);
	PlaySoundMem(TitleSound1, DX_PLAYTYPE_LOOP);
	ChangeVolumeSoundMem(soundBolume, TitleSe1);
	ChangeVolumeSoundMem(soundBolume, TitleSe2);
}

bool Title::Update(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput)
{
	if (((keys[KEY_INPUT_UP] && !oldkeys[KEY_INPUT_UP]) || (input.Buttons[XINPUT_BUTTON_DPAD_UP] && !oldinput.Buttons[XINPUT_BUTTON_DPAD_UP])) && curPosY >= 500 && settingFlag == false && moveFlag == false) {
		curPosY -= 120;
		PlaySoundMem(TitleSe1, DX_PLAYTYPE_BACK);
	}

	if (((keys[KEY_INPUT_UP] && !oldkeys[KEY_INPUT_UP]) || (input.Buttons[XINPUT_BUTTON_DPAD_UP] && !oldinput.Buttons[XINPUT_BUTTON_DPAD_UP])) && curPosY >= 620 && settingFlag == true) {
		curPosY -= 120;
		PlaySoundMem(TitleSe1, DX_PLAYTYPE_BACK);
	}

	if (((keys[KEY_INPUT_DOWN] && !oldkeys[KEY_INPUT_DOWN]) || (input.Buttons[XINPUT_BUTTON_DPAD_DOWN] && !oldinput.Buttons[XINPUT_BUTTON_DPAD_DOWN])) && curPosY <= 500 && moveFlag == false) {
		curPosY += 120;
		PlaySoundMem(TitleSe1, DX_PLAYTYPE_BACK);
	}

	if (curPosY == 380)
	{
		scale1 = 0.7f;
		scale2 = 0.5f;
		scale3 = 0.5f;

		if (((keys[KEY_INPUT_SPACE] && !oldkeys[KEY_INPUT_SPACE]) || (input.Buttons[XINPUT_BUTTON_A] && !oldinput.Buttons[XINPUT_BUTTON_A])) && moveFlag == false && settingFlag == false) {
			moveFlag = true;
			PlaySoundMem(TitleSe2, DX_PLAYTYPE_BACK);
		}
	}
	if (curPosY == 500)
	{
		scale1 = 0.5f;
		scale2 = 0.7f;
		scale3 = 0.5f;
		if (((keys[KEY_INPUT_SPACE] && !oldkeys[KEY_INPUT_SPACE]) || (input.Buttons[XINPUT_BUTTON_A] && !oldinput.Buttons[XINPUT_BUTTON_A])) && settingFlag == false && moveFlag == false) {
			settingFlag = true;
			PlaySoundMem(TitleSe2, DX_PLAYTYPE_BACK);
		}
		if (((keys[KEY_INPUT_LEFT] && !oldkeys[KEY_INPUT_LEFT]) || (input.Buttons[XINPUT_BUTTON_DPAD_LEFT] && !oldinput.Buttons[XINPUT_BUTTON_DPAD_LEFT])) && settingFlag == true) {
			if (tex9Num > 0)
			{
				tex9Num--;
				soundBolume -= 20;
				ChangeVolumeSoundMem(soundBolume, TitleSound1);
				ChangeVolumeSoundMem(soundBolume, TitleSe1);
				ChangeVolumeSoundMem(soundBolume, TitleSe2);
			}
		}
		if (((keys[KEY_INPUT_RIGHT] && !oldkeys[KEY_INPUT_RIGHT]) || (input.Buttons[XINPUT_BUTTON_DPAD_RIGHT] && !oldinput.Buttons[XINPUT_BUTTON_DPAD_RIGHT])) && settingFlag == true) {
			if (tex9Num < 5)
			{
				tex9Num++;
				soundBolume += 20;
				ChangeVolumeSoundMem(soundBolume, TitleSound1);
				ChangeVolumeSoundMem(soundBolume, TitleSe1);
				ChangeVolumeSoundMem(soundBolume, TitleSe2);
			}
		}
	}
	if (curPosY == 620)
	{
		scale1 = 0.5f;
		scale2 = 0.5f;
		scale3 = 0.7f;

		if (((keys[KEY_INPUT_SPACE] && !oldkeys[KEY_INPUT_SPACE]) || (input.Buttons[XINPUT_BUTTON_A] && !oldinput.Buttons[XINPUT_BUTTON_A])) && settingFlag == false) {
			PlaySoundMem(TitleSe2, DX_PLAYTYPE_BACK);
			endFlag = true;
		}
		if (((keys[KEY_INPUT_SPACE] && !oldkeys[KEY_INPUT_SPACE]) || (input.Buttons[XINPUT_BUTTON_A] && !oldinput.Buttons[XINPUT_BUTTON_A])) && settingFlag == true) {
			PlaySoundMem(TitleSe2, DX_PLAYTYPE_BACK);
			curPosY = 500;
			settingFlag = false;
		}
	}

	if (CheckSoundMem(TitleSe2) == 0 && endFlag == true)
	{
		exit(0);
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
		doorPosX1 = -140;
		doorPosX2 = 1280 + 140;
		timer++;
		alpha-=2;
		if (timer > 120)
		{
			moveFlag = false;
			Speedframe = 0.0f;
			StopSoundMem(TitleSound1);
			return true;
		}
	}
	return false;
}

void Title::Draw()
{
	if (settingFlag == false)
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
	else
	{
		DrawRotaGraph(doorPosX1, 720 / 2, 1.0f, 0.0f, TitleTex6, TRUE);
		DrawRotaGraph(doorPosX2, 720 / 2, 1.0f, DX_PI_F, TitleTex6, TRUE);
		DrawRotaGraph(curPosX, curPosY, 0.5f, 0.0f, TitleTex4, TRUE);
		DrawRotaGraph(WIN_WIDTH / 2, 380, scale1, 0.0f, TitleTex7, TRUE);
		DrawGraph(WIN_WIDTH / 2-120, 500 - 112 / 2, TitleTex9[tex9Num], TRUE);
		DrawRotaGraph(WIN_WIDTH / 2, 620, scale3, 0.0f, TitleTex8, TRUE);
		DrawGraph(0, 0, TitleTex, TRUE);
	}
}
