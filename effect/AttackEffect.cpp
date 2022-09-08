#include "AttackEffect.h"

void AttackEffect::Update(FLOAT3 _pos)
{
	if (isAlive == true) {
		size = FLOAT2{ size.u + 1,size.v + 1 };

		if (count >= 3.0f) {
			isAlive = false;
		}

		count += 1.0f / 60.0f;
	}
}

void AttackEffect::Draw()
{
	DrawBillboard3D(pos, 0.5f, 0.5f, 100, angle, texture, true);
}
