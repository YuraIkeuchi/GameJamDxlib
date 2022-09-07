#include "Player.h"
#include "Easing.h"
#include <DxLib.h>
#include "math.h"
//�R���X�g���N�^
Player::Player() {
}
//�f�X�g���N�^
Player::~Player() {
}

void Player::Initialize()
{
	playerPosX = WIN_WIDTH / 2;
	playerPosY = WIN_HEIGHT / 2;
	//�~�^���̂��߂̕ϐ�
	x = 0;
	y = 0;
	PlayerRadius = 0.0f;
	PlayerSpeed = 0.0f;
	PlayerScale = 80.0f;// LaneNum�ƈꏏ�ɕς��邱��
	PlayerCircleX = 0.0f;
	PlayerCircleY = 0.0f;
	Add = 1.0f;
	//�U���֌W
	Attack = false;
	AttackStart = false;
	AfterScale = 0.0f;
	AfterSpeed = 0.0f;
	frame = 0.0f;
	AttackTimer = 0;
	AttackCount = 0;
	AttackInterval = 0;
	//�G���~�߂邽�߂̕ϐ�
	Stop = false;
	StopInterval = 5;


}

void Player::Update(char keys[255], char oldkeys[255]) {
	//�ړ�
	Move(keys, oldkeys);
	//�U��
	AttackMove(keys, oldkeys);
}

void Player::Move(char keys[255], char oldkeys[255]) {
	//�v���C���[
	//�T�[�N���ύX
	if (keys[KEY_INPUT_DOWN] == 1 && oldkeys[KEY_INPUT_DOWN] == 0) {
		if (PlayerScale > 81.0f) {
			PlayerScale -= 80.0f;
		}
	}

	if (keys[KEY_INPUT_UP] == 1 && oldkeys[KEY_INPUT_UP] == 0) {
		if (PlayerScale < 319.0f) {
			PlayerScale += 80.0f;
		}
	}

	//�ړ������ϊ�
	if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
		Add = -Add;
	}

	//�G���~�߂�
	if (keys[KEY_INPUT_A] == 1 && oldkeys[KEY_INPUT_A] == 0 && !Stop) {
		Stop = true;
	}

	if (Stop) {
		StopInterval--;
		if (StopInterval == 0) {
			Stop = false;
			StopInterval = 5;
		}
	}
	//�ړ��ʂ����Z���Ă���(�U����̍d����ȊO)
	if (AttackInterval == 0) {
		PlayerSpeed += Add;
	}

	//�U����̍d��(���̊ԂɃ����N���肷��)
	if (AttackInterval > 0) {
		AttackInterval--;
	}
	else {
		//�����N���؂��
		AttackInterval = 0;
		AttackCount = 0;
	}

	//0����360�܂Ŕ͈͂��w�肷��
	if (PlayerSpeed > 360.0f) {
		PlayerSpeed = 0.0f;
	}

	if (PlayerSpeed < 0.0f) {
		PlayerSpeed = 360.0f;
	}
	//�ʒu�����߂Ă���
	PlayerRadius = PlayerSpeed * PI / 180.0f;
	PlayerCircleX = cosf(PlayerRadius) * PlayerScale;
	PlayerCircleY = sinf(PlayerRadius) * PlayerScale;
	playerPosX = PlayerCircleX + x;
	playerPosY = PlayerCircleY + y;
}

void Player::AttackMove(char keys[255], char oldkeys[255]) {
	//�G�ɍU������
	if (keys[KEY_INPUT_S] == 1 && oldkeys[KEY_INPUT_S] == 0 && !Attack && !AttackStart) {
		Attack = true;
	}
	//1�t���[���݂̂̔���
	if (Attack) {
		AttackTimer++;
		if (AttackTimer == 2) {
			AttackTimer = 0;
			Attack = false;
		}
	}

	if (AttackStart) {
		if (frame < 1.0f) {
			frame += 0.1f;
		}
		else {
			frame = 0.0f;
			AttackStart = false;
		}

		PlayerScale = Ease(In, Cubic, frame, PlayerScale, AfterScale);
		PlayerSpeed = Ease(In, Cubic, frame, PlayerSpeed, AfterSpeed);
	}
}

void Player::Draw() {
	DrawBillboard3D(VGet(playerPosX, playerPosY, 0), 0.5f, 0.5f, 50, 0.0f, texture, true);
	//DrawCircle(playerPosX, playerPosY, 20, GetColor(0, 0, 0), true);
}

void Player::FormatDraw() {
	DrawFormatString(0, 100, GetColor(0, 0, 0), "AttackCount:%d", AttackCount);
	DrawFormatString(0, 140, GetColor(0, 0, 0), "Attack:%d", Attack);
	DrawFormatString(0, 120, GetColor(0, 0, 0), "AttackInterVal:%d", AttackInterval);

}