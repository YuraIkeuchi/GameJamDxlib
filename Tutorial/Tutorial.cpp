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
	TutorialTimer = 600;
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

bool Tutorial::Update(XINPUT_STATE input, XINPUT_STATE oldinput, int TutorialCount)
{
	//�`���[�g���A���̐i�s�󋵂�\���Ă���
	if (TutorialNumber == Tutorial0) {
		if ((input.LeftTrigger && !oldinput.LeftTrigger) || (input.RightTrigger && !oldinput.RightTrigger)) {
			TutorialCheck = true;
			if (TextCount == 1 && frame == 1.0f) {
				TextStart = false;
				frame = 0.0f;
				TextEnd = true;
			}
		}

		if (TextCount < 2) {
			//easing�Ńe�L�X�g������Ă���
			if (TextStart) {
				if (frame < 1.0f) {
					frame += 0.01f;
				}
				else {
					frame = 1.0f;
				}

				if (TextCount == 0) {
					TutorialStopTimer++;
					if (TutorialStopTimer == 150) {
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
				if (TextInterVal == 50) {
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

		//�e�L�X�g�ƃ^�X�N���I������玟�̃`���[�g���A���ɉf��
		if (TutorialCheck && TextCheck) {
			TextCount = 0;
			TextCheck = false;
			TutorialCheck = false;
			TutorialNumber = Tutorial1;
			TutorialTimer = 800;
		}
	}
	else if (TutorialNumber == Tutorial1) {
		if (TextCount < 2) {
			//easing�Ńe�L�X�g������Ă���
			if (TextStart) {
				if (frame < 1.0f) {
					frame += 0.01f;
				}
				else {
					frame = 1.0f;
				}

				if (TextCount == 0) {
					TutorialStopTimer++;
					if (TutorialStopTimer == 150) {
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
				if (TextInterVal == 50) {
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

		if (TutorialTimer >= 500) {
			TutorialTimer--;
		}
		else {
			TutorialTimer = 500;
		}

		//�e�L�X�g�ƃ^�X�N���I������玟�̃`���[�g���A���ɉf��
		if (TutorialCheck && TextCheck) {
			TextCount = 0;
			TextCheck = false;
			TutorialCheck = false;
			TutorialNumber = Tutorial2;
		}

	}
	else if (TutorialNumber == Tutorial2) {
		if (TextCount < 3) {
			//easing�Ńe�L�X�g������Ă���
			if (TextStart) {
				if (frame < 1.0f) {
					frame += 0.01f;
				}
				else {
					frame = 1.0f;
				}

				if (TextCount == 0 || TextCount == 2) {
					TutorialStopTimer++;
					if (TutorialStopTimer == 150) {
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
				if (TextInterVal == 50) {
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

		if (TutorialCount == 3) {
			TutorialCheck = true;
			if (TextCount == 1 && frame == 1.0f) {
				TextStart = false;
				frame = 0.0f;
				TextEnd = true;
			}
		}

		if (TextCount == 1) {
			if (TutorialTimer >= 400) {
				TutorialTimer--;
			}
			else {
				TutorialTimer = 400;
			}
		}

		//�e�L�X�g�ƃ^�X�N���I������玟�̃`���[�g���A���ɉf��
		if (TutorialCheck && TextCheck) {
			TextCount = 0;
			TextCheck = false;
			TutorialCheck = false;
			TutorialNumber = Tutorial3;
		}

	}
	else if (TutorialNumber == Tutorial3) {
		if (TextCount < 3) {
			//easing�Ńe�L�X�g������Ă���
			if (TextStart) {
				if (frame < 1.0f) {
					frame += 0.01f;
				}
				else {
					frame = 1.0f;
				}

				if (TextCount == 0 || TextCount == 2) {
					TutorialStopTimer++;
					if (TutorialStopTimer == 150) {
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
				if (TextInterVal == 50) {
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

		//�e�L�X�g�ƃ^�X�N���I������玟�̃`���[�g���A���ɉf��
		if (TutorialCheck && TextCheck) {
			TextCount = 0;
			TextCheck = false;
			TutorialCheck = false;
			TutorialNumber = Tutorial4;
		}
	}
	else if (TutorialNumber == Tutorial4) {
		if (TextCount < 3) {
			//easing�Ńe�L�X�g������Ă���
			if (TextStart) {
				if (frame < 1.0f) {
					frame += 0.01f;
				}
				else {
					frame = 1.0f;
				}

				if (TextCount == 0 || TextCount == 1) {
					TutorialStopTimer++;
					if (TutorialStopTimer == 150) {
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
				if (TextInterVal == 50) {
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

		//�e�L�X�g�ƃ^�X�N���I������玟�̃`���[�g���A���ɉf��
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
			//easing�Ńe�L�X�g������Ă���
			if (TextStart) {
				if (frame < 1.0f) {
					frame += 0.01f;
				}
				else {
					frame = 1.0f;
				}

				TutorialStopTimer++;
				if (TutorialStopTimer == 150) {
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
				if (TextInterVal == 50) {
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

		//�e�L�X�g�ƃ^�X�N���I������玟�̃`���[�g���A���ɉf��
		if (TutorialCheck && TextCheck) {
			return true;
		}
	}
	return false;
}

void Tutorial::Draw()
{
	DrawExtendGraph((TutorialPosX - 500) ,(656 - 64), (TutorialPosX + 500), (656 + 64),
		TutorialGraph, TRUE);
	DrawFormatString(0, 360, GetColor(0, 0, 0), "TutorialTimer %d", TutorialTimer);
	DrawFormatString(0, 380, GetColor(0, 0, 0), "TextCount %d", TextCount);
	DrawFormatString(0, 400, GetColor(0, 0, 0), "TextStart %d", TextStart);
	DrawFormatString(0, 420, GetColor(0, 0, 0), "TextEnd %d", TextEnd);
	DrawFormatString(0, 440, GetColor(0, 0, 0), "TutorialStopTimer %d", TutorialStopTimer);
	DrawFormatString(0, 460, GetColor(0, 0, 0), "frame %f", frame);

	ChangeFont("HOKKORIRegular");
	SetFontSize(50);
	if (TextNumber == TutorialTex0) {
		DrawFormatString((TutorialPosX - 420), 630, GetColor(0, 0, 0), "�悭�����ȁE�E�E���[�T���̐��E��");
	}
	else if (TextNumber == TutorialTex1) {
		DrawFormatString((TutorialPosX - 280), 630, GetColor(0, 0, 0), "RT��LT�ŕ�����ϊ����Ă݂�");
	}
	else if (TextNumber == TutorialTex2) {
		DrawFormatString((TutorialPosX - 200), 630, GetColor(0, 0, 0), "���͓G��|���Ă݂�");
	}
	else if (TextNumber == TutorialTex3) {
		DrawFormatString((TutorialPosX - 420), 630, GetColor(0, 0, 0), "L�X�e�B�b�N�ŏƏ������킹��A������");
	}
	else if (TextNumber == TutorialTex4) {
		DrawFormatString((TutorialPosX - 180), 630, GetColor(0, 0, 0), "�����N�̐��������悤");
	}
	else if (TextNumber == TutorialTex5) {
		DrawFormatString((TutorialPosX - 410), 630, GetColor(0, 0, 0), "�߂��ɓG�������ԂœG��|����");
	}
	else if (TextNumber == TutorialTex6) {
		DrawFormatString((TutorialPosX - 360), 630, GetColor(0, 0, 0), "�߂��̓G�Ƀ����N���ē|���邼");
	}
	else if (TextNumber == TutorialTex7) {
		DrawFormatString((TutorialPosX - 180), 630, GetColor(0, 0, 0), "�����N�������́E�E�E");
	}
	else if (TextNumber == TutorialTex8) {
		DrawFormatString((TutorialPosX - 250), 630, GetColor(0, 0, 0), "���[�����ׂ��œ|���邼");
	}
	else if (TextNumber == TutorialTex9) {
		DrawFormatString((TutorialPosX - 450), 630, GetColor(0, 0, 0), "�����N�I�����̏ꏊ�ŃX�R�A�����܂邼");
	}
	else if (TextNumber == TutorialTex10) {
		DrawFormatString((TutorialPosX - 160), 630, GetColor(0, 0, 0), "B��������");
	}
	else if (TextNumber == TutorialTex11) {
		DrawFormatString((TutorialPosX - 350), 630, GetColor(0, 0, 0), "�����T�[�N����̓G���~�߂��邼");
	}
	else if (TextNumber == TutorialTex12) {
		DrawFormatString((TutorialPosX - 360), 630, GetColor(0, 0, 0), "�����N���ēG��|���Ă݂悤");
	}
	else if (TextNumber == TutorialTex13) {
		DrawFormatString((TutorialPosX - 180), 630, GetColor(0, 0, 0), "�悭�o������");
	}
	else if (TextNumber == TutorialTex14) {
		DrawFormatString((TutorialPosX - 450), 630, GetColor(0, 0, 0), "�G�ƂԂ���Ɠ����Ȃ��Ȃ��Ă��܂���");
	}
	else if (TextNumber == TutorialTex15) {
		DrawFormatString((TutorialPosX - 340), 630, GetColor(0, 0, 0), "�����N���ăX�R�A���҂��̂�");
	}
	SetFontSize(20);
}
