#pragma once
#include"Player.h"
#include"Enemy.h"
#include "Score.h"
#include"StageCircle.h"
#include "math.h"
#include<time.h>
#include "DxLib.h"
#include"Title.h"
#include"End.h"
#include "Tutorial.h"
#include <vector>
#include <memory>
#include <list> // �w�b�_�t�@�C���C���N���[�h
using namespace std;         //  ���O��Ԏw��
class SceneManager
{
private:
	//�Œ�l
	static const int Enemy_Max = 10;
private:
	//�V�[���̎��
	enum class NO
	{
		Title,
		Tutorial,
		GameScene,
		End,
	};

	//���݂̃V�[���̔ԍ�
	int SceneNo = static_cast<int>(NO::Title);
	//�������̂��߂̌v��
	int SceneTime = 0;
#pragma region �V�[�����Ƃ̏���
	void TitleInit();
	void TitleUpdate(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput);
	void TitleDraw();

	void TutorialInit();
	void TutorialUpdate(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput);
	void TutorialDraw();

	void GameSceneInit();
	void GameSceneUpdate(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput);
	void GameSceneDraw();

	void EndInit();
	void EndUpdate(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput);
	void EndDraw();

	//�N���X�錾
	// 	//�G�l�~�[
	vector<unique_ptr<Enemy>>enemy;
	bool EnemyArgment = false;
	//�v���C���[
	Player *player = nullptr;
	//�X�e�[�W��̉~
	StageCircle *stagecircle = nullptr;
	//�^�C�g���̓���
	Title *title = nullptr;
	//�`���[�g���A���̓���
	Tutorial* tutorial = nullptr;
	//�G���h�̓���
	End *end = nullptr;
	//�X�R�A
	Score* score = nullptr;
	float x = WIN_WIDTH / 2;
	float y = WIN_HEIGHT / 2;
	int BirthEnemyCount = 0;
	int TutorialCount = 0;
public:
	//�ŏ��ɏ������������
	void StaticInit();
	//�V�[����؂�ւ��邽�тɏ������������
	void Init();
	//Update
	void Update(char keys[255], char oldkeys[255],XINPUT_STATE input, XINPUT_STATE oldinput);
	//Draw
	void Draw();

public:
	//getter
	const int &GetSceneTime() { return SceneTime; }
};
