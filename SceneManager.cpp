#include "SceneManager.h"

void SceneManager::StaticInit()
{
	//画像などのリソースデータの変数宣言と読み込み


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
}

void SceneManager::TitleUpdate(char keys[255], char oldkeys[255])
{
	//仮置き（次のシーンに行く）
	if (keys[KEY_INPUT_N] == 1 && oldkeys[KEY_INPUT_N] == 0) {
		SceneTime = 0;
		SceneNo = static_cast<int>(NO::GameScene);
	}
}

void SceneManager::TitleDraw()
{
}

void SceneManager::GameSceneInit()
{
}

void SceneManager::GameSceneUpdate(char keys[255], char oldkeys[255])
{
	//更新処理
	//仮置き（次のシーンに行く）
	if (keys[KEY_INPUT_N] == 1 && oldkeys[KEY_INPUT_N] == 0) {
		SceneTime = 0;
		SceneNo = static_cast<int>(NO::End);
	}

	//プレイヤー
	player->Update(keys, oldkeys);
	//エネミー
	for (int i = 0; i < Enemy_Max; i++) {
		enemy[i]->Update(player);
	}
}

void SceneManager::GameSceneDraw()
{
	//描画処理
	//ステージ上の円
	stagecircle->Draw();

	//プレイヤー
	player->Draw();
	player->FormatDraw();

	//エネミー
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
	//仮置き（次のシーンに行く）
	if (keys[KEY_INPUT_N] == 1 && oldkeys[KEY_INPUT_N] == 0) {
		SceneTime = 0;
		SceneNo = static_cast<int>(NO::Title);
	}
}

void SceneManager::EndDraw()
{
}