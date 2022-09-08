#pragma once
#include "Emitter.h"

constexpr auto ALPHA_MAX = 255;
constexpr auto DEFALUT_SIZE = 100;

class MoveEffect : public Emitter {

	FLOAT3 pos;//�����ʒu
	float size;//�T�C�Y
	float angle;//�p�x
	float alpha;//�����x

	float count;//�o�����ԁi���j

	int texture;//�e�N�X�`��
public:
	//setter
	void SetEmitPos(FLOAT3 _pos) { this->pos = _pos; }
	void SetTexture(int tex) { this->texture = tex; }

	//�R���X�g���N�^
	MoveEffect();

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