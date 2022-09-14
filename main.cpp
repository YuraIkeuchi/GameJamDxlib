#include"SceneManager.h"
#include "Vector3.h"
#include"FPS.h"

const char TITLE[] = "3002_���[�T��";

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	ChangeWindowMode(TRUE);						//�E�B���h�E���[�h�ɐݒ�
	//�E�B���h�E�T�C�Y���蓮�ł͕ύX�ł����A���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetMainWindowText(TITLE);			
	SetWindowIconID(333);
	// �^�C�g����ύX
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);	//��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�i���j�^�[�̉𑜓x�ɍ��킹��j
	SetWindowSizeExtendRate(1.0);				//��ʃT�C�Y��ݒ�i�𑜓x�Ƃ̔䗦�Őݒ�j
	SetBackgroundColor(0xFF, 0xFF, 0xFF);		// ��ʂ̔w�i�F��ݒ肷��

	//Dx���C�u�����̏�����
	if (DxLib_Init() == -1) { return -1; }

	//�i�_�u���o�b�t�@�j�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	//�Q�[�����[�v�Ŏg���ϐ��̐錾
	char keys[256] = { 0 }; //�ŐV�̃L�[�{�[�h���p
	char oldkeys[256] = { 0 };//1���[�v�i�t���[���j�O�̃L�[�{�[�h���
	
	SceneManager *scene = new SceneManager;
	scene->StaticInit();

	struct XINPUT_STICK
	{
		unsigned char LeftTrigger; // ���g���K�[( 0�`255 )
		unsigned char RightTrigger; // �E�g���K�[( 0�`255 )
		short ThumbLX; // ���X�e�B�b�N�̉����l( -32768 �` 32767 )
		short ThumbLY; // ���X�e�B�b�N�̏c���l( -32768 �` 32767 )
		short ThumbRX; // �E�X�e�B�b�N�̉����l( -32768 �` 32767 )
		short ThumbRY; // �E�X�e�B�b�N�̏c���l( -32768 �` 32767 )
	};

	//�{�^��
	XINPUT_STATE input = { 0 };
	
	FPS fps(30.0f,800);

	// �Q�[�����[�v
	while (1)
	{
		//�ŐV�̃L�[�{�[�h��񂾂������̂͂P�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		for (int i = 0; i < 256; i++) {
			oldkeys[i] = keys[i];
		}
		//�ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);
		//�R���g���[���[���
		XINPUT_STATE oldinput = input;
		GetJoypadXInputState(DX_INPUT_PAD1, &input);

		//��ʃN���A
		ClearDrawScreen();
	
		//�J����
		Vector3 cameraOrgPosition(0.0f, 10.0f, -100.0f);
		Vector3 cameraPosition = cameraOrgPosition;

		Vector3 cameraOrgUp(0.0f, 1.0f, 0.0f);
		Vector3 cameraUp = cameraOrgUp;

		Vector3 cameraTarget(0.0f, 0.0f, 0.0f);

		float cameraUpAngle = 0.0f;

		//�N���b�v��
		SetCameraNearFar(1.0f, 10000.0f);
		SetCameraScreenCenter(WIN_WIDTH / 2.0f, WIN_HEIGHT / 2.0f);
		SetCameraPositionAndTargetAndUpVec(
			cameraPosition,
			cameraTarget,
			cameraUp);


		//---------  ��������v���O�������L�q  ----------//

		if (scene->GetSceneTime() == 0)
		{
			scene->Init();
		}
		scene->Update(keys, oldkeys, input, oldinput);
		scene->Draw();

		fps.getFps();
		fps.wait();
		//---------  �����܂łɃv���O�������L�q  ---------//
		ScreenFlip();//�i�_�u���o�b�t�@�j����
		// 20�~���b�ҋ@�i�^��60FPS�j
		//WaitTimer(20);
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
	delete scene;
	scene = nullptr;

	return 0;
}
