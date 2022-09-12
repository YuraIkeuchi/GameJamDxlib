#include "SceneManager.h"
#include "Vector3.h"

void SceneManager::StaticInit()
{
	int playerTex = LoadGraph("Resources/player.png");
	int targetTex = LoadGraph("Resources/TargetArea.png");
	int stageTex = LoadGraph("Resources/stage.png");
	gameBgm = LoadSoundMem("Resources/sound/gameBgm.mp3");
	filterTex = LoadGraph("Resources/filter.png");
	menuStopTex = LoadGraph("Resources/menuStop.png");
	newStartTex = LoadGraph("Resources/newStart.png");
	goTitleTex = LoadGraph("Resources/goTitle.png");
	removeTex = LoadGraph("Resources/remove.png");
	curTex = LoadGraph("Resources/title4.png");
	menuChangeSE = LoadSoundMem("Resources/sound/titleSound2.mp3");
	checkSE = LoadSoundMem("Resources/sound/titleSound3.mp3");

	//for (int i = 0; i < Enemy_Max; i++) {
	//	enemy[i] = new Enemy();
	//	enemy[i]->SetEnemyTex(enemyTex);
	//	enemy[i]->SetLinkEnemyTex(enemylinkTex);
	//	enemy[i]->SetEnemyStopTex(enemystopTex);
	//	enemy[i]->SetTargetEnemyTex(enemytargetTex);
	//}
	player = new Player();
	StageCircle* stagecircle_;
	stagecircle_ = new StageCircle();
	stagecircle.reset(stagecircle_);
	Score* score_;
	score_ = new Score();
	score_->SetPlayer(player);
	score.reset(score_);
	Title* title_;
	title_ = new Title();
	title.reset(title_);
	Tutorial* tutorial_;
	tutorial_ = new Tutorial();
	tutorial.reset(tutorial_);
	End* end_;
	end_ = new End();
	end.reset(end_);
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
		/*DrawFormatString(0, 320, GetColor(0, 0, 0), "BirthEnemyCount %d", BirthEnemyCount);
		DrawFormatString(0, 340, GetColor(0, 0, 0), "TutorialCount %d", TutorialCount);*/
		TutorialDraw();
		break;
	case static_cast<int>(SceneManager::NO::GameScene):
		DrawFormatString(0, 300, GetColor(0, 0, 0), "GAME");
		DrawFormatString(0, 320, GetColor(0, 0, 0), "BirthEnemyCount %d", BirthEnemyCount);
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
	int enemyrespornTex = LoadGraph("Resources/resporn.png");
	int enemytargetTex = LoadGraph("Resources/enemytarget.png");
	int enemystopTex = LoadGraph("Resources/enemystop.png");
	//特定のフレームで敵を生成する
	if (tutorial->GetTutorialTimer() == 321 || tutorial->GetTutorialTimer() == 316 || tutorial->GetTutorialTimer() == 311
		|| tutorial->GetTutorialTimer() == 306 || tutorial->GetTutorialTimer() == 150 || tutorial->GetTutorialTimer() == 145
		|| tutorial->GetTutorialTimer() == 140) {
		BirthEnemyCount++;
		EnemyArgment = true;
	}

	if (EnemyArgment) {
		unique_ptr<Enemy> newEnemy;
		newEnemy = make_unique<Enemy>();
		newEnemy->SetEnemyTex(enemyTex);
		newEnemy->SetRespornTex(enemyrespornTex);
		newEnemy->SetTargetEnemyTex(enemytargetTex);
		newEnemy->SetStopTex(enemystopTex);
		newEnemy->Initialize();
		if (BirthEnemyCount == 1) {
			newEnemy->SetTargetLine(0);
			newEnemy->SetTutorialMove(true);
			newEnemy->SetSpeed(0.0f);
		}
		else if (BirthEnemyCount == 2) {
			newEnemy->SetTargetLine(0);
			newEnemy->SetTutorialMove(true);
			newEnemy->SetSpeed(90.0f);
		}
		else if (BirthEnemyCount == 3) {
			newEnemy->SetTargetLine(0);
			newEnemy->SetTutorialMove(true);
			newEnemy->SetSpeed(180.0f);
		}
		else if (BirthEnemyCount == 4) {
			newEnemy->SetTargetLine(0);
			newEnemy->SetTutorialMove(true);
			newEnemy->SetSpeed(270.0f);
		}
		else if (BirthEnemyCount == 5) {
			newEnemy->SetTargetLine(0);
			newEnemy->SetTutorialMove(true);
			newEnemy->SetSpeed(180.0f);
		}
		else if (BirthEnemyCount == 6) {
			newEnemy->SetTargetLine(1);
			newEnemy->SetTutorialMove(true);
			newEnemy->SetSpeed(180.0f);
		}
		else if (BirthEnemyCount == 7) {
			newEnemy->SetTargetLine(2);
			newEnemy->SetTutorialMove(true);
			newEnemy->SetSpeed(180.0f);
		}
		enemy.push_back(std::move(newEnemy));
		EnemyArgment = false;
	}

	//最後のチュートリアルは三体同時に倒さないと進まない
	if (tutorial->GetTutorialNumber() == 2) {
		if (TutorialCount == 7) {
			if (player->GetKnockCount() == 3) {
				tutorial->SetTutorialClear(true);
			}
			else {
				tutorial->SetTutorialClear(false);
				TutorialCount = 4;
				BirthEnemyCount = 4;
				tutorial->SetTutorialTimer(200);
			}
		}
	}

	if (tutorial->GetDoorEnd()) {
		player->SetScale(320.0f);
		score->SetScorePoint(0);
		BirthEnemyCount = 0;
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

	//score->FormatDraw();
	//エネミー
	for (unique_ptr<Enemy>& newEnemy : enemy) {
		if (newEnemy != nullptr) {
			newEnemy->Draw(player);
			newEnemy->FormatDraw(2);
		}
	}


	//スコア
	score->Draw();
	ChangeVolumeSoundMem(title->GetVolume(), gameBgm);
	PlaySoundMem(gameBgm, DX_PLAYTYPE_LOOP);
	tutorial->Draw();

}


void SceneManager::GameSceneInit()
{
	score->Initialize();
	changeFlag = false;
	scale1 = 0.5f;
	scale2 = 0.5f;
	scale3 = 0.5f;
	curPosX = WIN_WIDTH / 2 - (300 * 0.5);
	curPosY = 380;
	ChangeVolumeSoundMem(title->GetVolume(), menuChangeSE);
	ChangeVolumeSoundMem(title->GetVolume(), checkSE);
}

void SceneManager::GameSceneUpdate(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput)
{
	//敵の生成
	if (changeFlag == false)
	{
		GameSceneEnemyArg();
		//プレイヤー
		if (score->GetGameTimer() > 0)
		{
			player->Update(keys, oldkeys, input, oldinput);
			for (unique_ptr<Enemy> &newEnemy : enemy) {
				if (newEnemy != nullptr) {
					newEnemy->Update(player);
					if (newEnemy->GetAttackArea()) {
						newEnemy->Target(player);
					}
				}
			}
		}

		//ゲーム終了
		if (score->Update(keys, oldkeys, input, oldinput) == true)
		{
			player->SetScale(320.0f);
			score->SetScorePoint(0);
			BirthEnemyCount = 0;
			//要素全削除
			enemy.clear();
			SceneTime = 0;
			StopSoundMem(gameBgm);
			EndInit();
			SceneNo = static_cast<int>(NO::End);
		}
	}

	if (input.Buttons[XINPUT_BUTTON_START] && !oldinput.Buttons[XINPUT_BUTTON_START])
	{
		changeFlag = true;
	}

	if (changeFlag == true)
	{
		if (input.Buttons[XINPUT_BUTTON_DPAD_UP] && !oldinput.Buttons[XINPUT_BUTTON_DPAD_UP] && curPosY >= 500) {
			curPosY -= 120;
			PlaySoundMem(menuChangeSE, DX_PLAYTYPE_BACK);
		}

		if (input.Buttons[XINPUT_BUTTON_DPAD_DOWN] && !oldinput.Buttons[XINPUT_BUTTON_DPAD_DOWN] && curPosY <= 500) {
			curPosY += 120;
			PlaySoundMem(menuChangeSE, DX_PLAYTYPE_BACK);
		}

		if (curPosY == 380)
		{
			scale1 = 0.7f;
			scale2 = 0.5f;
			scale3 = 0.5f;

			if (input.Buttons[XINPUT_BUTTON_A] && !oldinput.Buttons[XINPUT_BUTTON_A]) {
				GameSceneInit();
				player->Initialize(title->GetVolume());
				enemy.clear();
				BirthEnemyCount = 0;
				PlaySoundMem(checkSE, DX_PLAYTYPE_BACK);
			}
		}
		if (curPosY == 500)
		{
			scale1 = 0.5f;
			scale2 = 0.7f;
			scale3 = 0.5f;
			if (input.Buttons[XINPUT_BUTTON_A] && !oldinput.Buttons[XINPUT_BUTTON_A]) {
				PlaySoundMem(checkSE, DX_PLAYTYPE_BACK);
				StopSoundMem(gameBgm);
				TitleInit();
				BirthEnemyCount = 0;
				//要素全削除
				enemy.clear();
				SceneNo = static_cast<int>(NO::Title);
			}
		}
		if (curPosY == 620)
		{
			scale1 = 0.5f;
			scale2 = 0.5f;
			scale3 = 0.7f;

			if (input.Buttons[XINPUT_BUTTON_A] && !oldinput.Buttons[XINPUT_BUTTON_A]) {
				PlaySoundMem(checkSE, DX_PLAYTYPE_BACK);
				curPosY = 500;
				changeFlag = false;
			}
		}

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
	player->FormatDraw();

	//score->FormatDraw();
	//エネミー
	for (unique_ptr<Enemy>& newEnemy : enemy) {
		if (newEnemy != nullptr) {
			newEnemy->Draw(player);
			newEnemy->FormatDraw(2);
		}
	}

	//スコア
	score->Draw();
	if (changeFlag == true)
	{
		//スコア
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawGraph(0, 0, filterTex, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawRotaGraph(WIN_WIDTH / 2 , 200, 1.3f, 0.0f, menuStopTex, TRUE);
		DrawRotaGraph(WIN_WIDTH / 2, 380, scale1, 0.0f, newStartTex, TRUE);
		DrawRotaGraph(WIN_WIDTH / 2, 500, scale2, 0.0f, goTitleTex, TRUE);
		DrawRotaGraph(WIN_WIDTH / 2, 620, scale3, 0.0f, removeTex, TRUE);
		DrawRotaGraph(curPosX, curPosY, 0.5f, 0.0f, curTex, TRUE);
	}
}

void SceneManager::GameSceneEnemyArg() {

	int enemyTex = LoadGraph("Resources/enemy.png");
	int enemyrespornTex = LoadGraph("Resources/resporn.png");
	int enemytargetTex = LoadGraph("Resources/enemytarget.png");
	int enemystopTex = LoadGraph("Resources/enemystop.png");
	//特定のフレームで敵を生成する
	if (score->GetGameTimer() == 3520 || score->GetGameTimer() == 3500 || score->GetGameTimer() == 3480
		|| score->GetGameTimer() == 3460 || score->GetGameTimer() == 3100 || score->GetGameTimer() == 3000
		|| score->GetGameTimer() == 2900 || score->GetGameTimer() == 2800 || score->GetGameTimer() == 2700//9
		|| score->GetGameTimer() == 2500 || score->GetGameTimer() == 2450 || score->GetGameTimer() == 2400
		|| score->GetGameTimer() == 2350 || score->GetGameTimer() == 2300 || score->GetGameTimer() == 2250
		|| score->GetGameTimer() == 2200 || score->GetGameTimer() == 2150 || score->GetGameTimer() == 2100
		|| score->GetGameTimer() == 2050 || score->GetGameTimer() == 2000 || score->GetGameTimer() == 1980//21
		|| score->GetGameTimer() == 1500 || score->GetGameTimer() == 1450 || score->GetGameTimer() == 1400
		|| score->GetGameTimer() == 1300 || score->GetGameTimer() == 1250 || score->GetGameTimer() == 1200
		|| score->GetGameTimer() == 1100 || score->GetGameTimer() == 1050 || score->GetGameTimer() == 1000
		|| score->GetGameTimer() == 900 || score->GetGameTimer() == 850 || score->GetGameTimer() == 800//30
		) {
		BirthEnemyCount++;
		EnemyArgment = true;
	}

	if (EnemyArgment) {
		unique_ptr<Enemy> newEnemy;
		newEnemy = make_unique<Enemy>();
		newEnemy->SetEnemyTex(enemyTex);
		newEnemy->SetRespornTex(enemyrespornTex);
		newEnemy->SetTargetEnemyTex(enemytargetTex);
		newEnemy->SetStopTex(enemystopTex);
		newEnemy->Initialize();
		if (BirthEnemyCount == 1) {
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(RIGHT);
			newEnemy->SetSpeed(0.0f);
		}
		else if (BirthEnemyCount == 2) {
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(RIGHT);
			newEnemy->SetSpeed(90.0f);
		}
		else if (BirthEnemyCount == 3) {
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(RIGHT);
			newEnemy->SetSpeed(180.0f);
		}
		else if (BirthEnemyCount == 4) {
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(RIGHT);
			newEnemy->SetSpeed(270.0f);
		}
		else if (BirthEnemyCount == 5) {
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(LEFT);
			newEnemy->SetSpeed(0.0f);
		}
		else if (BirthEnemyCount == 6) {
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(LEFT);
			newEnemy->SetSpeed(30.0f);
		}
		else if (BirthEnemyCount == 7) {
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(LEFT);
			newEnemy->SetSpeed(60.0f);
		}
		else if (BirthEnemyCount == 8) {
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(LEFT);
			newEnemy->SetSpeed(90.0f);
		}
		else if (BirthEnemyCount == 9) {
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(LEFT);
			newEnemy->SetSpeed(120.0f);
		}
		else if (BirthEnemyCount == 10) {
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(RIGHT);
			newEnemy->SetSpeed(0.0f);
		}
		else if (BirthEnemyCount == 11) {
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(RIGHT);
			newEnemy->SetSpeed(20.0f);
		}
		else if (BirthEnemyCount == 12) {
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(RIGHT);
			newEnemy->SetSpeed(40.0f);
		}
		else if (BirthEnemyCount == 13) {
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(LEFT);
			newEnemy->SetSpeed(90.0f);
		}
		else if (BirthEnemyCount == 14) {
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(LEFT);
			newEnemy->SetSpeed(110.0f);
		}
		else if (BirthEnemyCount == 15) {
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(LEFT);
			newEnemy->SetSpeed(130.0f);
		}
		else if (BirthEnemyCount == 16) {
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(RIGHT);
			newEnemy->SetSpeed(180.0f);
		}
		else if (BirthEnemyCount == 17) {
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(RIGHT);
			newEnemy->SetSpeed(200.0f);
		}
		else if (BirthEnemyCount == 18) {
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(RIGHT);
			newEnemy->SetSpeed(220.0f);
		}
		else if (BirthEnemyCount == 19) {
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(LEFT);
			newEnemy->SetSpeed(270.0f);
		}
		else if (BirthEnemyCount == 20) {
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(LEFT);
			newEnemy->SetSpeed(290.0f);
		}
		else if (BirthEnemyCount == 21) {
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(LEFT);
			newEnemy->SetSpeed(310.0f);
		}
		else if (BirthEnemyCount == 22) {
		newEnemy->SetTargetLine(2);
		newEnemy->SetDir(RIGHT);
		newEnemy->SetSpeed(40.0f);
		}
		else if (BirthEnemyCount == 23) {
		newEnemy->SetTargetLine(1);
		newEnemy->SetDir(RIGHT);
		newEnemy->SetSpeed(40.0f);
		}
		else if (BirthEnemyCount == 24) {
		newEnemy->SetTargetLine(0);
		newEnemy->SetDir(RIGHT);
		newEnemy->SetSpeed(40.0f);
		}
		else if (BirthEnemyCount == 25) {
		newEnemy->SetTargetLine(2);
		newEnemy->SetDir(LEFT);
		newEnemy->SetSpeed(220.0f);
		}
		else if (BirthEnemyCount == 26) {
		newEnemy->SetTargetLine(1);
		newEnemy->SetDir(LEFT);
		newEnemy->SetSpeed(220.0f);
		}
		else if (BirthEnemyCount == 27) {
		newEnemy->SetTargetLine(0);
		newEnemy->SetDir(LEFT);
		newEnemy->SetSpeed(220.0f);
		}
		else if (BirthEnemyCount == 28) {
		newEnemy->SetTargetLine(3);
		newEnemy->SetDir(RIGHT);
		newEnemy->SetSpeed(0.0f);
		}
		else if (BirthEnemyCount == 29) {
		newEnemy->SetTargetLine(3);
		newEnemy->SetDir(RIGHT);
		newEnemy->SetSpeed(120.0f);
		}
		else if (BirthEnemyCount == 30) {
		newEnemy->SetTargetLine(3);
		newEnemy->SetDir(RIGHT);
		newEnemy->SetSpeed(240.0f);
		}
		enemy.push_back(std::move(newEnemy));
		EnemyArgment = false;
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

	////プレイヤー
	player->Draw();
	////player->FormatDraw();

	////スコア
	//score->Draw();
	end->Draw(score->GetScorePoint());
	//score->FormatDraw();
	//エネミー
}
