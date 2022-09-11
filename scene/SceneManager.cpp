#include "SceneManager.h"
#include "Vector3.h"

void SceneManager::StaticInit()
{
	int playerTex = LoadGraph("Resources/player.png");
	int targetTex = LoadGraph("Resources/TargetArea.png");
	
	int stageTex = LoadGraph("Resources/stage.png");
	gameBgm = LoadSoundMem("Resources/sound/gameBgm.mp3");

	//for (int i = 0; i < Enemy_Max; i++) {
	//	enemy[i] = new Enemy();
	//	enemy[i]->SetEnemyTex(enemyTex);
	//	enemy[i]->SetLinkEnemyTex(enemylinkTex);
	//	enemy[i]->SetEnemyStopTex(enemystopTex);
	//	enemy[i]->SetTargetEnemyTex(enemytargetTex);
	//}
	player = new Player();
	stagecircle = new StageCircle();
	score = new Score();
	score->SetPlayer(player);
	title = new Title();
	tutorial = new Tutorial();
	end = new End();

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
		SceneTime = 1;
		break;
	case static_cast<int>(SceneManager::NO::Tutorial):
		TutorialInit();
		SceneTime = 1;
		break;
	case static_cast<int>(SceneManager::NO::GameScene):
		GameSceneInit();
		SceneTime = 1;
		break;
	case static_cast<int>(SceneManager::NO::End):
		EndInit();
		SceneTime = 1;
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
		TitleUpdate(keys,oldkeys,input,oldinput);
		break;
	case static_cast<int>(SceneManager::NO::Tutorial):
		TutorialUpdate(keys, oldkeys, input, oldinput);
		SceneTime = 1;
		break;
	case static_cast<int>(SceneManager::NO::GameScene):
		GameSceneUpdate(keys, oldkeys, input, oldinput);
		break;
	case static_cast<int>(SceneManager::NO::End):
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
		DrawFormatString(0, 300, GetColor(0, 0, 0), "TITLE");
		TitleDraw();
		break;
	case static_cast<int>(SceneManager::NO::Tutorial):
		DrawFormatString(0, 300, GetColor(0, 0, 0), "TUTORIAL");
	/*	DrawFormatString(0, 320, GetColor(0, 0, 0), "BirthEnemyCount %d", BirthEnemyCount);
		DrawFormatString(0, 340, GetColor(0, 0, 0), "TutorialCount %d", TutorialCount);*/
		TutorialDraw();
		break;
	case static_cast<int>(SceneManager::NO::GameScene):
		DrawFormatString(0, 300, GetColor(0, 0, 0), "GAME");
		GameSceneDraw();
		break;
	case static_cast<int>(SceneManager::NO::End):
		DrawFormatString(0, 300, GetColor(0, 0, 0), "END");
		EndDraw();
		break;

	default:
		break;
	}
}

void SceneManager::TitleInit()
{
	title->Initialize();
	player->Initialize(title->GetVolume());
}

void SceneManager::TitleUpdate(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput)
{
	if (title->Update(input, oldinput) == true)
	{
		SceneTime = 0;
		TutorialInit();
		SceneNo = static_cast<int>(NO::Tutorial);
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

void SceneManager::TutorialInit()
{
	//score->Initialize();
	score->Initialize();
	tutorial->Initialize();
	//for (int i = 0; i < Enemy_Max; i++) {
	//	enemy[i]->Initialize();
	//}

}

void SceneManager::TutorialUpdate(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput)
{
	int enemyTex = LoadGraph("Resources/enemy.png");
	int enemystopTex = LoadGraph("Resources/enemystop.png");
	int enemylinkTex = LoadGraph("Resources/LinkArea.png");
	int enemytargetTex = LoadGraph("Resources/enemytarget.png");

	//特定のフレームで敵を生成する
	if (tutorial->GetTutorialTimer() == 520 || tutorial->GetTutorialTimer() == 480
		|| tutorial->GetTutorialTimer() == 450 || tutorial->GetTutorialTimer() == 330
		|| tutorial->GetTutorialTimer() == 320 || tutorial->GetTutorialTimer() == 310
		|| tutorial->GetTutorialTimer() == 250 || tutorial->GetTutorialTimer() == 230) {

		BirthEnemyCount++;
		EnemyArgment = true;
	}

	if (EnemyArgment) {
		unique_ptr<Enemy> newEnemy;
		newEnemy = make_unique<Enemy>();
		newEnemy->SetEnemyTex(enemyTex);
		newEnemy->SetLinkEnemyTex(enemylinkTex);
		newEnemy->SetEnemyStopTex(enemystopTex);
		newEnemy->SetTargetEnemyTex(enemytargetTex);
		newEnemy->TutorialInitialize();
		if (BirthEnemyCount == 1) {
			newEnemy->SetTargetLine(0);
			newEnemy->SetSpeed(358.0f);
		}
		else if (BirthEnemyCount == 2) {
			newEnemy->SetTargetLine(0);
			newEnemy->SetSpeed(180.0f);
		}
		else if (BirthEnemyCount == 3) {
			newEnemy->SetTargetLine(0);
			newEnemy->SetSpeed(160.0f);
		}
		else if (BirthEnemyCount == 4) {
			newEnemy->SetTargetLine(0);
			newEnemy->SetSpeed(200.0f);
		}
		else if (BirthEnemyCount == 5) {
			newEnemy->SetTargetLine(1);
			newEnemy->SetSpeed(220.0f);
		}
		else if (BirthEnemyCount == 6) {
			newEnemy->SetTargetLine(2);
			newEnemy->SetSpeed(240.0f);
		}
		else if (BirthEnemyCount == 7) {
			newEnemy->SetTargetLine(1);
			newEnemy->SetTutorialMove(true);
			newEnemy->SetSpeed(90.0f);
		}
		else if (BirthEnemyCount == 8) {
			newEnemy->SetTargetLine(2);
			newEnemy->SetTutorialMove(true);
			newEnemy->SetSpeed(270.0f);
		}
		enemy.push_back(std::move(newEnemy));
		EnemyArgment = false;
	}
	//最後のチュートリアルは二体同時に倒さないと進まない
	if (tutorial->GetTutorialNumber() == 4) {
		if (TutorialCount == 8) {
			if(player->GetKnockCount() == 2){
				tutorial->SetTutorialClear(true);
			}
			else {
				tutorial->SetTutorialClear(false);
				TutorialCount = 6;
				BirthEnemyCount = 6;
				tutorial->SetTutorialTimer(300);
			}
		}
	}

	if (tutorial->GetTutorialTimer() == 10) {
		//要素全削除
		enemy.clear();
	}
	//プレイヤー
	if (tutorial->GetTutorialTimer() > 0)
	{
		player->Update(keys, oldkeys, input, oldinput);
		for (unique_ptr<Enemy>& newEnemy : enemy) {
			if (newEnemy != nullptr) {
				newEnemy->TutorialUpdate(player);
				if (newEnemy->GetAttackArea()) {
					newEnemy->Target(player);
				}

				if (newEnemy->GetDeathEnemy()) {
					TutorialCount++;
					newEnemy->SetDeathEnemy(false);
				}
			}
		}
	}

	if (tutorial->Update(input, oldinput, TutorialCount) == true) {
		SceneTime = 0;
		GameSceneInit();
		SceneNo = static_cast<int>(NO::GameScene);
	}

	score->TutorialUpdate(keys, oldkeys, input, oldinput);

	/*if (score->Update(keys, oldkeys, input, oldinput) == true)
	{
		SceneTime = 0;
		EndInit();
		SceneNo = static_cast<int>(NO::End);
	}*/

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

void SceneManager::TutorialDraw()
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
	for (unique_ptr<Enemy>& newEnemy : enemy) {
		if (newEnemy != nullptr) {
			newEnemy->Draw();
			newEnemy->FormatDraw(2);
		}
	}

	ChangeVolumeSoundMem(title->GetVolume(), gameBgm);
	PlaySoundMem(gameBgm, DX_PLAYTYPE_LOOP);
	tutorial->Draw();

}


void SceneManager::GameSceneInit()
{
	score->Initialize();
}

void SceneManager::GameSceneUpdate(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput)
{
	int enemyTex = LoadGraph("Resources/enemy.png");
	int enemystopTex = LoadGraph("Resources/enemystop.png");
	int enemylinkTex = LoadGraph("Resources/LinkArea.png");
	int enemytargetTex = LoadGraph("Resources/enemytarget.png");

	//特定のフレームで敵を生成する
	if (score->GetGameTimer() == 900 || score->GetGameTimer() == 800) {
		BirthEnemyCount++;
		EnemyArgment = true;
	}

	if (EnemyArgment) {
		unique_ptr<Enemy> newEnemy;
		newEnemy = make_unique<Enemy>();
		newEnemy->SetEnemyTex(enemyTex);
		newEnemy->SetLinkEnemyTex(enemylinkTex);
		newEnemy->SetEnemyStopTex(enemystopTex);
		newEnemy->SetTargetEnemyTex(enemytargetTex);
		newEnemy->Initialize();
		if (BirthEnemyCount == 1) {
			newEnemy->SetSpeed(0.0f);
		}
		else if (BirthEnemyCount == 2) {
			newEnemy->SetSpeed(123.0f);
		}
		enemy.push_back(std::move(newEnemy));
		EnemyArgment = false;
	}
	//プレイヤー
	if (score->GetGameTimer() > 0)
	{
		player->Update(keys, oldkeys, input, oldinput);
		for (unique_ptr<Enemy>& newEnemy : enemy) {
			if (newEnemy != nullptr) {
				newEnemy->Update(player);
				if (newEnemy->GetAttackArea()) {
					newEnemy->Target(player);
				}
			}
		}
	}

	if (score->Update(keys, oldkeys, input, oldinput) == true)
	{
		SceneTime = 0;
		StopSoundMem(gameBgm);
		EndInit();
		SceneNo = static_cast<int>(NO::End);
	}

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
	//player->FormatDraw();

	//スコア
	score->Draw();
	//score->FormatDraw();
	//エネミー
	for (unique_ptr<Enemy>& newEnemy : enemy) {
		if (newEnemy != nullptr) {
			newEnemy->Draw();
			newEnemy->FormatDraw(2);
		}
	}
}

void SceneManager::EndInit()
{
	end->Initialize(title->GetVolume());
}

void SceneManager::EndUpdate(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput)
{
	//仮置き（次のシーンに行く）
	if (end->Update(input, oldinput) == true) {
		SceneTime = 0;
		TitleInit();
		SceneNo = static_cast<int>(NO::Title);
	}

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

void SceneManager::EndDraw()
{
	//描画処理
//ステージ上の円
	stagecircle->Draw();

	//プレイヤー
	player->Draw();
	//player->FormatDraw();

	//スコア
	score->Draw();
	//score->FormatDraw();
	//エネミー
}
