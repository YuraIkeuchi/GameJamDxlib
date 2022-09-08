#pragma once
#include "Emitter.h"

class AttackEffect : public Emitter {

	FLOAT3 pos;
	float size;
	float angle;
	float alpha;

	float count;

	int texture;
public:
	//
	void SetEmitPos(FLOAT3 _pos) { this->pos = _pos; }
	void SetTexture(int tex) { this->texture = tex; }

	AttackEffect();

	void active(FLOAT3 _pos);
	void Update();
	void Draw();
};