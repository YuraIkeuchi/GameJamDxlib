#pragma once
#include "Share.h"
class StageCircle {
public:
	//�R���X�g���N�^
	StageCircle();
	//�f�X�g���N�^
	~StageCircle();
public://�����o�֐�
	//�~��`�������Ȃ̂ŕ`��̂�
	void Draw();

	void SetTexture(int tex) { this->stageTex = tex; }
private:	//�����o�ϐ�
	int stageTex = 0;

	float x = WIN_WIDTH;
	float y = WIN_HEIGHT / 2;
};