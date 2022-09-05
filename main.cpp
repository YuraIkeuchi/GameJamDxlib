#include "DxLib.h"
#include "math.h"
#include "Vector2.h"
#include "Vector3.h"
#include<time.h>

const char TITLE[] = "�w�Дԍ����O�F�^�C�g��";

const int WIN_WIDTH = 800; //�E�B���h�E����
const int WIN_HEIGHT = 600;//�E�B���h�E�c��

const int Enemy_Max = 5;
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	ChangeWindowMode(TRUE);						//�E�B���h�E���[�h�ɐݒ�
	//�E�B���h�E�T�C�Y���蓮�ł͕ύX�ł����A���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetMainWindowText(TITLE);					// �^�C�g����ύX
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);	//��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�i���j�^�[�̉𑜓x�ɍ��킹��j
	SetWindowSizeExtendRate(1.0);				//��ʃT�C�Y��ݒ�i�𑜓x�Ƃ̔䗦�Őݒ�j
	SetBackgroundColor(0xFF, 0xFF, 0xFF);		// ��ʂ̔w�i�F��ݒ肷��

	//Dx���C�u�����̏�����
	if (DxLib_Init() == -1) { return -1; }

	//�i�_�u���o�b�t�@�j�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	Vector3 cameraPosition(0.0f, 0.0f, 500.0f);
	Vector3 cameraTarget(0.0f, 0.0f, 0.0f);
	Vector3 cameraUp(0.0f, 1.0f, 0.0f);


	SetCameraNearFar(1.0f, 1000.0f);
	SetCameraScreenCenter(WIN_WIDTH / 2.0f, WIN_HEIGHT / 2.0f);
	SetCameraPositionAndTargetAndUpVec(
		cameraPosition,
		cameraTarget,
		cameraUp);

	//�摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���
	int player = LoadGraph("player.png");


	//�Q�[�����[�v�Ŏg���ϐ��̐錾
	char keys[256] = { 0 }; //�ŐV�̃L�[�{�[�h���p
	char oldkeys[256] = { 0 };//1���[�v�i�t���[���j�O�̃L�[�{�[�h���
	float PI = 3.14f;

	float x = WIN_WIDTH / 2;
	float y = WIN_HEIGHT / 2;

	float playerPosX = WIN_WIDTH / 2;
	float playerPosY = WIN_HEIGHT / 2;

	float _playerPosX = 0;
	float _playerPosY = 0;

	float Playerradius = 0.0f;
	float PlayerSpeed = 0.0f;
	float Playerscale = 80.0f;// LaneNum�ƈꏏ�ɕς��邱��
	float PlayerCircleX = 0.0f;
	float PlayerCircleY = 0.0f;
	float add = 1.0f;

	float EnemyPosX[Enemy_Max];
	float EnemyPosY[Enemy_Max];
	float Enemyradius[Enemy_Max];
	float EnemySpeed[Enemy_Max];
	float EnemySaveSpeed[Enemy_Max];
	float Enemyscale[Enemy_Max]; //LaneNum�ƈꏏ�ɕς��邱��
	float EnemyCircleX[Enemy_Max];
	float EnemyCircleY[Enemy_Max];
	float Enemyadd[Enemy_Max];
	bool EnemyAlive[Enemy_Max];
	int EnemyTimer[Enemy_Max];
	bool EnemyMove[Enemy_Max];
	bool EnemySet[Enemy_Max];
	bool EnemyStop[Enemy_Max];
	int EnemyStopTimer[Enemy_Max];
	int TargetLine[Enemy_Max];
	for (int i = 0; i < Enemy_Max; i++) {
		EnemyPosX[i] = 0.0f;
		EnemyPosY[i] = 0.0f;
		Enemyradius[i] = 0.0f;
		EnemySpeed[i] = 0.0f;
		Enemyscale[i] = 500.0f;
		EnemyCircleX[i] = 0.0f;
		EnemyCircleY[i] = 0.0f;
		Enemyadd[i] = 0.0f;
		EnemyAlive[i] = false;
		EnemyTimer[i] = rand() % 800 + 100;
		EnemyMove[i] = false;
		EnemySet[i] = false;
		EnemyStop[i] = false;
		EnemyStopTimer[i] = 0;
		TargetLine[i] = 0;
		EnemySaveSpeed[i] = 0.0f;
	}
	srand(time(NULL));
	// �Q�[�����[�v
	while (1)
	{
		//�ŐV�̃L�[�{�[�h��񂾂������̂͂P�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		for (int i = 0; i < 256; i++) {
			oldkeys[i] = keys[i];
		}
		//�ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		//��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		//�X�V����
		//�v���C���[
		if (keys[KEY_INPUT_DOWN] == 1 && oldkeys[KEY_INPUT_DOWN] == 0) {
			if (Playerscale > 81.0f) {
				Playerscale -= 40.0f;
			}
		}

		if (keys[KEY_INPUT_UP] == 1 && oldkeys[KEY_INPUT_UP] == 0) {
			if (Playerscale < 201.0f) {
				Playerscale += 40.0f;
			}
		}

		if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
			add = -add;
		}

		if (keys[KEY_INPUT_A] == 1 && oldkeys[KEY_INPUT_A] == 0) {
			for (int i = 0; i < Enemy_Max; i++) {
				if (Playerscale == Enemyscale[i]) {
					EnemyStop[i] = true;
				}
			}
		}
		static float speed = 3.0f;
		if (keys[KEY_INPUT_F]) {
			_playerPosX -= speed;
		}
		if (keys[KEY_INPUT_T]) {
			_playerPosY += speed;
		}
		if (keys[KEY_INPUT_H]) {
			_playerPosX += speed;
		}
		if (keys[KEY_INPUT_G]) {
			_playerPosY -= speed;
		}

		PlayerSpeed += add;

		if (PlayerSpeed == 360.0f || PlayerSpeed == -360.0f) {
			PlayerSpeed = 0.0f;
		}

		Playerradius = PlayerSpeed * PI / 180.0f;
		PlayerCircleX = cosf(Playerradius) * Playerscale;
		PlayerCircleY = sinf(Playerradius) * Playerscale;
		playerPosX = PlayerCircleX + x;
		playerPosY = PlayerCircleY + y;
		//�G�l�~�[
		for (int i = 0; i < Enemy_Max; i++) {
			if (!EnemyAlive[i]) {
				EnemyTimer[i]--;

				if (EnemyTimer[i] == 0) {
					Enemyscale[i] = rand() % 400 + 200;
					EnemySpeed[i] = rand() % 360;
					Enemyadd[i] = 1;
					TargetLine[i] = 4;
					EnemyAlive[i] = true;
					EnemyTimer[i] = rand() % 800;
					EnemySet[i] = true;
				}
			}

			if (EnemySet[i]) {
				if (TargetLine[i] == 0) {
					if (Enemyscale[i] >= 80.0f) {
						Enemyscale[i] -= 5.0f;
					}
					else {
						EnemySet[i] = false;
						EnemyMove[i] = true;
						EnemySaveSpeed[i] = EnemySpeed[i];
						Enemyscale[i] = 80.0f;
					}
				}
				else if (TargetLine[i] == 1) {
					if (Enemyscale[i] >= 120.0f) {
						Enemyscale[i] -= 5.0f;
					}
					else {
						EnemySet[i] = false;
						EnemyMove[i] = true;
						Enemyscale[i] = 120.0f;
					}
				}
				else if (TargetLine[i] == 2) {
					if (Enemyscale[i] >= 160.0f) {
						Enemyscale[i] -= 5.0f;
					}
					else {
						EnemySet[i] = false;
						EnemyMove[i] = true;
						EnemySaveSpeed[i] = EnemySpeed[i];
						Enemyscale[i] = 160.0f;
					}
				}
				else if (TargetLine[i] == 3) {
					if (Enemyscale[i] >= 200.0f) {
						Enemyscale[i] -= 5.0f;
					}
					else {
						EnemySet[i] = false;
						EnemyMove[i] = true;
						EnemySaveSpeed[i] = EnemySpeed[i];
						Enemyscale[i] = 200.0f;
					}
				}
				else if (TargetLine[i] == 4) {
					if (Enemyscale[i] >= 240.0f) {
						Enemyscale[i] -= 5.0f;
					}
					else {
						EnemySet[i] = false;
						EnemyMove[i] = true;
						EnemySaveSpeed[i] = EnemySpeed[i];
						Enemyscale[i] = 240.0f;
					}
				}
			}
		}

		for (int i = 0; i < Enemy_Max; i++) {
			if (EnemyMove[i]) {
				if (EnemySpeed[i] == EnemySaveSpeed[i] + 360.0f) {
					if (Enemyscale[i] > 41.0f) {
						Enemyscale[i] -= 40.0f;
					}
					EnemySpeed[i] = EnemySpeed[i] - 360.0f;
					EnemySaveSpeed[i] = EnemySpeed[i];
				}
			}
		}

		for (int i = 0; i < Enemy_Max; i++) {
			Enemyradius[i] = EnemySpeed[i] * PI / 180.0f;
			EnemyCircleX[i] = cosf(Enemyradius[i]) * Enemyscale[i];
			EnemyCircleY[i] = sinf(Enemyradius[i]) * Enemyscale[i];
			EnemyPosX[i] = EnemyCircleX[i] + x;
			EnemyPosY[i] = EnemyCircleY[i] + y;
			if (EnemyMove[i] && !EnemyStop[i]) {
				EnemySpeed[i] += Enemyadd[i];
			}

			if (EnemyStop[i]) {
				EnemyStopTimer[i]++;

				if (EnemyStopTimer[i] == 200) {
					EnemyStop[i] = false;
					EnemyStopTimer[i] = 0;
				}
			}
		}
		cameraTarget = Vector3(_playerPosX, _playerPosY, 0);
		SetCameraPositionAndTargetAndUpVec(
			cameraPosition,
			cameraTarget,
			cameraUp);

		DrawCone3D(VECTOR{ 0,0,0 }, VECTOR{ 0,10,0 }, 5, 1, GetColor(0, 255, 0), GetColor(255, 0, 0), true);
		//�`�揈��
		DrawCircle(x, y, 240, GetColor(255, 0, 0), false);
		DrawCircle(x, y, 200, GetColor(255, 0, 0), false);
		DrawCircle(x, y, 160, GetColor(0, 255, 0), false);
		DrawCircle(x, y, 120, GetColor(0, 0, 255), false);
		DrawCircle(x, y, 80, GetColor(0, 0, 255), false);
		DrawCircle(playerPosX, playerPosY, 10, GetColor(0, 0, 0), true);

		//DrawGraph3D(0, 0, 0, player, false);
		DrawBillboard3D(
			VGet(_playerPosX, _playerPosY, 0.0f),
			0.5f, 0.5f, 50.0f, 0.0f, player, TRUE);

		for (int i = 0; i < Enemy_Max; i++) {
			if (!EnemyStop[i]) {
				DrawCircle(EnemyPosX[i], EnemyPosY[i], 10, GetColor(255, 255, 0), true);
			}
			else {
				DrawCircle(EnemyPosX[i], EnemyPosY[i], 10, GetColor(0, 255, 255), true);
			}

			DrawFormatString(0, (20 * i) + 40, GetColor(0, 0, 0), "Save[%d]:%f", i, EnemySaveSpeed[i]);
			DrawFormatString(0, (20 * i) + 100, GetColor(0, 0, 0), "Speed[%d]:%f", i, EnemySpeed[i]);
			DrawFormatString(0, (20 * i) + 180, GetColor(0, 0, 0), "Timer[%d]:%d", i, EnemyStopTimer[i]);
		}
		DrawFormatString(0, 0, GetColor(0, 0, 0), "Speed:%f", PlayerSpeed);
		DrawFormatString(0, 20, GetColor(0, 0, 0), "add:%f", add);
		//---------  �����܂łɃv���O�������L�q  ---------//
		ScreenFlip();//�i�_�u���o�b�t�@�j����
		// 20�~���b�ҋ@�i�^��60FPS�j
		WaitTimer(20);
		// Windows �V�X�e�����炭�������������
		if (ProcessMessage() == -1)
		{
			break;
		}
		// �d�r�b�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	//Dx���C�u�����I������
	DxLib_End();

	return 0;
}