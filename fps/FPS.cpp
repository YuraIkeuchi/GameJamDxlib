#include "FPS.h"

void FPS::Initialize(float refreshRate, int updateTime)
{
	frameTime = (int)(1000.0f / refreshRate);
	this->updateTime = updateTime;
	waitTime = 0;
	lastTime = nowTime = 0;
	count = 0.0f;
	fps = 0.0f;
	lastUpdate = 0;
}

void FPS::wait()
{
	nowTime = GetNowCount();
	waitTime = frameTime - (nowTime - lastTime);
	if (waitTime > 0)
	{
		WaitTimer(waitTime);
	}
	lastTime = GetNowCount();
}

float FPS::getFps()
{
	count += 1.0f;
	if (updateTime < (lastTime - lastUpdate))
	{
		fps = count / (float)(lastTime - lastUpdate) * 1000.0f;
		lastUpdate = lastTime;
		count = 0.0f;
	}

	return fps;
}
