#include "End.h"
#include <DxLib.h>
#include "Easing.h"

End::End()
{
	EndTex = LoadGraph("Resources/title1.png");
	EndTex6 = LoadGraph("Resources/title6.png");
	LoadDivGraph("Resources/rank.png", 4, 4, 1, 400, 112, EndTex10);
	EndTex11 = LoadGraph("Resources/end1.png");
	endBgm = LoadSoundMem("Resources/sound/endBgm.mp3");
	endSe1 = LoadSoundMem("Resources/sound/titleSound3.mp3");
}

void End::Initialize(int soundBolume)
{
	doorPosX1 = -140;
	doorPosX2 = 1280 + 140;
	moveFlag = false;
	AddSpeed = 1.0f;
	Speedframe = 0.0f;
	timer = 0;
	alpha = 100;
	endFlag = false;
	drawFlag = false;
	ChangeVolumeSoundMem(soundBolume, endBgm);
	PlaySoundMem(endBgm, DX_PLAYTYPE_LOOP);
	ChangeVolumeSoundMem(soundBolume, endSe1);
}

bool End::Update(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput)
{
	if (alpha < 255)
	{
		alpha += 2;
	}
	if (alpha >= 255)
	{
		moveFlag = true;
	}
	if (moveFlag == true)
	{
		if (Speedframe < 1.0f) {
			Speedframe += 0.025f;
		}

		AddSpeed = Ease(InOut, Cubic, Speedframe, AddSpeed, 8.0f);

		doorPosX1 += AddSpeed;
		doorPosX2 -= AddSpeed;
	}
	if (doorPosX1 >= WIN_WIDTH / 2 - 592 / 2)
	{
		doorPosX1 = WIN_WIDTH / 2 - 592 / 2;
		doorPosX2 = WIN_WIDTH / 2 + 592 / 2;
		moveFlag = false;
		timer++;
		if (timer > 40)
		{
			drawFlag = true;
			if (((keys[KEY_INPUT_SPACE] && !oldkeys[KEY_INPUT_SPACE]) || (input.Buttons[XINPUT_BUTTON_A] && !oldinput.Buttons[XINPUT_BUTTON_A])))
			{
				Speedframe = 0.0f;
				PlaySoundMem(endSe1, DX_PLAYTYPE_BACK);
				StopSoundMem(endBgm);
				return true;
			}
		}
	}
	return false;
}

void End::Draw(int score)
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawRotaGraph(doorPosX1, 720 / 2, 1.0f, 0.0f, EndTex6, TRUE);
	DrawRotaGraph(doorPosX2, 720 / 2, 1.0f, DX_PI_F, EndTex6, TRUE);
	DrawGraph(0, 0, EndTex, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	if (drawFlag)
	{
		if (score >= S)
		{
			DrawGraph(WIN_WIDTH / 2 - 200, 500, EndTex10[0], TRUE);
		}
		else if (score >= A)
		{
			DrawGraph(WIN_WIDTH / 2 - 200, 500, EndTex10[1], TRUE);
		}
		else if (score >= B)
		{
			DrawGraph(WIN_WIDTH / 2 - 200, 500, EndTex10[2], TRUE);
		}
		else if(score >= C)
		{
			DrawGraph(WIN_WIDTH / 2 - 200, 500, EndTex10[3], TRUE);
		}
		else
		{
			DrawGraph(WIN_WIDTH / 2 - 200, 500, EndTex10[3], TRUE);
		}
		DrawGraph(WIN_WIDTH / 2 - 200, 620, EndTex11, TRUE);
	}
}
