#include "AttackEffect.h"

constexpr auto INCREASE_SIZE = 8;
constexpr auto STEP_COUNT = 1.0f / 60.0f;

AttackEffect::AttackEffect()
{
	Emitter();
	pos = FLOAT3{ 0,0,0 };
	size = DEFALUT_SIZE;
	alpha = ALPHA_MAX;
	angle = 0;

	count = 0;
}

void AttackEffect::active(FLOAT3 _pos)
{
	Emitter::activate();
	SetEmitPos(_pos);
	angle = rand() % 360;
}

void AttackEffect::Update()
{
	if (isAlive == true) {
		size += INCREASE_SIZE;
		count += STEP_COUNT;
		alpha -= STEP_COUNT * 255 * 1.2f;

		if (count >= 3.0f) {
			isAlive = false;
			count = 0;
			alpha = ALPHA_MAX;
			size = DEFALUT_SIZE;
		}
	}
}

void AttackEffect::Draw()
{
	if (isAlive == true) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);		//ブレンドモードをα(128/255)に設定
		DrawBillboard3D(pos, 0.5f, 0.5f, size, angle, texture, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//ブレンドモードをオフ
	}
}
