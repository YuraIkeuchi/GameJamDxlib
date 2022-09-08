#include "AttackEffect.h"

AttackEffect::AttackEffect()
{
	Emitter();
	pos = FLOAT3{ 0,0,0 };
	size = 100;
	angle = 0;
	alpha = 255;

	count = 0;
}

void AttackEffect::active(FLOAT3 _pos)
{
	Emitter::activate();
	SetEmitPos(_pos);
}

void AttackEffect::Update()
{
	if (isAlive == true) {
		size += 1;
		if (count >= 3.0f) {
			isAlive = false;
			count = 0;
			size = 100;
		}

		count += 1.0f / 60.0f;
	}
}

void AttackEffect::Draw()
{
	if (isAlive == true) {
		DrawBillboard3D(pos, 0.5f, 0.5f, size, angle, texture, true);
	}
}
