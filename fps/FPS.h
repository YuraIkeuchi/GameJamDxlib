#pragma once
#include"DxLib.h"

class FPS
{
	int frameTime;
	int waitTime;
	int lastTime;
	int nowTime;
	float count;
	float fps;
	int updateTime;
	int lastUpdate;
	void Initialize(float refreshRate,int updateTime);

public:
	FPS(float refreshRate, int updateTime)
	{
		Initialize(refreshRate, updateTime);
	}
	FPS()
	{
		Initialize(60.0f, 800);
	}
	//‘Ò‚¿ŽžŠÔ
	void wait();
	float getFps();
};

