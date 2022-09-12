#include "Tutorial.h"
#include <DxLib.h>
#include "Easing.h"

Tutorial::Tutorial()
{
	
}

void Tutorial::Initialize()
{
	TutorialGraph = LoadGraph("Resources/Tutorial.png");
	TutorialNumber = Tutorial0;
	TutorialTimer = 500;
	TextNumber = 0;
	TutorialClear = false;
	TutorialPosX = 1780.0f;
	frame = 0.0f;
	TextNumber = TutorialTex0;
	TextStart = true;
	TextEnd = false;
	TutorialStopTimer = 0;
	TextInterVal = 0;
	TextCount = 0;
	TextCheck = false;
	TutorialCheck = false;

	doorStart = false;
	doorEnd = false;
	doorStopTimer = 0;
	doorframe = 0.0f;
	doorPosX1 = -320.0f;
	doorPosX2 = 1600.0f;
	doorTex = LoadGraph("Resources/tutorialdoor.png");
}

bool Tutorial::Update(XINPUT_STATE input, XINPUT_STATE oldinput, int TutorialCount)
{
	//チュートリアルスキップ
	if (input.Buttons[XINPUT_BUTTON_Y] && !oldinput.Buttons[XINPUT_BUTTON_Y]) {
		doorStart = true;
	}
	//チュートリアルの進行状況を表している
	if (TutorialNumber == Tutorial0) {
		TutorialCheck = true;
		/*if ((input.LeftTrigger && !oldinput.LeftTrigger) || (input.RightTrigger && !oldinput.RightTrigger)) {
		
			if (TextCount == 1 && frame == 1.0f) {
				TextStart = false;
				frame = 0.0f;
				TextEnd = true;
			}
		}*/

		if (TextCount < 1) {
			//easingでテキストが流れてくる
			if (TextStart) {
				if (frame < 1.0f) {
					frame += 0.01f;
				}
				else {
					frame = 1.0f;
				}

				if (TextCount == 0) {
					TutorialStopTimer++;
					if (TutorialStopTimer == 120) {
						TutorialStopTimer = 0;
						TextStart = false;
						frame = 0.0f;
						TextEnd = true;
					}
				}
				TutorialPosX = Ease(In, Cubic, frame, TutorialPosX, WIN_WIDTH / 2);
			}
			if (TextEnd) {
				if (frame < 1.0f) {
					frame += 0.01f;
				}
				else {
					TextNumber++;
					TextCount++;
					TextEnd = false;
					frame = 0.0f;
				}
				TutorialPosX = Ease(In, Cubic, frame, TutorialPosX, -500.0f);
			}

			if (!TextStart && !TextEnd) {
				TextInterVal++;
				if (TextInterVal == 20) {
					TextInterVal = 0;
					TutorialPosX = 1780.0f;
					frame = 0.0f;
					TextStart = true;
				}
			}
		}
		else {
			TextCheck = true;
		}

		//テキストとタスクが終わったら次のチュートリアルに映る
		if (TutorialCheck && TextCheck) {
			TextCount = 0;
			TextCheck = false;
			TutorialCheck = false;
			TutorialNumber = Tutorial1;
			TutorialTimer = 500;
		}
	}
	else if (TutorialNumber == Tutorial1) {
		if (TextCount < 3) {
			//easingでテキストが流れてくる
			if (TextStart) {
				if (frame < 1.0f) {
					frame += 0.01f;
				}
				else {
					frame = 1.0f;
				}

				if (TextCount == 0) {
					TutorialStopTimer++;
					if (TutorialStopTimer == 120) {
						TutorialStopTimer = 0;
						TextStart = false;
						frame = 0.0f;
						TextEnd = true;
					}
				}
				TutorialPosX = Ease(In, Cubic, frame, TutorialPosX, WIN_WIDTH / 2);
			}
			if (TextEnd) {
				if (frame < 1.0f) {
					frame += 0.01f;
				}
				else {
					TextNumber++;
					TextCount++;
					TextEnd = false;
					frame = 0.0f;
				}
				TutorialPosX = Ease(In, Cubic, frame, TutorialPosX, -500.0f);
			}

			if (!TextStart && !TextEnd) {
				TextInterVal++;
				if (TextInterVal == 20) {
					TextInterVal = 0;
					TutorialPosX = 1780.0f;
					frame = 0.0f;
					TextStart = true;
				}
			}
		}
		else {
			TextCheck = true;
		}

		if (TutorialCount == 1) {
			TutorialCheck = true;
			if (TextCount == 1 && frame == 1.0f) {
				TextStart = false;
				frame = 0.0f;
				TextEnd = true;
			}
		}

		if (TutorialTimer >= 300) {
			TutorialTimer--;
		}
		else {
			TutorialTimer = 300;
		}

		//テキストとタスクが終わったら次のチュートリアルに映る
		if (TutorialCheck && TextCheck) {

			TextCount = 0;
			TextCheck = false;
			TutorialCheck = false;
			TutorialNumber = Tutorial2;
		}

	}
	else if (TutorialNumber == Tutorial2) {
		if (TextCount < 5) {
			//easingでテキストが流れてくる
			if (TextStart) {
				if (frame < 1.0f) {
					frame += 0.01f;
				}
				else {
					frame = 1.0f;
				}

				TutorialStopTimer++;
				if (TutorialStopTimer == 120) {
					TutorialStopTimer = 0;
					TextStart = false;
					frame = 0.0f;
					TextEnd = true;
				}
				TutorialPosX = Ease(In, Cubic, frame, TutorialPosX, WIN_WIDTH / 2);
			}
			if (TextEnd) {
				if (frame < 1.0f) {
					frame += 0.01f;
				}
				else {
					TextNumber++;
					TextCount++;
					TextEnd = false;
					frame = 0.0f;
				}
				TutorialPosX = Ease(In, Cubic, frame, TutorialPosX, -500.0f);
			}

			if (!TextStart && !TextEnd) {
				TextInterVal++;
				if (TextInterVal == 10) {
					TextInterVal = 0;
					TutorialPosX = 1780.0f;
					frame = 0.0f;
					TextStart = true;
				}
			}
		}
		else {
			TextCheck = true;
		}

		if (TutorialCount == 5) {
			TutorialCheck = true;
		}

		if (TutorialTimer >= 100) {
			TutorialTimer--;
		}
		else {
			TutorialTimer = 100;
		}

		//テキストとタスクが終わったら次のチュートリアルに映る
		if (TutorialCheck && TextCheck) {
			TextCount = 0;
			TextCheck = false;
			TutorialCheck = false;
			TutorialNumber = Tutorial3;
		}
	}
	else if (TutorialNumber == Tutorial3) {
		if (TextCount < 3) {
			//easingでテキストが流れてくる
			if (TextStart) {
				if (frame < 1.0f) {
					frame += 0.01f;
				}
				else {
					frame = 1.0f;
				}

				if (TextCount == 0 || TextCount == 2) {
					TutorialStopTimer++;
					if (TutorialStopTimer == 120) {
						TutorialStopTimer = 0;
						TextStart = false;
						frame = 0.0f;
						TextEnd = true;
					}
				}
				TutorialPosX = Ease(In, Cubic, frame, TutorialPosX, WIN_WIDTH / 2);
			}
			if (TextEnd) {
				if (frame < 1.0f) {
					frame += 0.01f;
				}
				else {
					TextNumber++;
					TextCount++;
					TextEnd = false;
					frame = 0.0f;
				}
				TutorialPosX = Ease(In, Cubic, frame, TutorialPosX, -500.0f);
			}

			if (!TextStart && !TextEnd) {
				TextInterVal++;
				if (TextInterVal == 20) {
					TextInterVal = 0;
					TutorialPosX = 1780.0f;
					frame = 0.0f;
					TextStart = true;
				}
			}
		}
		else {
			TextCheck = true;
		}

		if (TextCount == 1) {
			if (TutorialTimer >= 300) {
				TutorialTimer--;
			}
			else {
				TutorialTimer = 300;
			}
		}

		if (TutorialCount == 6) {
			TutorialCheck = true;
			if (TextCount == 1 && frame == 1.0f) {
				TextStart = false;
				frame = 0.0f;
				TextEnd = true;
			}
		}

		//テキストとタスクが終わったら次のチュートリアルに映る
		if (TutorialCheck && TextCheck) {
			TextCount = 0;
			TextCheck = false;
			TutorialCheck = false;
			TutorialNumber = Tutorial4;
		}
	}
	else if (TutorialNumber == Tutorial4) {
		if (TextCount < 3) {
			//easingでテキストが流れてくる
			if (TextStart) {
				if (frame < 1.0f) {
					frame += 0.01f;
				}
				else {
					frame = 1.0f;
				}

				if (TextCount == 0 || TextCount == 1) {
					TutorialStopTimer++;
					if (TutorialStopTimer == 120) {
						TutorialStopTimer = 0;
						TextStart = false;
						frame = 0.0f;
						TextEnd = true;
					}
				}
				TutorialPosX = Ease(In, Cubic, frame, TutorialPosX, WIN_WIDTH / 2);
			}
			if (TextEnd) {
				if (frame < 1.0f) {
					frame += 0.01f;
				}
				else {
					TextNumber++;
					TextCount++;
					TextEnd = false;
					frame = 0.0f;
				}
				TutorialPosX = Ease(In, Cubic, frame, TutorialPosX, -500.0f);
			}

			if (!TextStart && !TextEnd) {
				TextInterVal++;
				if (TextInterVal == 20) {
					TextInterVal = 0;
					TutorialPosX = 1780.0f;
					frame = 0.0f;
					TextStart = true;
				}
			}
		}
		else {
			TextCheck = true;
		}

		if (TextCount == 2) {
			if (TutorialTimer >= 200) {
				TutorialTimer--;
			}
			else {
				TutorialTimer = 200;
			}
		}

		if (TutorialCount == 8 && TutorialClear) {
			TutorialCheck = true;
			if (TextCount == 2 && frame == 1.0f) {
				TextStart = false;
				frame = 0.0f;
				TextEnd = true;
			}
		}

		//テキストとタスクが終わったら次のチュートリアルに映る
		if (TutorialCheck && TextCheck) {
			TextCount = 0;
			TextCheck = false;
			TutorialCheck = false;
			TutorialNumber = Tutorial5;
		}
	}
	else if (TutorialNumber == Tutorial5) {
		TutorialCheck = true;
		if (TextCount < 3) {
			//easingでテキストが流れてくる
			if (TextStart) {
				if (frame < 1.0f) {
					frame += 0.01f;
				}
				else {
					frame = 1.0f;
				}

				TutorialStopTimer++;
				if (TutorialStopTimer == 120) {
					TutorialStopTimer = 0;
					TextStart = false;
					frame = 0.0f;
					TextEnd = true;
				}
				TutorialPosX = Ease(In, Cubic, frame, TutorialPosX, WIN_WIDTH / 2);
			}
			if (TextEnd) {
				if (frame < 1.0f) {
					frame += 0.01f;
				}
				else {
					TextNumber++;
					TextCount++;
					TextEnd = false;
					frame = 0.0f;
				}
				TutorialPosX = Ease(In, Cubic, frame, TutorialPosX, -500.0f);
			}

			if (!TextStart && !TextEnd) {
				TextInterVal++;
				if (TextInterVal == 20) {
					TextInterVal = 0;
					TutorialPosX = 1780.0f;
					frame = 0.0f;
					TextStart = true;
				}
			}
		}
		else {
			TextCheck = true;
		}

		//テキストとタスクが終わったら次のチュートリアルに映る
		if (TutorialCheck && TextCheck) {
			//doorPosX1 = -320.0f;
			//doorPosX2 = 1600.0f;
			doorStart = true;
		}
	}

	if (doorStart) {
		if (doorframe < 1.0f) {
			doorframe += 0.01f;
		}
		else {
			doorframe = 1.0f;
			doorStopTimer++;

			if (doorStopTimer == 10) {
				doorStart = false;
				doorEnd = true;
				doorframe = 0.0f;
				doorStopTimer = 0;
			}
		}
		doorPosX1 = Ease(In, Cubic, doorframe, doorPosX1, 320.0f);
		doorPosX2 = Ease(In, Cubic, doorframe, doorPosX2, 960.0f);
	}

	if (doorEnd) {
		if (doorframe < 1.0f) {
			doorframe += 0.01f;
		}
		else {
			return true;
		}
		doorPosX1 = Ease(In, Cubic, doorframe, doorPosX1, -320.0f);
		doorPosX2 = Ease(In, Cubic, doorframe, doorPosX2, 1600.0f);
	}
	return false;
}

void Tutorial::Draw()
{
	//DrawFormatString(0, 360, GetColor(0, 0, 0), "TutorialTimer %d", TutorialTimer);
	//DrawFormatString(0, 380, GetColor(0, 0, 0), "TextCount %d", TextCount);
	/*DrawFormatString(0, 360, GetColor(0, 0, 0), "TutorialTimer %d", TutorialTimer);
	
	DrawFormatString(0, 400, GetColor(0, 0, 0), "TextStart %d", TextStart);
	DrawFormatString(0, 420, GetColor(0, 0, 0), "TextEnd %d", TextEnd);
	DrawFormatString(0, 440, GetColor(0, 0, 0), "TutorialStopTimer %d", TutorialStopTimer);*/
	//DrawFormatString(600, 460, GetColor(0, 0, 0), "doorframe %f", doorframe);
	////DrawFormatString(600, 480, GetColor(0, 0, 0), "doorposX %f", doorPosX1);
	//DrawFormatString(0, 500, GetColor(0, 0, 0), "doorpos2 %f", doorPosX2);

	if (!doorEnd) {
		DrawExtendGraph((TutorialPosX - 500), (656 - 64), (TutorialPosX + 500), (656 + 64),
			TutorialGraph, TRUE);

		ChangeFont("HOKKORIRegular");
		SetFontSize(50);
		if (TextNumber == TutorialTex0) {
			DrawFormatString((TutorialPosX - 290), 630, GetColor(0, 0, 0), "まずRTとLTで方向を変換してみろ");
		}
		else if (TextNumber == TutorialTex1) {
			DrawFormatString((TutorialPosX - 200), 630, GetColor(0, 0, 0), "次は敵を倒してみろ");
		}
		else if (TextNumber == TutorialTex2) {
			DrawFormatString((TutorialPosX - 420), 630, GetColor(0, 0, 0), "Lスティックで照準を合わせてAを押せ");
		}
		else if (TextNumber == TutorialTex3) {
			DrawFormatString((TutorialPosX - 140), 630, GetColor(0, 0, 0), "Bを押すと");
		}
		else if (TextNumber == TutorialTex4) {
			DrawFormatString((TutorialPosX - 360), 630, GetColor(0, 0, 0), "同じサークル上の敵を止められるぞ");
		}
		else if (TextNumber == TutorialTex5) {
			DrawFormatString((TutorialPosX - 460), 630, GetColor(0, 0, 0), "敵とぶつかると動けなくなってしまうぞ");
		}
		else if (TextNumber == TutorialTex6) {
			DrawFormatString((TutorialPosX - 400), 630, GetColor(0, 0, 0), "近くに敵がいる状態で敵を倒すと");
		}
		else if (TextNumber == TutorialTex7) {
			DrawFormatString((TutorialPosX - 360), 630, GetColor(0, 0, 0), "近くの敵にリンクして倒せるぞ");
		}
		else if (TextNumber == TutorialTex8) {
			DrawFormatString((TutorialPosX - 190), 630, GetColor(0, 0, 0), "リンクした時は・・・");
		}
		else if (TextNumber == TutorialTex9) {
			DrawFormatString((TutorialPosX - 260), 630, GetColor(0, 0, 0), "レーンを跨いで倒せるぞ");
		}
		else if (TextNumber == TutorialTex10) {
			DrawFormatString((TutorialPosX - 460), 630, GetColor(0, 0, 0), "リンク終了時の場所でスコアが決まるぞ");
		}
		
		else if (TextNumber == TutorialTex11) {
			DrawFormatString((TutorialPosX - 340), 630, GetColor(0, 0, 0), "リンクしてスコアを稼ぐのだ");
		}
		SetFontSize(20);
	}
	DrawRotaGraph(doorPosX1, 720 / 2, 1.0f, 0.0f, doorTex, TRUE);
	DrawRotaGraph(doorPosX2, 720 / 2, 1.0f, DX_PI_F, doorTex, TRUE);
}
