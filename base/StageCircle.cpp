#include "StageCircle.h"
#include <DxLib.h>
StageCircle::StageCircle() {

}

StageCircle::~StageCircle() {

}

void StageCircle::Draw() {
	DrawBillboard3D(VGet(0, 0, 0), 0.5f, 0.5f, 800, 0.0f, stageTex, true);
	//DrawCircle(x, y, 480, GetColor(255, 0, 0), false, 10);
	//DrawCircle(x, y, 400, GetColor(255, 0, 0), false, 10);
	//DrawCircle(x, y, 320, GetColor(0, 255, 0), false, 10);
	//DrawCircle(x, y, 240, GetColor(0, 0, 255), false, 10);
	//DrawCircle(x, y, 160, GetColor(0, 0, 255), false, 10);
}