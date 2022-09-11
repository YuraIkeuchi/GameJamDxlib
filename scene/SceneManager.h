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

	void EndInit();
	void EndUpdate(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput);
	void EndDraw();

	//クラス宣言
	// 	//エネミー
	vector<unique_ptr<Enemy>>enemy;
	bool EnemyArgment = false;
	//プレイヤー
	Player *player = nullptr;
	//ステージ上の円
	StageCircle *stagecircle = nullptr;
	//タイトルの動き
	Title *title = nullptr;
	//チュートリアルの動き
	Tutorial* tutorial = nullptr;
	//エンドの動き
	End *end = nullptr;
	//スコア
	Score* score = nullptr;
	float x = WIN_WIDTH / 2;
	float y = WIN_HEIGHT / 2;

	int gameBgm;
	int BirthEnemyCount = 0;
	int TutorialCount = 0;
	int TutorialTimer = 100;
	enum EnemyDir {
		RIGHT,
		LEFT,
	};
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
