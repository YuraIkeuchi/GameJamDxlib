#include "MoveEffect.h"

constexpr auto INCREASE_SIZE = 8;
constexpr auto STEP_COUNT = 1.0f / 60.0f;
constexpr auto ALPHA_MAX = 128;
constexpr auto DEFALUT_SIZE = 50;

MoveEffect::MoveEffect()
{
	Emitter();
	pos = FLOAT3{ 0,0,0 };
	size = DEFALUT_SIZE;
	alpha = ALPHA_MAX;
	angle = 0;

	count = 0;
}

void MoveEffect::active(FLOAT3 _pos)
{
	Emitter::activate();
	SetEmitPos(_pos);
}

void MoveEffect::Update()
{
	if (isAlive == true) {
		count += STEP_COUNT;
		size -= DEFALUT_SIZE * (1.0f / 30.0f);
		alpha -= STEP_COUNT * ALPHA_MAX * 2;

		if (count >= 0.5f) {
			isAlive = false;
			count = 0;
			size = DEFALUT_SIZE;
			alpha = ALPHA_MAX;
		}
	}

}

void MoveEffect::Draw()
{
	if (isAlive == true) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);		//ブレンドモードをα(128/255)に設定
		DrawBillboard3D(pos, 0.5f, 0.5f, size, angle, texture, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//ブレンドモードをオフ
	}
}
