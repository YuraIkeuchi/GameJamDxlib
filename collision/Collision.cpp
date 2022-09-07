#include "Collision.h"
#include "math.h"

bool Collision::CircleCollision(const float& X1, const float& Y1, const float& R1, const float& X2, const float& Y2, const float& R2) {
	float a = X1 - X2;
	float b = Y1 - Y2;
	//2�̋������v�Z
	float distance = sqrtf(a * a + b * b);
	//���a�̍��v���v�Z
	float radius = R1 + R2;
	if (distance <= radius) {
		return true;
	}
	else {
		return false;
	}
	return true;
}