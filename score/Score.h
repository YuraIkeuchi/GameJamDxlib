#pragma once
#include "Player.h"
#include <memory>
#include <list> // �w�b�_�t�@�C���C���N���[�h
using namespace std;         //  ���O��Ԏw��
//�X�R�A�܂Ƃ߂�N���X
class Score {
public:
	void SetPlayer(Player* player) { this->player.reset(player); }
	//�R���X�g���N�^
	Score();
	//�f�X�g���N�^
	~Score();

	//������
	void Initialize();
	//�X�V
	void Update();
	//�`��
	void Draw();
	//FormatString�p
	void FormatDraw();
public:
	//getter setter
	const int GetScorePoint() { return ScorePoint; }

	const int GetGameTimer() { return GameTimer; }

	void SetScorePoint(int ScorePoint) { this->ScorePoint = ScorePoint; }
private:
	//�X�R�A
	int ScorePoint;
	//���Ԑ���(�ʃN���X�ł���������)
	int GameTimer;
	//�{��
	int MultPoint;
	//�p���N���X
	unique_ptr<Player> player = nullptr;
};