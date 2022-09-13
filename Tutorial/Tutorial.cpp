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

}

void Tutorial::Update(XINPUT_STATE input, XINPUT_STATE oldinput, int TutorialCount)
{
	////チュートリアルスキップ
	//if (input.Buttons[XINPUT_BUTTON_Y] && !oldinput.Buttons[XINPUT_BUTTON_Y]) {
	//	doorStart = true;
	//}
	//チュートリアルの進行状況を表している
	//操作説明
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
	//最初の敵を倒す
	else if (TutorialNumber == Tutorial1) {
		if (TextCount < 4) {
			//easingでテキストが流れてくる
			if (TextStart) {
				if (frame < 1.0f) {
					frame += 0.01f;
				}
				else {
					frame = 1.0f;
				}

				if (TextCount != 3) {
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

		if (TutorialCount == 0) {
			if (TutorialTimer >= 320) {
				TutorialTimer--;
			}
			else {
				TutorialTimer = 320;
			}
		}
		else if (TutorialCount == 1) {
			if (TutorialTimer >= 315) {
				TutorialTimer--;
			}
			else {
				TutorialTimer = 315;
			}
		}
		else if (TutorialCount == 2) {
			if (TutorialTimer >= 310) {
				TutorialTimer--;
			}
			else {
				TutorialTimer = 310;
			}
		}
		else if (TutorialCount == 3) {
			TutorialCheck = true;
			if (TextCount == 3 && frame == 1.0f) {
				TextStart = false;
				frame = 0.0f;
				TextEnd = true;
			}
			if (TutorialTimer >= 300) {
				TutorialTimer--;
			}
			else {
				TutorialTimer = 300;
			}
		}
		//テキストとタスクが終わったら次のチュートリアルに映る
		if (TutorialCheck && TextCheck) {
			TextCount = 0;
			TextCheck = false;
			TutorialCheck = false;
			TutorialNumber = Tutorial2;
		}

	}
	//リンクして敵を倒す
	else if (TutorialNumber == Tutorial2) {
		if (TextCount < 3) {
			//easingでテキストが流れてくる
			if (TextStart) {
				if (frame < 1.0f) {
					frame += 0.01f;
				}
				else {
					frame = 1.0f;
				}

				if (TextCount != 2) {
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

		if (TutorialCount == 6 && TutorialClear) {
			TutorialCheck = true;
			if (TextCount == 2 && frame == 1.0f) {
				TextStart = false;
				frame = 0.0f;
				TextEnd = true;
			}
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
		TutorialCheck = true;
		if (TextCount < 2) {
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

	}
}

void Tutorial::Draw()
{
	DrawFormatString(0, 360, GetColor(0, 0, 0), "TutorialTimer %d", TutorialTimer);
	DrawFormatString(0, 380, GetColor(0, 0, 0), "TutorialCheck %d", TutorialCheck);
	DrawFormatString(0, 400, GetColor(0, 0, 0), "TextCheck %d", TextCheck);
	DrawFormatString(0, 420, GetColor(0, 0, 0), "TutorialClear %d", TutorialClear);
	DrawFormatString(0, 440, GetColor(0, 0, 0), "TutorialPosX %f", TutorialPosX);
	//DrawFormatString(0, 380, GetColor(0, 0, 0), "TextCount %d", TextCount);
	/*DrawFormatString(0, 360, GetColor(0, 0, 0), "TutorialTimer %d", TutorialTimer);
	
	DrawFormatString(0, 400, GetColor(0, 0, 0), "TextStart %d", TextStart);
	DrawFormatString(0, 420, GetColor(0, 0, 0), "TextEnd %d", TextEnd);
	DrawFormatString(0, 440, GetColor(0, 0, 0), "TutorialStopTimer %d", TutorialStopTimer);*/
	//DrawFormatString(600, 460, GetColor(0, 0, 0), "doorframe %f", doorframe);
	////DrawFormatString(600, 480, GetColor(0, 0, 0), "doorposX %f", doorPosX1);
	//DrawFormatString(0, 500, GetColor(0, 0, 0), "doorpos2 %f", doorPosX2);

		DrawExtendGraph((TutorialPosX - 500), (656 - 64), (TutorialPosX + 500), (656 + 64),
			TutorialGraph, TRUE);

		ChangeFont("HOKKORIRegular");
		SetFontSize(50);
		if (TextNumber == TutorialTex0) {
			DrawFormatString((TutorialPosX - 360), 630, GetColor(0, 0, 0), "まずRTとLTで方向を変換してみろ");
		}
		else if (TextNumber == TutorialTex1) {
			DrawFormatString((TutorialPosX - 220), 630, GetColor(0, 0, 0), "次は敵を倒してみろ");
		}
		else if (TextNumber == TutorialTex2) {
			DrawFormatString((TutorialPosX - 420), 630, GetColor(0, 0, 0), "Lスティックで照準を合わせてAを押せ");
		}
		else if (TextNumber == TutorialTex3) {
			DrawFormatString((TutorialPosX - 460), 630, GetColor(0, 0, 0), "敵とぶつかると動けなくなってしまうぞ");
		}
		else if (TextNumber == TutorialTex4) {
			DrawFormatString((TutorialPosX - 450), 630, GetColor(0, 0, 0), "Bで同じサークル上の敵がスタンするぞ");
		}
		else if (TextNumber == TutorialTex5) {
			DrawFormatString((TutorialPosX - 400), 630, GetColor(0, 0, 0), "近くに敵がいる状態で敵を倒すと");
		}
		else if (TextNumber == TutorialTex6) {
			DrawFormatString((TutorialPosX - 360), 630, GetColor(0, 0, 0), "近くの敵にリンクして倒せるぞ");
		}
		else if (TextNumber == TutorialTex7) {
			DrawFormatString((TutorialPosX - 220), 630, GetColor(0, 0, 0), "リンクを使い倒そう");
		}
		else if (TextNumber == TutorialTex8) {
			DrawFormatString((TutorialPosX - 460), 630, GetColor(0, 0, 0), "リンク終了時の場所でスコアが決まるぞ");
		}
		else if (TextNumber == TutorialTex9) {
			DrawFormatString((TutorialPosX - 340), 630, GetColor(0, 0, 0), "リンクしてスコアを稼ぐのだ");
		}
		SetFontSize(20);
}
