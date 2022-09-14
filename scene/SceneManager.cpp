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
	enemyTex = LoadGraph("Resources/enemy.png");
	enemyrespornTex = LoadGraph("Resources/resporn.png");
	enemytargetTex = LoadGraph("Resources/enemytarget.png");
	enemystopTex = LoadGraph("Resources/enemystop.png");
	startTex = LoadGraph("Resources/start.png");

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

	SceneChange* scenechange_;
	scenechange_ = new SceneChange();
	scenechange.reset(scenechange_);
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
		//DrawFormatString(0, 300, GetColor(0, 0, 0), "TITLE");
		TitleDraw();
		break;
	case static_cast<int>(SceneManager::NO::Tutorial):
		//DrawFormatString(0, 300, GetColor(0, 0, 0), "TUTORIAL");
		//DrawFormatString(0, 340, GetColor(0, 0, 0), "TutorialCount %d", TutorialCount);
		/*
		*/
		TutorialDraw();
		break;
	case static_cast<int>(SceneManager::NO::GameScene):
		//DrawFormatString(0, 320, GetColor(0, 0, 0), "BirthEnemyCount %d", BirthEnemyCount);
		//DrawFormatString(0, 300, GetColor(0, 0, 0), "GAME");
		//DrawFormatString(0, 320, GetColor(0, 0, 0), "BirthEnemyCount %d", BirthEnemyCount);
		GameSceneDraw();
		break;
	case static_cast<int>(SceneManager::NO::End):
		//DrawFormatString(0, 300, GetColor(0, 0, 0), "END");
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
	player->SetSound(false);
	BGMLOOP = false;
}

void SceneManager::TitleUpdate(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput)
{
	if (title->Update(input, oldinput) == true)
	{
		TutorialCount = 0;
		SceneTime = 0;
		TutorialInit();
		SceneNo = static_cast<int>(NO::Tutorial);
	}
	//プレイヤー
	player->Update(keys, oldkeys, input, oldinput);
	//シーンチェンジ
	scenechange->Update();

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

	//シーンチェンジ
	scenechange->Draw();
}

void SceneManager::TutorialInit()
{
	score->Initialize();
	tutorial->Initialize();
	/*ChangeVolumeSoundMem(title->GetVolume(), gameBgm);
	PlaySoundMem(gameBgm, DX_PLAYTYPE_LOOP);*/
	scenechange->Initialize();
	player->SetSound(true);
	ResetTutorial = true;
	ChangeStart = false;
	ChangeVolumeSoundMem(title->GetVolume(), checkSE);
}

void SceneManager::TutorialUpdate(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput)
{


	//BGM
	if (!BGMLOOP) {
		ChangeVolumeSoundMem(title->GetVolume(), gameBgm);
		PlaySoundMem(gameBgm, DX_PLAYTYPE_LOOP);
		BGMLOOP = true;
	}
	//特定のフレームで敵を生成する
	if (tutorial->GetTutorialTimer() == 321 || tutorial->GetTutorialTimer() == 316 || tutorial->GetTutorialTimer() == 311
		|| tutorial->GetTutorialTimer() == 150 || tutorial->GetTutorialTimer() == 145 || tutorial->GetTutorialTimer() == 140
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
			newEnemy->SetTutorialMove(true);
			newEnemy->Pattern(0.0f, 0, RIGHT);
		}
		else if (BirthEnemyCount == 2) {
			newEnemy->SetTutorialMove(true);
			newEnemy->Pattern(90.0f, 0, RIGHT);
		}
		else if (BirthEnemyCount == 3) {
			newEnemy->SetTutorialMove(true);
			newEnemy->Pattern(180.0f, 1, RIGHT);
		}
		else if (BirthEnemyCount == 4) {
			newEnemy->SetTutorialMove(true);
			newEnemy->Pattern(180.0f, 1, RIGHT);
		}
		else if (BirthEnemyCount == 5) {
			newEnemy->SetTutorialMove(true);
			newEnemy->Pattern(180.0f, 2, RIGHT);
		}
		else if (BirthEnemyCount == 6) {
			newEnemy->SetTutorialMove(true);
			newEnemy->Pattern(180.0f, 3, RIGHT);
		}
		enemy.push_back(std::move(newEnemy));
		EnemyArgment = false;
	}

	//最後のチュートリアルは三体同時に倒さないと進まない
	if (tutorial->GetTutorialNumber() == 2) {
		if (!player->GetAttackStart() && TutorialCount != 3) {
			
			if (TutorialCount == 6) {
				tutorial->SetTutorialClear(true);
			}
			else {
				if (!ChangeStart) {
					scenechange->SetdoorStart(true);
					scenechange->Setdoorframe(0.0f);
					ChangeStart = true;
				}
				ResetTutorial = true;
			}
		}
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

	//チュートリアル
	if (input.Buttons[XINPUT_BUTTON_Y] && !oldinput.Buttons[XINPUT_BUTTON_Y]) {
		ResetTutorial = false;
		if (!ChangeStart) {
			scenechange->SetdoorStart(true);
			scenechange->Setdoorframe(0.0f);
			ChangeStart = true;
			PlaySoundMem(checkSE, DX_PLAYTYPE_BACK);
		}
	}
	if (tutorial->GetTutorialNumber() == 3 && tutorial->GetTextCheck() && tutorial->GetTutorialCheck()) {
		if (!scenechange->GetDoorStart()) {
			ResetTutorial = false;
			if (!ChangeStart) {
				scenechange->SetdoorStart(true);
				scenechange->Setdoorframe(0.0f);
				ChangeStart = true;
			}
		}
	}

	if (scenechange->GetChange()) {
		//チュートリアルクリア
		if (!ResetTutorial) {
			player->SetScale(320.0f);
			score->SetScorePoint(0);
			BirthEnemyCount = 0;
			//要素全削除
			enemy.clear();
			SceneTime = 0;
			GameSceneInit();
			SceneNo = static_cast<int>(NO::GameScene);
			ChangeStart = false;
		}
		//やり直し
		else {
			player->SetScale(240.0f);
			enemy.clear();
			tutorial->SetTutorialClear(false);
			TutorialCount = 3;
			BirthEnemyCount = 3;
			tutorial->SetTutorialTimer(200);
			ChangeStart = false;
		}
		scenechange->SetChange(false);
	}

	tutorial->Update(input, oldinput, TutorialCount);
	score->TutorialUpdate(keys, oldkeys, input, oldinput);
	scenechange->Update();

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
	//player->FormatDraw();

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

	if (!scenechange->GetDoorEnd() || ResetTutorial) {
		tutorial->Draw();
	}
	scenechange->Draw();
}


void SceneManager::GameSceneInit()
{
	score->Initialize();
	scenechange->Initialize();
	player->SetSound(true);
	player->SetSpeed(0.0f);
	changeFlag = false;
	ChangeStart = false;
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
	}

	if (input.Buttons[XINPUT_BUTTON_START] && !oldinput.Buttons[XINPUT_BUTTON_START] && changeFlag == false)
	{
		changeFlag = true;
		PlaySoundMem(checkSE, DX_PLAYTYPE_BACK);
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

		//リスタート
		if (curPosY == 380)
		{
			scale1 = 0.7f;
			scale2 = 0.5f;
			scale3 = 0.5f;

			if (input.Buttons[XINPUT_BUTTON_A] && !oldinput.Buttons[XINPUT_BUTTON_A]) {
				scenechange->SetdoorStart(true);
				scenechange->Setdoorframe(0.0f);
				ChangeNumber = RESTART;
			}
		}
		//タイトル
		if (curPosY == 500)
		{
			scale1 = 0.5f;
			scale2 = 0.7f;
			scale3 = 0.5f;
			if (input.Buttons[XINPUT_BUTTON_A] && !oldinput.Buttons[XINPUT_BUTTON_A]) {
				scenechange->SetdoorStart(true);
				scenechange->Setdoorframe(0.0f);
				ChangeNumber = TITLE;
			}
		}
		if (curPosY == 620)
		{
			scale1 = 0.5f;
			scale2 = 0.5f;
			scale3 = 0.7f;

			if (input.Buttons[XINPUT_BUTTON_A] && !oldinput.Buttons[XINPUT_BUTTON_A]) {
				PlaySoundMem(checkSE, DX_PLAYTYPE_BACK);
				curPosY = 380;
				changeFlag = false;
			}
		}
	}

	//ゲーム終了
	if (score->Update(keys, oldkeys, input, oldinput) == true)
	{
		player->SetAttackInterval(0);
		player->SetAttackStart(false);
		player->SetScale(320.0f);
		BirthEnemyCount = 0;
		//要素全削除
		enemy.clear();
		SceneTime = 0;
		StopSoundMem(gameBgm);
		EndInit();
		SceneNo = static_cast<int>(NO::End);
	}
	if (ChangeNumber == RESTART) {
		if (scenechange->GetChange()) {
			GameSceneInit();
			player->Initialize(title->GetVolume());
			enemy.clear();
			BirthEnemyCount = 0;
			PlaySoundMem(checkSE, DX_PLAYTYPE_BACK);
			ChangeNumber = NO;
			scenechange->SetChange(false);
		}
	}
	else if (ChangeNumber == TITLE) {
		if (scenechange->GetChange()) {
			PlaySoundMem(checkSE, DX_PLAYTYPE_BACK);
			StopSoundMem(gameBgm);
			TitleInit();
			BirthEnemyCount = 0;
			//要素全削除
			enemy.clear();
			SceneNo = static_cast<int>(NO::Title);
			ChangeNumber = NO;
			scenechange->SetChange(false);
		}
	}
	
	scenechange->Update();
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

	DrawRotaGraph(WIN_WIDTH - (128 * 0.4f) , WIN_HEIGHT - (128 * 0.4f), 0.4f, 0.0f, startTex, TRUE);

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

	scenechange->Draw();
}

void SceneManager::GameSceneEnemyArg() {

	//特定のフレームで敵を生成する
	if (score->GetGameTimer() == 5920 || score->GetGameTimer() == 5900 || score->GetGameTimer() == 5880//3
		|| score->GetGameTimer() == 5860 || score->GetGameTimer() == 5700 || score->GetGameTimer() == 5680//6
		|| score->GetGameTimer() == 5660 || score->GetGameTimer() == 5650 || score->GetGameTimer() == 5630//9
		|| score->GetGameTimer() == 5610 || score->GetGameTimer() == 5600 || score->GetGameTimer() == 5580//12

		|| score->GetGameTimer() == 5560 || score->GetGameTimer() == 5300 || score->GetGameTimer() == 5280//15
		|| score->GetGameTimer() == 5240 || score->GetGameTimer() == 5220 || score->GetGameTimer() == 5180//18
		|| score->GetGameTimer() == 5160 || score->GetGameTimer() == 5100 || score->GetGameTimer() == 5080//21

		|| score->GetGameTimer() == 5060 || score->GetGameTimer() == 5040 || score->GetGameTimer() == 5000//24
		|| score->GetGameTimer() == 4980 || score->GetGameTimer() == 4960 || score->GetGameTimer() == 4940//27
		|| score->GetGameTimer() == 4800 || score->GetGameTimer() == 4700 || score->GetGameTimer() == 4600//30

		|| score->GetGameTimer() == 4600 || score->GetGameTimer() == 4500 || score->GetGameTimer() == 4400//33
		|| score->GetGameTimer() == 4300 || score->GetGameTimer() == 4200 || score->GetGameTimer() == 4100//36
		|| score->GetGameTimer() == 4000 || score->GetGameTimer() == 3900 || score->GetGameTimer() == 3800//39

		|| score->GetGameTimer() == 3500 || score->GetGameTimer() == 3460 || score->GetGameTimer() == 3420//42
		|| score->GetGameTimer() == 3380 || score->GetGameTimer() == 3340 || score->GetGameTimer() == 3300//45
		|| score->GetGameTimer() == 3260 || score->GetGameTimer() == 3220 || score->GetGameTimer() == 3180//48

		|| score->GetGameTimer() == 3140 || score->GetGameTimer() == 3100 || score->GetGameTimer() == 3060//51
		|| score->GetGameTimer() == 3020 || score->GetGameTimer() == 2980 || score->GetGameTimer() == 2940//54
		|| score->GetGameTimer() == 2900 || score->GetGameTimer() == 2700 || score->GetGameTimer() == 2680//57

		|| score->GetGameTimer() == 2660 || score->GetGameTimer() == 2640 || score->GetGameTimer() == 2620//60
		|| score->GetGameTimer() == 2600 || score->GetGameTimer() == 2580 || score->GetGameTimer() == 2560//63
		|| score->GetGameTimer() == 2540 || score->GetGameTimer() == 2520 || score->GetGameTimer() == 2500//66

		|| score->GetGameTimer() == 2480 || score->GetGameTimer() == 2460 || score->GetGameTimer() == 2440//69
		|| score->GetGameTimer() == 2420 || score->GetGameTimer() == 2400 || score->GetGameTimer() == 2380//71
		|| score->GetGameTimer() == 2360 || score->GetGameTimer() == 2340 || score->GetGameTimer() == 2320//74

		|| score->GetGameTimer() == 2300 || score->GetGameTimer() == 2280 || score->GetGameTimer() == 2260//77
		|| score->GetGameTimer() == 2340 || score->GetGameTimer() == 2320 || score->GetGameTimer() == 1800//80
		|| score->GetGameTimer() == 1790 || score->GetGameTimer() == 1780 || score->GetGameTimer() == 1770//83

		|| score->GetGameTimer() == 1760 || score->GetGameTimer() == 1750 || score->GetGameTimer() == 1740//86
		|| score->GetGameTimer() == 1730 || score->GetGameTimer() == 1720 || score->GetGameTimer() == 1710//89
		|| score->GetGameTimer() == 1700 || score->GetGameTimer() == 1690 || score->GetGameTimer() == 1680//92

		|| score->GetGameTimer() == 1670 || score->GetGameTimer() == 1660 || score->GetGameTimer() == 1650//95
		|| score->GetGameTimer() == 1640 || score->GetGameTimer() == 1630 || score->GetGameTimer() == 1620//98
		|| score->GetGameTimer() == 1610 || score->GetGameTimer() == 1600 || score->GetGameTimer() == 1590//101

		|| score->GetGameTimer() == 1580 || score->GetGameTimer() == 1570 || score->GetGameTimer() == 1560//104
		|| score->GetGameTimer() == 1550 || score->GetGameTimer() == 1540 || score->GetGameTimer() == 1530//107
		|| score->GetGameTimer() == 1520 || score->GetGameTimer() == 1510 || score->GetGameTimer() == 1500//110

		|| score->GetGameTimer() == 1490 || score->GetGameTimer() == 900 || score->GetGameTimer() == 890//113
		|| score->GetGameTimer() == 880 || score->GetGameTimer() == 870 || score->GetGameTimer() == 860//116
		|| score->GetGameTimer() == 850 || score->GetGameTimer() == 840 || score->GetGameTimer() == 830//119

		|| score->GetGameTimer() == 810 || score->GetGameTimer() == 820 || score->GetGameTimer() == 800//122
		|| score->GetGameTimer() == 790 || score->GetGameTimer() == 780 || score->GetGameTimer() == 770//125

		|| score->GetGameTimer() == 760 || score->GetGameTimer() == 750 || score->GetGameTimer() == 740//128
		|| score->GetGameTimer() == 730 || score->GetGameTimer() == 720 || score->GetGameTimer() == 710//131
		|| score->GetGameTimer() == 700 || score->GetGameTimer() == 690 || score->GetGameTimer() == 680//140
		|| score->GetGameTimer() == 670 || score->GetGameTimer() == 660 || score->GetGameTimer() == 650//143

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
		//これで一組
		if (BirthEnemyCount == 1) {
			newEnemy->Pattern(0.0f, 0, RIGHT);
		}
		else if (BirthEnemyCount == 2) {
			newEnemy->Pattern(90.0f, 0, RIGHT);
		}
		else if (BirthEnemyCount == 3) {
			newEnemy->Pattern(180.0f, 0, RIGHT);
		}
		else if (BirthEnemyCount == 4) {
			newEnemy->Pattern(270.0f, 0, RIGHT);
		}
		//これで一組
		else if (BirthEnemyCount == 5 || BirthEnemyCount == 6 || BirthEnemyCount == 7) {
			newEnemy->Pattern(0.0f, 0, LEFT);
		}
		//これで一組
		else if (BirthEnemyCount == 8 || BirthEnemyCount == 9 || BirthEnemyCount == 10) {
			newEnemy->Pattern(120.0f, 0, LEFT);
		}
		//これで一組
		else if (BirthEnemyCount == 11 || BirthEnemyCount == 12 || BirthEnemyCount == 13) {
			newEnemy->Pattern(240.0f, 0, LEFT);
		}
		//これで一組
		else if (BirthEnemyCount == 14) {
			newEnemy->Pattern(0.0f, 0, RIGHT);
		}
		else if (BirthEnemyCount == 15) {
			newEnemy->Pattern(0.0f, 1, RIGHT);
		}
		//これで一組
		else if (BirthEnemyCount == 16) {
			newEnemy->Pattern(120.0f, 0, RIGHT);
		}
		else if (BirthEnemyCount == 17) {
			newEnemy->Pattern(120.0f, 1, RIGHT);
		}
		//これで一組
		else if (BirthEnemyCount == 18) {
			newEnemy->Pattern(240.0f, 0, RIGHT);
		}
		else if (BirthEnemyCount == 19) {
			newEnemy->Pattern(240.0f, 1, RIGHT);
		}
		//これで一組
		else if (BirthEnemyCount == 20) {
			newEnemy->Pattern(290.0f, 0, LEFT);
		}
		else if (BirthEnemyCount == 21) {
			newEnemy->Pattern(290.0f, 1, LEFT);
		}
		else if (BirthEnemyCount == 22) {
			newEnemy->Pattern(290.0f, 2, LEFT);
		}
		else if (BirthEnemyCount == 23) {
			newEnemy->Pattern(290.0f, 3, LEFT);
		}
		//これで一組
		else if (BirthEnemyCount == 24) {
			newEnemy->Pattern(110.0f, 0, LEFT);
		}
		else if (BirthEnemyCount == 25) {
			newEnemy->Pattern(110.0f, 1, LEFT);

		}
		else if (BirthEnemyCount == 26) {
			newEnemy->Pattern(110.0f, 2, LEFT);
		}
		else if (BirthEnemyCount == 27) {
			newEnemy->Pattern(110.0f, 3, LEFT);
		}
		//これで一組
		else if (BirthEnemyCount == 28) {
			newEnemy->Pattern(0.0f, 0, RIGHT);
		}
		else if (BirthEnemyCount == 29) {
			newEnemy->Pattern(0.0f, 1, RIGHT);
		}
		else if (BirthEnemyCount == 30) {
			newEnemy->Pattern(0.0f, 2, RIGHT);
		}
		//これで一組
		else if (BirthEnemyCount == 31) {
			newEnemy->Pattern(90.0f, 0, RIGHT);
		}
		else if (BirthEnemyCount == 32) {
			newEnemy->Pattern(90.0f, 1, RIGHT);
		}
		else if (BirthEnemyCount == 33) {
			newEnemy->Pattern(90.0f, 2, RIGHT);
		}
		//これで一組
		else if (BirthEnemyCount == 34) {
			newEnemy->Pattern(180.0f, 0, RIGHT);
		}
		else if (BirthEnemyCount == 35) {
			newEnemy->Pattern(180.0f, 1, RIGHT);
		}
		else if (BirthEnemyCount == 36) {
			newEnemy->Pattern(180.0f, 2, RIGHT);
		}
		//これで一組
		else if (BirthEnemyCount == 37) {
			newEnemy->Pattern(270.0f, 0, RIGHT);
		}
		else if (BirthEnemyCount == 38) {
			newEnemy->Pattern(270.0f, 1, RIGHT);
		}
		else if (BirthEnemyCount == 39) {
			newEnemy->Pattern(270.0f, 2, RIGHT);
		}
		//これで一組
		else if (BirthEnemyCount == 40) {
			newEnemy->Pattern(0.0f, 0, RIGHT);
		}
		else if (BirthEnemyCount == 41) {
			newEnemy->Pattern(90.0f, 0, RIGHT);
		}
		else if (BirthEnemyCount == 42) {
			newEnemy->Pattern(180.0f, 0, RIGHT);
		}
		else if (BirthEnemyCount == 43) {
			newEnemy->Pattern(270.0f, 0, RIGHT);
		}
		//これで一組
		else if (BirthEnemyCount == 44) {
			newEnemy->Pattern(0.0f, 1, LEFT);
		}
		else if (BirthEnemyCount == 45) {
			newEnemy->Pattern(90.0f, 1, LEFT);
		}
		else if (BirthEnemyCount == 46) {
			newEnemy->Pattern(180.0f, 1, LEFT);
		}
		else if (BirthEnemyCount == 47) {
			newEnemy->Pattern(270.0f, 1, LEFT);
		}
		//これで一組
		else if (BirthEnemyCount == 48) {
			newEnemy->Pattern(0.0f, 2, RIGHT);
		}
		else if (BirthEnemyCount == 49) {
			newEnemy->Pattern(90.0f, 2, RIGHT);
		}
		else if (BirthEnemyCount == 50) {
			newEnemy->Pattern(180.0f, 2, RIGHT);
		}
		else if (BirthEnemyCount == 51) {
			newEnemy->Pattern(270.0f, 2, RIGHT);
		}
		//これで一組
		else if (BirthEnemyCount == 52) {
			newEnemy->Pattern(0.0f, 3, LEFT);
		}
		else if (BirthEnemyCount == 53) {
			newEnemy->Pattern(90.0f, 3, LEFT);
		}
		else if (BirthEnemyCount == 54) {
			newEnemy->Pattern(180.0f, 3, LEFT);
		}
		else if (BirthEnemyCount == 55) {
			newEnemy->Pattern(270.0f, 3, LEFT);
		}
		//これで一組
		else if (BirthEnemyCount == 56 || BirthEnemyCount == 57 || BirthEnemyCount == 58) {
			newEnemy->Pattern(90.0f, 0, LEFT);
		}
		//これで一組
		else if (BirthEnemyCount == 59 || BirthEnemyCount == 60 || BirthEnemyCount == 61) {
			newEnemy->Pattern(270.0f, 0, LEFT);
		}
		//これで一組
		else if (BirthEnemyCount == 62 || BirthEnemyCount == 63 || BirthEnemyCount == 64) {
			newEnemy->Pattern(0.0f, 1, RIGHT);
		}
		//これで一組
		else if (BirthEnemyCount == 65 || BirthEnemyCount == 66 || BirthEnemyCount == 67) {
			newEnemy->Pattern(180.0f, 1, RIGHT);
		}
		//これで一組
		else if (BirthEnemyCount == 68 || BirthEnemyCount == 69 || BirthEnemyCount == 70) {
			newEnemy->Pattern(90.0f, 2, LEFT);
		}
		//これで一組
		else if (BirthEnemyCount == 71 || BirthEnemyCount == 72 || BirthEnemyCount == 73) {
			newEnemy->Pattern(270.0f, 0, LEFT);
		}
		//これで一組
		else if (BirthEnemyCount == 74 || BirthEnemyCount == 75 || BirthEnemyCount == 76) {
			newEnemy->Pattern(0.0f, 0, RIGHT);
		}
		//これで一組
		else if (BirthEnemyCount == 77 || BirthEnemyCount == 78 || BirthEnemyCount == 79) {
			newEnemy->Pattern(180.0f, 0, RIGHT);
		}
		//これで一組
		else if (BirthEnemyCount == 80 || BirthEnemyCount == 112) {
		newEnemy->Pattern(0.0f, 0, RIGHT);
		}
		else if (BirthEnemyCount == 81 || BirthEnemyCount == 113) {
		newEnemy->Pattern(45.0f, 0, RIGHT);
		}
		else if (BirthEnemyCount == 82 || BirthEnemyCount == 114) {
		newEnemy->Pattern(90.0f, 0, RIGHT);
		}
		else if (BirthEnemyCount == 83 || BirthEnemyCount == 115) {
		newEnemy->Pattern(135.0f, 0, RIGHT);
		}
		else if (BirthEnemyCount == 84 || BirthEnemyCount == 116) {
		newEnemy->Pattern(180.0f, 0, RIGHT);
		}
		else if (BirthEnemyCount == 85 || BirthEnemyCount == 117) {
		newEnemy->Pattern(225.0f, 0, RIGHT);
		}
		else if (BirthEnemyCount == 86 || BirthEnemyCount == 118) {
		newEnemy->Pattern(270.0f, 0, RIGHT);
		}
		else if (BirthEnemyCount == 87 || BirthEnemyCount == 119) {
		newEnemy->Pattern(315.0f, 0, RIGHT);
		}
		//これで一組
		else if (BirthEnemyCount == 88 || BirthEnemyCount == 120) {
		newEnemy->Pattern(0.0f, 1, LEFT);
		}
		else if (BirthEnemyCount == 89 || BirthEnemyCount == 121) {
		newEnemy->Pattern(45.0f, 1, LEFT);
		}
		else if (BirthEnemyCount == 90 || BirthEnemyCount == 122) {
		newEnemy->Pattern(90.0f, 1, LEFT);
		}
		else if (BirthEnemyCount == 91 || BirthEnemyCount == 123) {
		newEnemy->Pattern(135.0f, 1, LEFT);
		}
		else if (BirthEnemyCount == 92 || BirthEnemyCount == 124) {
		newEnemy->Pattern(180.0f, 1, LEFT);
		}
		else if (BirthEnemyCount == 93 || BirthEnemyCount == 125) {
		newEnemy->Pattern(225.0f, 1, LEFT);
		}
		else if (BirthEnemyCount == 94 || BirthEnemyCount == 126) {
		newEnemy->Pattern(270.0f, 1, LEFT);
		}
		else if (BirthEnemyCount == 95 || BirthEnemyCount == 127) {
		newEnemy->Pattern(315.0f, 1, LEFT);
		}
		//これで一組
		else if (BirthEnemyCount == 96 || BirthEnemyCount == 128) {
		newEnemy->Pattern(0.0f, 2, RIGHT);
		}
		else if (BirthEnemyCount == 97 || BirthEnemyCount == 129) {
		newEnemy->Pattern(45.0f, 2, RIGHT);
		}
		else if (BirthEnemyCount == 98 || BirthEnemyCount == 130) {
		newEnemy->Pattern(90.0f, 2, RIGHT);
		}
		else if (BirthEnemyCount == 99 || BirthEnemyCount == 131) {
		newEnemy->Pattern(135.0f, 2, RIGHT);
		}
		else if (BirthEnemyCount == 100 || BirthEnemyCount == 132) {
		newEnemy->Pattern(180.0f, 2, RIGHT);
		}
		else if (BirthEnemyCount == 101 || BirthEnemyCount == 133) {
		newEnemy->Pattern(225.0f, 2, RIGHT);
		}
		else if (BirthEnemyCount == 102 || BirthEnemyCount == 134) {
		newEnemy->Pattern(270.0f, 2, RIGHT);
		}
		else if (BirthEnemyCount == 103 || BirthEnemyCount == 135) {
		newEnemy->Pattern(315.0f, 2, RIGHT);
		}
		//これで一組
		else if (BirthEnemyCount == 104 || BirthEnemyCount == 136) {
		newEnemy->Pattern(0.0f, 3, LEFT);
		}
		else if (BirthEnemyCount == 105 || BirthEnemyCount == 137) {
		newEnemy->Pattern(45.0f, 3, LEFT);
		}
		else if (BirthEnemyCount == 106 || BirthEnemyCount == 138) {
		newEnemy->Pattern(90.0f, 3, LEFT);
		}
		else if (BirthEnemyCount == 107 || BirthEnemyCount == 139) {
		newEnemy->Pattern(135.0f, 3, LEFT);
		}
		else if (BirthEnemyCount == 108 || BirthEnemyCount == 140) {
		newEnemy->Pattern(180.0f, 3, LEFT);
		}
		else if (BirthEnemyCount == 109 || BirthEnemyCount == 141) {
		newEnemy->Pattern(225.0f, 3, LEFT);
		}
		else if (BirthEnemyCount == 110 || BirthEnemyCount == 142) {
		newEnemy->Pattern(270.0f, 3, LEFT);
		}
		else if (BirthEnemyCount == 111 || BirthEnemyCount == 143) {
		newEnemy->Pattern(315.0f, 3, LEFT);
		}
		enemy.push_back(std::move(newEnemy));
		EnemyArgment = false;
	}
}

void SceneManager::EndInit()
{
	end->Initialize(title->GetVolume());
	scenechange->Initialize();
	ChangeStart = false;
}

void SceneManager::EndUpdate(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput)
{
	//仮置き（次のシーンに行く）
	if (end->Update(input, oldinput) == true) {
		scenechange->SetdoorStart(true);
		scenechange->Setdoorframe(0.0f);
		ChangeStart = true;
	}

	if (scenechange->GetChange() && ChangeStart) {
		SceneTime = 0;
		TitleInit();
		SceneNo = static_cast<int>(NO::Title);
		scenechange->SetChange(false);
	}

	scenechange->Update();

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
	score->Draw();
	end->Draw(score->GetScorePoint());

	scenechange->Draw();
	//score->FormatDraw();
	//エネミー
}
