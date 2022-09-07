#pragma once
#include"Player.h"
#include"Enemy.h"
#include"StageCircle.h"
#include "math.h"
#include<time.h>
#include "DxLib.h"

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
		GameScene,
		End,
	};

	//現在のシーンの番号
	int SceneNo = static_cast<int>(NO::GameScene);
	//初期化のための計測
	int SceneTime = 0;
#pragma region シーンごとの処理
	void TitleInit();
	void TitleUpdate(char keys[255], char oldkeys[255]);
	void TitleDraw();

	void GameSceneInit();
	void GameSceneUpdate(char keys[255], char oldkeys[255]);
	void GameSceneDraw();

	void EndInit();
	void EndUpdate(char keys[255], char oldkeys[255]);
	void EndDraw();

	//クラス宣言
	// 	//エネミー
	Enemy *enemy[Enemy_Max];
	//プレイヤー
	Player *player = nullptr;
	//ステージ上の円
	StageCircle *stagecircle = nullptr;

	float x = WIN_WIDTH / 2;
	float y = WIN_HEIGHT / 2;


public:
	//最初に初期化するもの
	void StaticInit();
	//シーンを切り替えるたびに初期化するもの
	void Init();
	//Update
	void Update(char keys[255], char oldkeys[255]);
	//Draw
	void Draw();

public:
	//getter
	const int &GetSceneTime() { return SceneTime; }
};
