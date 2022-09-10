#include "Collision.h"
#include "math.h"

float Collision::GetLength(float posX, float posY, float posX2, float posY2)
{

	float len;
	len = sqrtf((posX - posX2) * (posX - posX2) + (posY - posY2) * (posY - posY2));
	return len;
}

bool Collision::CircleCollision(const float& X1, const float& Y1, const float& R1, const float& X2, const float& Y2, const float& R2) {
	float a = X1 - X2;
	float b = Y1 - Y2;
	//2‚Â‚Ì‹——£‚ğŒvZ
	float distance = sqrtf(a * a + b * b);
	//”¼Œa‚Ì‡Œv‚ğŒvZ
	float radius = R1 + R2;
	if (distance <= radius) {
		return true;
	}
	else {
		return false;
	}
	return true;
}