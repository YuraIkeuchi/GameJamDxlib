#pragma once
#include "Player.h"
#include <memory>
#include <list> // ヘッダファイルインクルード
using namespace std;         //  名前空間指定
//スコアまとめるクラス
class Score {
public:
	void SetPlayer(Player* player) { this->player.reset(player); }
	//コンストラクタ
	Score();
	//デストラクタ
	~Score();

	//初期化
	void Initialize();
	//更新
	bool Update(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput);
	//更新
	bool TutorialUpdate(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput);
	//描画
	void Draw();

	//FormatString用
	void FormatDraw();
public:
	//getter setter
	const int GetScorePoint() { return ScorePoint; }

	const int GetGameTimer() { return GameTimer; }

	void SetScorePoint(int ScorePoint) { this->ScorePoint = ScorePoint; }
private:
	//スコア
	int ScorePoint;
	//時間制限(別クラスでもいいかも)
	int GameTimer;
	//倍率
	int MultPoint;
	//継承クラス
	unique_ptr<Player> player = nullptr;

	float scorePosX;
	float scorePosY;

	float scorePosX2;
	float scorePosY2;

	int knockCount;
	int alphaCount;

	int scoreTex;
	int timeTex;
};