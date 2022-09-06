#pragma once
#include"Player.h"
#include"Enemy.h"
#include"StageCircle.h"
#include "math.h"
#include<time.h>
#include "DxLib.h"

class SceneManager
{
private:
	//�Œ�l
	static const int Enemy_Max = 5;
private:
	//�V�[���̎��
	enum class NO
	{
		Title,
		GameScene,
		End,
	};

	//���݂̃V�[���̔ԍ�
	int SceneNo = static_cast<int>(NO::GameScene);
	//�������̂��߂̌v��
	int SceneTime = 0;
#pragma region �V�[�����Ƃ̏���
	void TitleInit();
	void TitleUpdate(char keys[255], char oldkeys[255]);
	void TitleDraw();

	void GameSceneInit();
	void GameSceneUpdate(char keys[255], char oldkeys[255]);
	void GameSceneDraw();

	void EndInit();
	void EndUpdate(char keys[255], char oldkeys[255]);
	void EndDraw();

	//�N���X�錾
	// 	//�G�l�~�[
	Enemy *enemy[Enemy_Max];
	//�v���C���[
	Player *player = nullptr;
	//�X�e�[�W��̉~
	StageCircle *stagecircle = nullptr;

	float x = WIN_WIDTH / 2;
	float y = WIN_HEIGHT / 2;


public:
	//�ŏ��ɏ������������
	void StaticInit();
	//�V�[����؂�ւ��邽�тɏ������������
	void Init();
	//Update
	void Update(char keys[255], char oldkeys[255]);
	//Draw
	void Draw();

public:
	//getter
	const int &GetSceneTime() { return SceneTime; }
};