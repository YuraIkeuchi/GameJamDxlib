#pragma once
//当たり判定用のクラス
class Collision {
public:
	//円と円
	static bool CircleCollision(const float& X1, const float& Y1, const float& R1, const float& X2, const float& Y2, const float& R2);
};