#pragma once
#include "Emitter.h"

class BreakEffect : public Emitter {

	FLOAT3 pos;
	float size;
	float angle;
	float alpha;

	float count;

	int texture;
	bool DeleteEffect;
public:
	//getter
	const bool GetDeleteEffect() { return DeleteEffect; }
	//setter
	void SetEmitPos(FLOAT3 _pos) { this->pos = _pos; }
	void SetTexture(int tex) { this->texture = tex; }

	//コンストラクタ
	BreakEffect();

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