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

private:	//�����o�ϐ�
	float x = WIN_WIDTH / 2;
	float y = WIN_HEIGHT / 2;
};