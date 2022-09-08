#pragma once
#include "Emitter.h"

constexpr auto ALPHA_MAX = 255;
constexpr auto DEFALUT_SIZE = 100;

class AttackEffect : public Emitter {

	FLOAT3 pos;
	float size;
	float angle;
	float alpha;

	float count;

	int texture;
public:
	//setter
	void SetEmitPos(FLOAT3 _pos) { this->pos = _pos; }
	void SetTexture(int tex) { this->texture = tex; }

	//コンストラクタ
	AttackEffect();

	/// <summary>
	/// 発生時
	/// </summary>
	/// <param name="_pos">発生場所</param>
	void active(FLOAT3 _pos);

	//更新
	void Update();
	//描画
	void Draw();
};