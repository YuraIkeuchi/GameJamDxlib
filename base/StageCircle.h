#pragma once
#include "Share.h"
class StageCircle {
public:
	//コンストラクタ
	StageCircle();
	//デストラクタ
	~StageCircle();
public://メンバ関数
	//円を描くだけなので描画のみ
	void Draw();

	void SetTexture(int tex) { this->stageTex = tex; }
private:	//メンバ変数
	int stageTex = 0;

	float x = WIN_WIDTH;
	float y = WIN_HEIGHT / 2;
};