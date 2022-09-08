#pragma once
#include "Emitter.h"

class AttackEffect : public Emitter {

	FLOAT3 pos;	//出現座標
	FLOAT2 size;//大きさ
	float angle;//回転角度
	float alpha;//透明度

	//出現時間
	float count;
	//テクスチャ
	int texture;
public:
	//Setter
	void SetEmitPos(FLOAT3 _pos) { this->pos = _pos; }
	void SetTexture(int tex) { this->texture = tex; }

	void Update(FLOAT3 _pos);
	void Draw();
};