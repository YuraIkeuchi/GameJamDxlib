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

	//�R���X�g���N�^
	AttackEffect();

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