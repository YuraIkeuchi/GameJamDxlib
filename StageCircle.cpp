#include "StageCircle.h"
#include <DxLib.h>
StageCircle::StageCircle() {

}

StageCircle::~StageCircle() {

}

void StageCircle::Draw() {
	DrawCircle(x, y, 480, GetColor(255, 0, 0), false, 10);
	DrawCircle(x, y, 400, GetColor(255, 0, 0), false, 10);
	DrawCircle(x, y, 320, GetColor(0, 255, 0), false, 10);
	DrawCircle(x, y, 240, GetColor(0, 0, 255), false, 10);
	DrawCircle(x, y, 160, GetColor(0, 0, 255), false, 10);
}