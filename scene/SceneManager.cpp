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
		/*DrawFormatString(0, 320, GetColor(0, 0, 0), "BirthEnemyCount %d", BirthEnemyCount);
		*/
		TutorialDraw();
		break;
	case static_cast<int>(SceneManager::NO::GameScene):
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
			newEnemy->SetTargetLine(1);
			newEnemy->SetTutorialMove(true);
			newEnemy->SetSpeed(180.0f);
		}
		else if (BirthEnemyCount == 4) {
			newEnemy->SetTargetLine(1);
			newEnemy->SetTutorialMove(true);
			newEnemy->SetSpeed(180.0f);
		}
		else if (BirthEnemyCount == 5) {
			newEnemy->SetTargetLine(2);
			newEnemy->SetTutorialMove(true);
			newEnemy->SetSpeed(180.0f);
		}
		else if (BirthEnemyCount == 6) {
			newEnemy->SetTargetLine(3);
			newEnemy->SetTutorialMove(true);
			newEnemy->SetSpeed(180.0f);
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
	//ゲーム終了
	score->Update(keys, oldkeys, input, oldinput);

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
	if (score->GetGameTimer() == 7120 || score->GetGameTimer() == 7100 || score->GetGameTimer() == 7080//3
		|| score->GetGameTimer() == 7060 || score->GetGameTimer() == 6700 || score->GetGameTimer() == 6680//6
		|| score->GetGameTimer() == 6660 || score->GetGameTimer() == 6650 || score->GetGameTimer() == 6630//9
		|| score->GetGameTimer() == 6610 || score->GetGameTimer() == 6600 || score->GetGameTimer() == 6580//12
		|| score->GetGameTimer() == 6560 || score->GetGameTimer() == 6000 || score->GetGameTimer() == 5980//15
		|| score->GetGameTimer() == 5940 || score->GetGameTimer() == 5920 || score->GetGameTimer() == 5880//18
		|| score->GetGameTimer() == 5860 || score->GetGameTimer() == 5600 || score->GetGameTimer() == 5580//21
		|| score->GetGameTimer() == 5560 || score->GetGameTimer() == 5540 || score->GetGameTimer() == 5300//24
		|| score->GetGameTimer() == 5280 || score->GetGameTimer() == 5260 || score->GetGameTimer() == 5240//27
		|| score->GetGameTimer() == 4500 || score->GetGameTimer() == 4450 || score->GetGameTimer() == 4400//30
		|| score->GetGameTimer() == 4350 || score->GetGameTimer() == 4300 || score->GetGameTimer() == 4250//33
		|| score->GetGameTimer() == 4200 || score->GetGameTimer() == 4150 || score->GetGameTimer() == 4100//36
		|| score->GetGameTimer() == 4050 || score->GetGameTimer() == 4000 || score->GetGameTimer() == 3950//39
		|| score->GetGameTimer() == 3300 || score->GetGameTimer() == 3290 || score->GetGameTimer() == 3280//42
		|| score->GetGameTimer() == 3270 || score->GetGameTimer() == 3260 || score->GetGameTimer() == 3250//45
		|| score->GetGameTimer() == 3240 || score->GetGameTimer() == 3230 || score->GetGameTimer() == 3220//48
		|| score->GetGameTimer() == 3210 || score->GetGameTimer() == 3200 || score->GetGameTimer() == 3190//51
		|| score->GetGameTimer() == 3180 || score->GetGameTimer() == 3170 || score->GetGameTimer() == 3160//54
		|| score->GetGameTimer() == 3150 || score->GetGameTimer() == 50 || score->GetGameTimer() == 100//57
		|| score->GetGameTimer() == 40 || score->GetGameTimer() == 40 || score->GetGameTimer() == 30//60
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
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(RIGHT);
			newEnemy->SetSpeed(0.0f);
		}
		else if (BirthEnemyCount == 2) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(RIGHT);
			newEnemy->SetSpeed(90.0f);
		}
		else if (BirthEnemyCount == 3) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(RIGHT);
			newEnemy->SetSpeed(180.0f);
		}
		else if (BirthEnemyCount == 4) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(RIGHT);
			newEnemy->SetSpeed(270.0f);
		}
		//これで一組
		else if (BirthEnemyCount == 5) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(LEFT);
			newEnemy->SetSpeed(0.0f);
		}
		else if (BirthEnemyCount == 6) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(LEFT);
			newEnemy->SetSpeed(0.0f);
		}
		else if (BirthEnemyCount == 7) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(LEFT);
			newEnemy->SetSpeed(0.0f);
		}
		//これで一組
		else if (BirthEnemyCount == 8) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(LEFT);
			newEnemy->SetSpeed(120.0f);
		}
		else if (BirthEnemyCount == 9) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(LEFT);
			newEnemy->SetSpeed(120.0f);
		}
		else if (BirthEnemyCount == 10) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(LEFT);
			newEnemy->SetSpeed(120.0f);
		}
		//これで一組
		else if (BirthEnemyCount == 11) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(LEFT);
			newEnemy->SetSpeed(240.0f);
		}
		else if (BirthEnemyCount == 12) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(LEFT);
			newEnemy->SetSpeed(240.0f);
		}

		else if (BirthEnemyCount == 13) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(LEFT);
			newEnemy->SetSpeed(240.0f);
		}
		//これで一組
		else if (BirthEnemyCount == 14) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(RIGHT);
			newEnemy->SetSpeed(110.0f);
		}
		else if (BirthEnemyCount == 15) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(1);
			newEnemy->SetDir(RIGHT);
			newEnemy->SetSpeed(110.0f);
		}
		//これで一組
		else if (BirthEnemyCount == 16) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(RIGHT);
			newEnemy->SetSpeed(180.0f);
		}
		else if (BirthEnemyCount == 17) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(1);
			newEnemy->SetDir(RIGHT);
			newEnemy->SetSpeed(180.0f);
		}
		//これで一組
		else if (BirthEnemyCount == 18) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(RIGHT);
			newEnemy->SetSpeed(250.0f);
		}
		else if (BirthEnemyCount == 19) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(1);
			newEnemy->SetDir(RIGHT);
			newEnemy->SetSpeed(250.0f);
		}
		//これで一組
		else if (BirthEnemyCount == 20) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(LEFT);
			newEnemy->SetSpeed(290.0f);
		}
		else if (BirthEnemyCount == 21) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(1);
			newEnemy->SetDir(LEFT);
			newEnemy->SetSpeed(290.0f);
		}
		else if (BirthEnemyCount == 22) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(2);
			newEnemy->SetDir(LEFT);
			newEnemy->SetSpeed(290.0f);
		}
		else if (BirthEnemyCount == 23) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(3);
			newEnemy->SetDir(LEFT);
			newEnemy->SetSpeed(290.0f);
		}
		//これで一組
		else if (BirthEnemyCount == 24) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(LEFT);
			newEnemy->SetSpeed(110.0f);
		}
		else if (BirthEnemyCount == 25) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(1);
			newEnemy->SetDir(LEFT);
			newEnemy->SetSpeed(110.0f);
		}
		else if (BirthEnemyCount == 26) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(2);
			newEnemy->SetDir(LEFT);
			newEnemy->SetSpeed(110.0f);
		}
		else if (BirthEnemyCount == 27) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(3);
			newEnemy->SetDir(LEFT);
			newEnemy->SetSpeed(110.0f);
		}
		//これで一組
		else if (BirthEnemyCount == 28) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(RIGHT);
			newEnemy->SetSpeed(0.0f);
		}
		else if (BirthEnemyCount == 29) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(1);
			newEnemy->SetDir(RIGHT);
			newEnemy->SetSpeed(0.0f);
		}
		else if (BirthEnemyCount == 30) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(2);
			newEnemy->SetDir(RIGHT);
			newEnemy->SetSpeed(0.0f);
		}
		//これで一組
		else if (BirthEnemyCount == 31) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(RIGHT);
			newEnemy->SetSpeed(90.0f);
		}
		else if (BirthEnemyCount == 32) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(1);
			newEnemy->SetDir(RIGHT);
			newEnemy->SetSpeed(90.0f);
		}
		else if (BirthEnemyCount == 33) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(2);
			newEnemy->SetDir(RIGHT);
			newEnemy->SetSpeed(90.0f);
		}
		//これで一組
		else if (BirthEnemyCount == 34) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(RIGHT);
			newEnemy->SetSpeed(180.0f);
		}
		else if (BirthEnemyCount == 35) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(1);
			newEnemy->SetDir(RIGHT);
			newEnemy->SetSpeed(180.0f);
		}
		else if (BirthEnemyCount == 36) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(2);
			newEnemy->SetDir(RIGHT);
			newEnemy->SetSpeed(180.0f);
		}
		//これで一組
		else if (BirthEnemyCount == 37) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(RIGHT);
			newEnemy->SetSpeed(270.0f);
		}
		else if (BirthEnemyCount == 38) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(1);
			newEnemy->SetDir(RIGHT);
			newEnemy->SetSpeed(270.0f);
		}
		else if (BirthEnemyCount == 39) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(2);
			newEnemy->SetDir(RIGHT);
			newEnemy->SetSpeed(270.0f);
		}
		//これで一組
		else if (BirthEnemyCount == 40) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(RIGHT);
			newEnemy->SetSpeed(0.0f);
		}
		else if (BirthEnemyCount == 41) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(RIGHT);
			newEnemy->SetSpeed(90.0f);
		}
		else if (BirthEnemyCount == 42) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(RIGHT);
			newEnemy->SetSpeed(180.0f);
		}
		else if (BirthEnemyCount == 43) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(0);
			newEnemy->SetDir(RIGHT);
			newEnemy->SetSpeed(270.0f);
		}
		//これで一組
		else if (BirthEnemyCount == 44) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(1);
			newEnemy->SetDir(LEFT);
			newEnemy->SetSpeed(0.0f);
		}
		else if (BirthEnemyCount == 45) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(1);
			newEnemy->SetDir(LEFT);
			newEnemy->SetSpeed(90.0f);
		}
		else if (BirthEnemyCount == 46) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(1);
			newEnemy->SetDir(LEFT);
			newEnemy->SetSpeed(180.0f);
		}
		else if (BirthEnemyCount == 47) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(1);
			newEnemy->SetDir(LEFT);
			newEnemy->SetSpeed(270.0f);
		}
		//これで一組
		else if (BirthEnemyCount == 48) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(2);
			newEnemy->SetDir(RIGHT);
			newEnemy->SetSpeed(0.0f);
		}
		else if (BirthEnemyCount == 49) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(2);
			newEnemy->SetDir(RIGHT);
			newEnemy->SetSpeed(90.0f);
		}
		else if (BirthEnemyCount == 50) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(2);
			newEnemy->SetDir(RIGHT);
			newEnemy->SetSpeed(180.0f);
		}
		else if (BirthEnemyCount == 51) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(2);
			newEnemy->SetDir(RIGHT);
			newEnemy->SetSpeed(270.0f);
		}
		//これで一組
		else if (BirthEnemyCount == 52) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(3);
			newEnemy->SetDir(LEFT);
			newEnemy->SetSpeed(0.0f);
		}
		else if (BirthEnemyCount == 53) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(3);
			newEnemy->SetDir(LEFT);
			newEnemy->SetSpeed(90.0f);
		}
		else if (BirthEnemyCount == 54) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(3);
			newEnemy->SetDir(LEFT);
			newEnemy->SetSpeed(180.0f);
		}
		else if (BirthEnemyCount == 55) {
			newEnemy->SetEnemyTimer(100);
			newEnemy->SetTargetLine(3);
			newEnemy->SetDir(LEFT);
			newEnemy->SetSpeed(270.0f);
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
	//score->Draw();
	end->Draw(score->GetScorePoint());

	scenechange->Draw();
	//score->FormatDraw();
	//エネミー
}
