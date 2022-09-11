#include "StopEffect.h"

constexpr auto INCREASE_SIZE = 150;
constexpr auto STEP_COUNT = 1.0f / 60.0f;
constexpr auto ALPHA_MAX = 128;
constexpr auto DEFALUT_SIZE = 100;

StopEffect::StopEffect()
{
	Emitter();
	pos = FLOAT3{ 0,0,0 };
	size = DEFALUT_SIZE;
	alpha = ALPHA_MAX;
	angle = 0;

	count = 0;
}

void StopEffect::active(FLOAT3 _pos)
{
	Emitter::activate();
	SetEmitPos(_pos);
}

void StopEffect::Update()
{
	if (isAlive == true) {
		size += INCREASE_SIZE;
		alpha -= STEP_COUNT * 128;

		if (alpha <= 0) {
			isAlive = false;
			count = 0;
			alpha = ALPHA_MAX;
			size = DEFALUT_SIZE;
		}
	}
}

void StopEffect::Draw()
{
	if (isAlive == true) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);		//ブレンドモードをα(128/255)に設定
		DrawBillboard3D(pos, 0.5f, 0.5f, size, angle, texture, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//ブレンドモードをオフ
	}
}
