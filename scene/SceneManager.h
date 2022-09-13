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
#include "SceneChange.h"
#include <vector>
#include <memory>
#include <list> // ヘッダファイルインクルード
using namespace std;         //  名前空間指定
class SceneManager
{
private:
	//固定値
	static const int Enemy_Max = 10;
private:
	//シーンの種類
	enum class NO
	{
		Title,
		Tutorial,
		GameScene,
		End,
	};

	//現在のシーンの番号
	int SceneNo = static_cast<int>(NO::Title);
	//初期化のための計測
	int SceneTime = 0;
//#pragma region シーンごとの処理
	void TitleInit();
	void TitleUpdate(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput);
	void TitleDraw();

	void TutorialInit();
	void TutorialUpdate(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput);
	void TutorialDraw();

	void GameSceneInit();
	void GameSceneUpdate(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput);
	void GameSceneDraw();

	void GameSceneEnemyArg();

	void EndInit();
	void EndUpdate(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput);
	void EndDraw();

	//クラス宣言
	// 	//エネミー
	vector<unique_ptr<Enemy>>enemy;
	bool EnemyArgment = false;
	//プレイヤー
	Player* player = nullptr;
	//ステージ上の円
	unique_ptr<StageCircle> stagecircle;
	//タイトルの動き
	unique_ptr<Title> title;
	//チュートリアルの動き
	unique_ptr<Tutorial> tutorial;
	//エンドの動き
	unique_ptr<End> end;
	//スコア
	unique_ptr<Score> score;
	//シーンチェンジ
	unique_ptr<SceneChange> scenechange;
	float x = WIN_WIDTH / 2;
	float y = WIN_HEIGHT / 2;

	int gameBgm;
	bool BGMLOOP;
	bool ResetTutorial;
	int BirthEnemyCount = 0;
	int TutorialCount = 0;
	enum EnemyDir {
		RIGHT,
		LEFT,
	};

	int ChangeNumber = 0;
	enum ChangeType {
		NO,
		RESTART,
		TITLE,
	};

	bool changeFlag;

	int filterTex;
	int curTex;
	int menuStopTex;
	int newStartTex;
	int goTitleTex;
	int removeTex;

	int curPosX;
	int curPosY;

	int menuChangeSE;
	int checkSE;

	float scale1;
	float scale2;
	float scale3;
public:
	//最初に初期化するもの
	void StaticInit();
	//シーンを切り替えるたびに初期化するもの
	void Init();
	//Update
	void Update(char keys[255], char oldkeys[255],XINPUT_STATE input, XINPUT_STATE oldinput);
	//Draw
	void Draw();

public:
	//getter
	const int &GetSceneTime() { return SceneTime; }
};
