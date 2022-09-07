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
	//�ړ��֌W
	AddSpeed = 1.0f;
	Speedframe = 0.0f;
	ChangeDir = false;
	Dir = RIGHT;
}

void Player::Update(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput) {
	//�ړ�
	Move(keys, oldkeys,input,oldinput);
	//�U��
	AttackMove(keys, oldkeys, input, oldinput);
}

void Player::Move(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput) {
	//�v���C���[
	//�T�[�N���ύX
	if (input.Buttons[XINPUT_BUTTON_DPAD_DOWN] && !oldinput.Buttons[XINPUT_BUTTON_DPAD_DOWN]) {
		if (PlayerScale > 81.0f) {
			PlayerScale -= 80.0f;
		}
	}

	if (input.Buttons[XINPUT_BUTTON_DPAD_UP]&& !oldinput.Buttons[XINPUT_BUTTON_DPAD_UP]) {
		if (PlayerScale < 319.0f) {
			PlayerScale += 80.0f;
		}
	}

	//�ړ������ϊ�
	//(�E�����ɂȂ�)
	if (input.RightTrigger && !oldinput.RightTrigger
		&& (Dir == LEFT)) {
		
		Speedframe = 0.0f;
		Dir = RIGHT;
		ChangeDir = true;
	}

	//(�E�����ɂȂ�)
	if (input.LeftTrigger && !oldinput.LeftTrigger
		&& (Dir == RIGHT)) {
		Speedframe = 0.0f;
		Dir = LEFT;
		ChangeDir = true;
	}

	//������ς����Ƃ����X�ɕς��
	if (ChangeDir) {

		if (Speedframe < 1.0f) {
			Speedframe += 0.025f;
		}
		else {
			Speedframe = 0.0f;
			ChangeDir = false;
		}
		if (Dir == RIGHT) {
			AddSpeed = Ease(In, Cubic, Speedframe, AddSpeed, 1.0f);
		}
		else {
			AddSpeed = Ease(In, Cubic, Speedframe, AddSpeed, -1.0f);
		}
	}

	//�G���~�߂�
	if (input.Buttons[XINPUT_BUTTON_B] && !oldinput.Buttons[XINPUT_BUTTON_B] && !Stop) {
		Stop = true;
	}
	//�G���~�߂Ă鎞��
	if (Stop) {
		StopInterval--;
		if (StopInterval == 0) {
			Stop = false;
			StopInterval = 5;
		}
	}
	//�ړ��ʂ����Z���Ă���(�U����̍d����ȊO)
	if (AttackInterval == 0) {
		PlayerSpeed += AddSpeed;
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

void Player::AttackMove(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput) {
	//�G�ɍU������
	if (input.Buttons[XINPUT_BUTTON_A] && !oldinput.Buttons[XINPUT_BUTTON_A] && !Attack && !AttackStart) {
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

	//�G�̈ʒu�܂�easing
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
	DrawFormatString(0, 0, GetColor(0, 0, 0), "AttackCount:%d", AttackCount);
	DrawFormatString(0, 60, GetColor(0, 0, 0), "KnockCount:%d", KnockCount);
	DrawFormatString(0, 20, GetColor(0, 0, 0), "AttackStart:%d", AttackStart);
	DrawFormatString(0, 40, GetColor(0, 0, 0), "Attack:%d", Attack);
}