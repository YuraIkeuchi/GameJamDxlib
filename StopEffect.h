#pragma once
#include "Emitter.h"

class StopEffect : public Emitter {

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

	//�R���X�g���N�^
	StopEffect();

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="_pos">�����ꏊ</param>
	void active(FLOAT3 _pos);

	//�X�V
	void Update();
	//�`��
	void Draw();
};