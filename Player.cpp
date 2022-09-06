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
	//攻撃
	AttackMove(keys, oldkeys);
}

void Player::Move(char keys[255], char oldkeys[255]) {
	//プレイヤー
	//サークル変更
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

	//移動方向変換
	if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
		Add = -Add;
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
	PlayerSpeed += Add;

	//0から360まで範囲を指定する
	if (PlayerSpeed > 360.0f) {
		PlayerSpeed = 0.0f;
	}

	if (PlayerSpeed < 0.0f) {
		PlayerSpeed = 360.0f;
	}
	//位置を求めている
	PlayerRadius = PlayerSpeed * PI / 180.0f;
	PlayerCircleX = cosf(PlayerRadius) * PlayerScale;
	PlayerCircleY = sinf(PlayerRadius) * PlayerScale;
	playerPosX = PlayerCircleX + x;
	playerPosY = PlayerCircleY + y;
}

void Player::AttackMove(char keys[255], char oldkeys[255]) {
	//敵に攻撃する
	if (keys[KEY_INPUT_S] == 1 && oldkeys[KEY_INPUT_S] == 0 && !Attack) {
		Attack = true;
	}
	//1フレームのみの判定
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