#include "SceneManager.h"
#include "Vector3.h"

void SceneManager::StaticInit()
{


	int playerTex = LoadGraph("Resources/player.png");
	int targetTex = LoadGraph("Resources/TargetArea.png");
	int enemyTex = LoadGraph("Resources/enemy.png");
	int enemystopTex = LoadGraph("Resources/enemystop.png");
	int enemylinkTex = LoadGraph("Resources/LinkArea.png");
	int enemytargetTex = LoadGraph("Resources/enemytarget.png");
	int stageTex = LoadGraph("Resources/stage.png");

	for (int i = 0; i < Enemy_Max; i++) {
		enemy[i] = new Enemy();
		enemy[i]->SetEnemyTex(enemyTex);
		enemy[i]->SetLinkEnemyTex(enemylinkTex);
		enemy[i]->SetEnemyStopTex(enemystopTex);
		enemy[i]->SetTargetEnemyTex(enemytargetTex);
	}
	player = new Player();
	stagecircle = new StageCircle();
	score = new Score();
	score->SetPlayer(player);
	title = new Title();

	player->SetPlayer(playerTex);
	player->SetTargetArea(targetTex);
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

void SceneManager::Update(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput)
{
	switch (SceneNo)
	{
	case static_cast<int>(SceneManager::NO::Title):
		SceneTime = 1;
		TitleUpdate(keys,oldkeys,input,oldinput);
		break;
	case static_cast<int>(SceneManager::NO::GameScene):
		SceneTime = 1;
		GameSceneUpdate(keys, oldkeys, input, oldinput);
		break;
	case static_cast<int>(SceneManager::NO::End):
		SceneTime = 1;
		EndUpdate(keys, oldkeys, input, oldinput);
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
	score->Initialize();
	title->Initialize();
}

void SceneManager::TitleUpdate(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput)
{
	if (title->Update(input, oldinput) == true)
	{
		SceneTime = 0;
		SceneNo = static_cast<int>(NO::GameScene);
	}
	//プレイヤー
	player->Update(keys, oldkeys, input, oldinput);

	Vector3 cameraOrgPosition(player->GetPositionX(), player->GetPositionY(), 500.0f);
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

void SceneManager::TitleDraw()
{
	//描画処理
	//ステージ上の円
	stagecircle->Draw();

	//プレイヤー
	player->Draw();

	//タイトル
	title->Draw();

}

void SceneManager::GameSceneInit()
{
	player->Initialize();
	score->Initialize();
	for (int i = 0; i < Enemy_Max; i++) {
		enemy[i]->Initialize();
	}

}

void SceneManager::GameSceneUpdate(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput)
{
	//更新処理
	//仮置き（次のシーンに行く）
	if (score->GetGameTimer() <= 0) {
		SceneTime = 0;
		SceneNo = static_cast<int>(NO::End);
	}

	//プレイヤー
	player->Update(keys, oldkeys, input, oldinput);
	//エネミー
	for (int i = 0; i < Enemy_Max; i++) {
		enemy[i]->Update(player);
		if (enemy[i]->GetAttackArea()) {
			enemy[i]->Target(player);
		}
	}

	score->Update();

	Vector3 cameraOrgPosition(player->GetPositionX(),player->GetPositionY(), 500.0f);
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

	//スコア
	score->Draw();
	score->FormatDraw();
	//エネミー
	for (int i = 0; i < Enemy_Max; i++) {
		enemy[i]->Draw();
		enemy[i]->FormatDraw(i);
	}


}

void SceneManager::EndInit()
{
}

void SceneManager::EndUpdate(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput)
{
	//仮置き（次のシーンに行く）
	if (input.Buttons[XINPUT_BUTTON_A] && !oldinput.Buttons[XINPUT_BUTTON_A]) {
		SceneTime = 0;
		SceneNo = static_cast<int>(NO::Title);
	}
}

void SceneManager::EndDraw()
{
}