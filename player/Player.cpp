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
	//攻撃関係
	Attack = false;
	AttackStart = false;
	AfterScale = 0.0f;
	AfterSpeed = 0.0f;
	frame = 0.0f;
	AttackTimer = 0;
	AttackCount = 0;
	AttackInterval = 0;
	KnockCount = 0;
	LockOnTexArea = 0.0f;
	LockOnArea = 0.0f;
	//敵を止めるための変数
	Stop = false;
	StopInterval = 5;
	//移動関係
	AddSpeed = 1.0f;
	Speedframe = 0.0f;
	ChangeDir = false;
	Dir = RIGHT;
	//ダメージ関係
	Stun = false;
	StunTimer = 100;
	Invisible = false;
	InvisibleTimer = 100;
}

void Player::Update(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput) {
	if (!Stun) {
		//移動
		Move(keys, oldkeys, input, oldinput);
		//攻撃
		AttackMove(keys, oldkeys, input, oldinput);
	}
	//スタン関係
	PlayerStun();
}

void Player::Move(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput) {
	//プレイヤー
	//サークル変更
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

	if (PlayerScale == 80.0f) {
		LockOnTexArea = 200.0f;
	}
	else if (PlayerScale == 160.0f) {
		LockOnTexArea = 300.0f;
	}
	else if (PlayerScale == 240.0f) {
		LockOnTexArea = 400.0f;
	}
	else if (PlayerScale == 320.0f) {
		LockOnTexArea = 500.0f;
	}

	//移動方向変換
	//(右向きになる)
	if (input.RightTrigger && !oldinput.RightTrigger
		&& (Dir == LEFT)) {
		
		Speedframe = 0.0f;
		Dir = RIGHT;
		ChangeDir = true;
	}

	//(右向きになる)
	if (input.LeftTrigger && !oldinput.LeftTrigger
		&& (Dir == RIGHT)) {
		Speedframe = 0.0f;
		Dir = LEFT;
		ChangeDir = true;
	}

	//向きを変えたとき徐々に変わる
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

	//敵を止める
	if (input.Buttons[XINPUT_BUTTON_B] && !oldinput.Buttons[XINPUT_BUTTON_B] && !Stop) {
		Stop = true;
	}
	//敵を止めてる時間
	if (Stop) {
		StopInterval--;
		if (StopInterval == 0) {
			Stop = false;
			StopInterval = 5;
		}
	}
	//移動量を加算している(攻撃後の硬直後以外)
	if (AttackInterval == 0) {
		PlayerSpeed += AddSpeed;
	}

	//攻撃後の硬直(この間にリンク判定する)
	if (AttackInterval > 0) {
		AttackInterval--;
	}
	else {
		//リンクが切れる
		AttackInterval = 0;
		AttackCount = 0;
	}

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

void Player::AttackMove(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput) {
	//敵に攻撃する
	if (input.Buttons[XINPUT_BUTTON_A] && !oldinput.Buttons[XINPUT_BUTTON_A] && !Attack && !AttackStart) {
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

	//敵の位置までeasing
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

void Player::PlayerStun() {
	//ダメージ食らったとき動けない
	if (Stun) {
		StunTimer--;
		if (StunTimer <= 0) {
			StunTimer = 100;
			Stun = false;
			Invisible = true;
		}
	}
	//スタン終わったとき一定時間無敵
	if (Invisible) {
		InvisibleTimer--;
		if (InvisibleTimer <= 0) {
			InvisibleTimer = 100;
			Invisible = false;
		}
	}
}
void Player::Draw() {
	DrawBillboard3D(VGet(playerPosX, playerPosY, 0), 0.5f, 0.5f, 50, 0.0f, texture, true);
	DrawBillboard3D(VGet(playerPosX, playerPosY, 0), 0.5f, 0.5f, LockOnTexArea, 0.0f, targettexture, true);
	//DrawCircle(playerPosX, playerPosY, 20, GetColor(0, 0, 0), true);
}

void Player::FormatDraw() {
	DrawFormatString(0, 0, GetColor(0, 0, 0), "Stun:%d", Stun);
	DrawFormatString(0, 60, GetColor(0, 0, 0), "Invisible:%d", Invisible);
	//DrawFormatString(0, 20, GetColor(0, 0, 0), "AttackStart:%d", AttackStart);
	//DrawFormatString(0, 40, GetColor(0, 0, 0), "Attack:%d", Attack);
}