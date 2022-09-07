#include "SceneManager.h"
#include "Vector3.h"

void SceneManager::StaticInit()
{
	//画像などのリソースデータの変数宣言と読み込み
	int playerTex = LoadGraph("player.png");
	int enemyTex = LoadGraph("player.png");
	int stageTex = LoadGraph("stage.png");

	for (int i = 0; i < Enemy_Max; i++) {
		enemy[i] = new Enemy();
		enemy[i]->SetEnemyTex(enemyTex);
	}
	player = new Player();
	stagecircle = new StageCircle();

	player->SetPlayer(playerTex);
	stagecircle->SetTexture(stageTex);
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
	//仮置き（次のシーンに行く）
	if (keys[KEY_INPUT_N] == 1 && oldkeys[KEY_INPUT_N] == 0) {
		SceneTime = 0;
		SceneNo = static_cast<int>(NO::GameScene);
	}

	//プレイヤー
	player->Update(keys, oldkeys);
}

void SceneManager::TitleDraw()
{
	//描画処理
	//ステージ上の円
	stagecircle->Draw();

	//プレイヤー
	player->Draw();
}

void SceneManager::GameSceneInit()
{
	player->Initialize();
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

	for (int i = 0; i < Enemy_Max; i++) {
		if (enemy[i]->GetAttackArea()) {
			enemy[i]->Target(player);
			break;
		}
	}

	Vector3 cameraOrgPosition(player->GetPositionX(),player->GetPositionY(), 400.0f);
	Vector3 cameraPosition = cameraOrgPosition;

	Vector3 cameraOrgUp(0.0f, 1.0f, 0.0f);
	Vector3 cameraUp = cameraOrgUp;

	Vector3 cameraTarget(player->GetPositionX(), player->GetPositionY(), 0.0f);

	float cameraUpAngle = 0.0f;

	//クリップ面
	SetCameraNearFar(1.0f, 10000.0f);
	SetCameraScreenCenter(WIN_WIDTH / 2.0f, WIN_HEIGHT / 2.0f);
	SetCameraPositionAndTargetAndUpVec(
		cameraPosition,
		cameraTarget,
		cameraUp);

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