#include "Player.h"
#include <DxLib.h>
#include "math.h"
//コンストラクタ
Player::Player() {
}
//デストラクタ
Player::~Player() {
}

void Player::Update(char keys[255], char oldkeys[255]) {
	//移動
	Move(keys, oldkeys);
}

void Player::Move(char keys[255], char oldkeys[255]) {
	//プレイヤー
	//サークル変更
	if (keys[KEY_INPUT_DOWN] == 1 && oldkeys[KEY_INPUT_DOWN] == 0) {
		if (Playerscale > 81.0f) {
			Playerscale -= 40.0f;
		}
	}

	if (keys[KEY_INPUT_UP] == 1 && oldkeys[KEY_INPUT_UP] == 0) {
		if (Playerscale < 201.0f) {
			Playerscale += 40.0f;
		}
	}

	//移動方向変換
	if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
		add = -add;
	}

	//敵を止める
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
	//移動量を加算している
	PlayerSpeed += add;

	if (PlayerSpeed == 360.0f || PlayerSpeed == -360.0f) {
		PlayerSpeed = 0.0f;
	}
	//位置を求めている
	Playerradius = PlayerSpeed * PI / 180.0f;
	PlayerCircleX = cosf(Playerradius) * Playerscale;
	PlayerCircleY = sinf(Playerradius) * Playerscale;
	playerPosX = PlayerCircleX + x;
	playerPosY = PlayerCircleY + y;
}

void Player::Draw() {
	DrawCircle(playerPosX, playerPosY, 10, GetColor(0, 0, 0), true);
}

void Player::FormatDraw() {
	DrawFormatString(0, 0, GetColor(0, 0, 0), "Speed:%f", PlayerSpeed);
	DrawFormatString(0, 20, GetColor(0, 0, 0), "StopInterval:%d", StopInterval);
}