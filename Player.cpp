#include "Player.h"
#include "Easing.h"
#include <DxLib.h>
#include "math.h"
//コンストラクタ
Player::Player() {
}
//デストラクタ
Player::~Player() {
}

void Player::Initialize()
{
	playerPosX = WIN_WIDTH / 2;
	playerPosY = WIN_HEIGHT / 2;
	//円運動のための変数
	x = 0;
	y = 0;
	PlayerRadius = 0.0f;
	PlayerSpeed = 0.0f;
	PlayerScale = 80.0f;// LaneNumと一緒に変えること
	PlayerCircleX = 0.0f;
	PlayerCircleY = 0.0f;
	Add = 1.0f;
	Attack = false;
	AttackStart = false;
	AfterScale = 0.0f;
	AfterSpeed = 0.0f;
	frame = 0.0f;
	AttackTimer = 0;
	//敵を止めるための変数
	Stop = false;
	StopInterval = 5;

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
			PlayerScale -= 80.0f;
		}
	}

	if (keys[KEY_INPUT_UP] == 1 && oldkeys[KEY_INPUT_UP] == 0) {
		if (PlayerScale < 319.0f) {
			PlayerScale += 80.0f;
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
	//DrawFormatString(0, 0, GetColor(0, 0, 0), "frame:%f", frame);
	//DrawFormatString(0, 20, GetColor(0, 0, 0), "AttackStart:%d", AttackStart);
}