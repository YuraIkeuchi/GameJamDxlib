#include "MoveEffect.h"

constexpr auto INCREASE_SIZE = 8;
constexpr auto STEP_COUNT = 1.0f / 60.0f;

MoveEffect::MoveEffect()
{
	Emitter();
}

void MoveEffect::active(FLOAT3 _pos)
{
	Emitter::activate();
}

void MoveEffect::Update()
{
	if (isAlive == true) {
		count += STEP_COUNT;
		alpha -= STEP_COUNT * 255;

		if (count >= 3.0f) {
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
		DrawBillboard3D(pos, 0.5f, 0.5f, size, angle, texture, true);
	}
}
