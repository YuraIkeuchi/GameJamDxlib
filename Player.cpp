#include "Player.h"
#include <DxLib.h>
#include "math.h"
//ƒRƒ“ƒXƒgƒ‰ƒNƒ^
Player::Player() {
}
//ƒfƒXƒgƒ‰ƒNƒ^
Player::~Player() {
}

void Player::Initialize()
{
	playerPosX = WIN_WIDTH / 2;
	playerPosY = WIN_HEIGHT / 2;
	//‰~‰^“®‚Ì‚½‚ß‚Ì•Ï”
	x = WIN_WIDTH / 2;
	y = WIN_HEIGHT / 2;
	PlayerRadius = 0.0f;
	PlayerSpeed = 0.0f;
	PlayerScale = 80.0f;// LaneNum‚Æˆê‚É•Ï‚¦‚é‚±‚Æ
	PlayerCircleX = 0.0f;
	PlayerCircleY = 0.0f;
	Add = 1.0f;
	Attack = false;
	AttackTimer = 0;
	//“G‚ðŽ~‚ß‚é‚½‚ß‚Ì•Ï”
	Stop = false;
	StopInterval = 5;
}

void Player::Update(char keys[255], char oldkeys[255]) {
	//ˆÚ“®
	Move(keys, oldkeys);
	//UŒ‚
	AttackMove(keys, oldkeys);
}

void Player::Move(char keys[255], char oldkeys[255]) {
	//ƒvƒŒƒCƒ„[
	//ƒT[ƒNƒ‹•ÏX
	if (keys[KEY_INPUT_DOWN] == 1 && oldkeys[KEY_INPUT_DOWN] == 0) {
		if (PlayerScale > 81.0f) {
			PlayerScale -= 40.0f;
		}
	}

	if (keys[KEY_INPUT_UP] == 1 && oldkeys[KEY_INPUT_UP] == 0) {
		if (PlayerScale < 201.0f) {
			PlayerScale += 40.0f;
		}
	}

	//ˆÚ“®•ûŒü•ÏŠ·
	if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
		Add = -Add;
	}

	//“G‚ðŽ~‚ß‚é
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
	//ˆÚ“®—Ê‚ð‰ÁŽZ‚µ‚Ä‚¢‚é
	PlayerSpeed += Add;

	//0‚©‚ç360‚Ü‚Å”ÍˆÍ‚ðŽw’è‚·‚é
	if (PlayerSpeed > 360.0f) {
		PlayerSpeed = 0.0f;
	}

	if (PlayerSpeed < 0.0f) {
		PlayerSpeed = 360.0f;
	}
	//ˆÊ’u‚ð‹‚ß‚Ä‚¢‚é
	PlayerRadius = PlayerSpeed * PI / 180.0f;
	PlayerCircleX = cosf(PlayerRadius) * PlayerScale;
	PlayerCircleY = sinf(PlayerRadius) * PlayerScale;
	playerPosX = PlayerCircleX + x;
	playerPosY = PlayerCircleY + y;
}

void Player::AttackMove(char keys[255], char oldkeys[255]) {
	//“G‚ÉUŒ‚‚·‚é
	if (keys[KEY_INPUT_S] == 1 && oldkeys[KEY_INPUT_S] == 0 && !Attack) {
		Attack = true;
	}
	//1ƒtƒŒ[ƒ€‚Ì‚Ý‚Ì”»’è
	if (Attack) {
		AttackTimer++;
		if (AttackTimer == 2) {
			AttackTimer = 0;
			Attack = false;
		}
	}
}

void Player::Draw() {
	DrawCircle(playerPosX, playerPosY, 10, GetColor(0, 0, 0), true);
}

void Player::FormatDraw() {
	DrawFormatString(0, 320, GetColor(0, 0, 0), "Timer:%d", AttackTimer);
	DrawFormatString(0, 300, GetColor(0, 0, 0), "Attack:%d", Attack);
}