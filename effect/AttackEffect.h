#pragma once
#include "Emitter.h"

class AttackEffect : public Emitter {

	FLOAT3 pos;	//�o�����W
	FLOAT2 size;//�傫��
	float angle;//��]�p�x
	float alpha;//�����x

	//�o������
	float count;
	//�e�N�X�`��
	int texture;
public:
	//Setter
	void SetEmitPos(FLOAT3 _pos) { this->pos = _pos; }
	void SetTexture(int tex) { this->texture = tex; }

	void Update(FLOAT3 _pos);
	void Draw();
};