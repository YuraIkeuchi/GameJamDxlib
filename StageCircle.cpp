#include "StageCircle.h"
#include <DxLib.h>
StageCircle::StageCircle() {

}

StageCircle::~StageCircle() {

}

void StageCircle::Draw() {
	DrawCircle(x, y, 240, GetColor(255, 0, 0), false);
	DrawCircle(x, y, 200, GetColor(255, 0, 0), false);
	DrawCircle(x, y, 160, GetColor(0, 255, 0), false);
	DrawCircle(x, y, 120, GetColor(0, 0, 255), false);
	DrawCircle(x, y, 80, GetColor(0, 0, 255), false);
}