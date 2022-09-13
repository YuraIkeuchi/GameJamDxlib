#pragma once
#pragma once
#include "DxLib.h"
#include "Share.h"
class SceneChange
{
public:
	//getter setter
	const bool& GetDoorEnd() { return doorEnd; }
	const bool& GetDoorStart() { return doorStart; }
	const bool& GetChange() { return Change; }
	const float& GetdoorFrame() { return doorframe; }
	void SetdoorStart(bool doorStart) { this->doorStart = doorStart; }
	void SetdoorEnd(bool doorEnd) { this->doorEnd = doorEnd; }
	void SetChange(bool Change) { this->Change = Change; }
	void Setdoorframe(float doorframe) { this->doorframe = doorframe; }
private:
	int doorTex;
	bool doorStart;
	bool doorEnd;
	bool Change;
	float doorPosX1;
	float doorPosX2;
	float doorframe;
	int doorStopTimer;
public:
	SceneChange();
	void Initialize();
	void Update();
	void Draw();

};
