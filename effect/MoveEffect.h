#pragma once
#include "Emitter.h"

class MoveEffect : public Emitter {

	FLOAT3 pos;//発生位置
	float size;//サイズ
	float angle;//角度
	float alpha;//透明度

	float count;//出現時間（仮）

	int texture;//テクスチャ

public:
	//setter
	void SetEmitPos(FLOAT3 _pos) { this->pos = _pos; }
	void SetTexture(int tex) { this->texture = tex; }
	void SetAngle(float _angle) { this->angle = _angle; }
	//コンストラクタ
	MoveEffect();

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