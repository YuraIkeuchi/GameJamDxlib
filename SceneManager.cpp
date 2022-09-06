#include "SceneManager.h"

void SceneManager::StaticInit()
{
	//�摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���


	for (int i = 0; i < Enemy_Max; i++) {
		enemy[i] = new Enemy();
	}
	player = new Player();
	stagecircle = new StageCircle();
	srand(time(NULL));
}

void SceneManager::Init()
{
	switch (SceneNo)
	{
	case static_cast<int>(SceneManager::NO::Title):
		TitleInit();
		break;
	case static_cast<int>(SceneManager::NO::GameScene):
		GameSceneInit();
		break;
	case static_cast<int>(SceneManager::NO::End):
		EndInit();
		break;

	default:
		break;
	}
}

void SceneManager::Update(char keys[255], char oldkeys[255])
{
	switch (SceneNo)
	{
	case static_cast<int>(SceneManager::NO::Title):
		SceneTime = 1;
		TitleUpdate(keys,oldkeys);
		break;
	case static_cast<int>(SceneManager::NO::GameScene):
		SceneTime = 1;
		GameSceneUpdate(keys, oldkeys);
		break;
	case static_cast<int>(SceneManager::NO::End):
		SceneTime = 1;
		EndUpdate(keys, oldkeys);
		break;

	default:
		break;
	}
}

void SceneManager::Draw()
{
	switch (SceneNo)
	{
	case static_cast<int>(SceneManager::NO::Title):
		TitleDraw();
		break;
	case static_cast<int>(SceneManager::NO::GameScene):
		GameSceneDraw();
		break;
	case static_cast<int>(SceneManager::NO::End):
		EndDraw();
		break;

	default:
		break;
	}
}

void SceneManager::TitleInit()
{
	player->Initialize();
}

void SceneManager::TitleUpdate(char keys[255], char oldkeys[255])
{
	//���u���i���̃V�[���ɍs���j
	if (keys[KEY_INPUT_N] == 1 && oldkeys[KEY_INPUT_N] == 0) {
		SceneTime = 0;
		SceneNo = static_cast<int>(NO::GameScene);
	}

	//�v���C���[
	player->Update(keys, oldkeys);
}

void SceneManager::TitleDraw()
{
	//�`�揈��
	//�X�e�[�W��̉~
	stagecircle->Draw();

	//�v���C���[
	player->Draw();
}

void SceneManager::GameSceneInit()
{
	player->Initialize();
}

void SceneManager::GameSceneUpdate(char keys[255], char oldkeys[255])
{
	//�X�V����
	//���u���i���̃V�[���ɍs���j
	if (keys[KEY_INPUT_N] == 1 && oldkeys[KEY_INPUT_N] == 0) {
		SceneTime = 0;
		SceneNo = static_cast<int>(NO::End);
	}

	//�v���C���[
	player->Update(keys, oldkeys);
	//�G�l�~�[
	for (int i = 0; i < Enemy_Max; i++) {
		enemy[i]->Update(player);
	}

	for (int i = 0; i < Enemy_Max; i++) {
		if (enemy[i]->GetAttackArea()) {
			enemy[i]->Target(player);
			break;
		}
	}
}

void SceneManager::GameSceneDraw()
{
	//�`�揈��
	//�X�e�[�W��̉~
	stagecircle->Draw();

	//�v���C���[
	player->Draw();
	player->FormatDraw();

	//�G�l�~�[
	for (int i = 0; i < Enemy_Max; i++) {
		enemy[i]->Draw();
		enemy[i]->FormatDraw(i);
	}


}

void SceneManager::EndInit()
{
}

void SceneManager::EndUpdate(char keys[255], char oldkeys[255])
{
	//���u���i���̃V�[���ɍs���j
	if (keys[KEY_INPUT_N] == 1 && oldkeys[KEY_INPUT_N] == 0) {
		SceneTime = 0;
		SceneNo = static_cast<int>(NO::Title);
	}
}

void SceneManager::EndDraw()
{
}