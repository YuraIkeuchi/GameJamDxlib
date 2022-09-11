#include "TimeEffect.h"

constexpr auto INCREASE_SIZE = 8;
constexpr auto STEP_COUNT = (2 * DX_PI) / 200.0f;
constexpr auto ALPHA_MAX = 255;
constexpr auto DEFALUT_SIZE = 100;

TimeEffect::TimeEffect()
{
	Emitter();
	pos = FLOAT3{ 0,0,0 };
	size = DEFALUT_SIZE;
	alpha = ALPHA_MAX;
	angle = 0;

	count = 0;
}

void TimeEffect::active(FLOAT3 _pos)
{
	Emitter::activate();
	SetEmitPos(_pos);
}

void TimeEffect::Update()
{
	if (isAlive == true) {
		//count += STEP_COUNT;
		angle += STEP_COUNT;

		if (angle >= 2 * DX_PI) {
			isAlive = false;
			count = 0;
			angle = 0;
		}
	}
}

void TimeEffect::Draw()
{
	if (isAlive == true) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);		//ブレンドモードをα(128/255)に設定
		DrawBillboard3D(pos, 0.5f, 0.5f, size, angle, texture, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//ブレンドモードをオフ
	}
}
