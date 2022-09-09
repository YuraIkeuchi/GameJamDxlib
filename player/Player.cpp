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
	PlayerScale = 320.0f;
	PlayerCircleX = 0.0f;
	PlayerCircleY = 0.0f;
	//攻撃関係
	Attack = false;
	AttackStart = false;
	AfterScale = 0.0f;
	AfterSpeed = 0.0f;
	frame = 0.0f;
	AttackTimer = 0;
	AttackInterval = 0;
	KnockCount = 0;
	LockOnTexArea = 0.0f;
	LockOnArea = 0.0f;
	//一回内側に入ったかどうか
	InArea = false;
	InAreaStart = false;
	//敵を止めるための変数
	Stop = false;
	StopInterval = 5;
	//移動関係
	AddSpeed = 1.0f;
	AddVelocity = 0.0f;
	Speedframe = 0.0f;
	ChangeDir = false;
	Dir = RIGHT;
	//ダメージ関係
	Stun = false;
	StunTimer = 100;
	Invisible = false;
	InvisibleTimer = 100;

	AttackAreaX = 0.0f;
	AttackAreaY = 0.0f;
	AttackScale = 60.0f;
	AttackSpeed = 0.0f;
	AttackCircleX = 0.0f;
	AttackCircleY = 0.0f;
	for (int i = 0; i < EFFECTS_MAX; i++) {
		Effects[i] = new MoveEffect();
		Effects[i]->SetTexture(texture);
	}

	inputX = 0.0f;
	inputY = 0.0f;
	joyangle = 0.0f;
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
	AttackArea();

	for (int i = 0; i < EFFECTS_MAX; i++)
	{
		if (Effects[i]->getIsAlive() != true) {
			Effects[i]->active(VGet(playerPosX, playerPosY, 0));
			break;
		}
	}
	for (int i = 0; i < EFFECTS_MAX; i++)
	{
		Effects[i]->Update();
	}
}

void Player::Move(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput) {
	/*float X = (float)input.ThumbLX;
	float Y = -(float)input.ThumbLY;
	joyangle = atan2((float)X, (float)Y) - PI / 2;*/

	inputX = (float)input.ThumbLX / 32768;
	inputY = (float)input.ThumbLY / 32768;
	joyangle = ((atan2(inputX, inputY) * (180.0f / PI))) + 90;
	AttackSpeed = joyangle;
	//プレイヤー
	//サークル変更
	if (input.Buttons[XINPUT_BUTTON_DPAD_DOWN] && !oldinput.Buttons[XINPUT_BUTTON_DPAD_DOWN]) {
		if (PlayerScale > 81.0f) {
			PlayerScale -= 80.0f;
		}
	}

	if (input.Buttons[XINPUT_BUTTON_DPAD_UP] && !oldinput.Buttons[XINPUT_BUTTON_DPAD_UP]) {
		if (PlayerScale < 319.0f) {
			PlayerScale += 80.0f;
		}
	}

	//どのサークルにいるかで変更するものがある
	if (PlayerScale == 80.0f) {
		LockOnTexArea = 200.0f;
		if (Dir == RIGHT) {
			AddVelocity = 0.75f;
		}
		else {
			AddVelocity = -0.75f;
		}
	}
	else if (PlayerScale == 160.0f) {
		LockOnTexArea = 300.0f;
		if (Dir == RIGHT) {
			AddVelocity = 0.5f;
		}
		else {
			AddVelocity = -0.5f;
		}
	}
	else if (PlayerScale == 240.0f) {
		LockOnTexArea = 400.0f;
		if (Dir == RIGHT) {
			AddVelocity = 0.25f;
		}
		else {
			AddVelocity = -0.25f;
		}
	}
	else if (PlayerScale == 320.0f) {
		LockOnTexArea = 500.0f;
		if (Dir == RIGHT) {
			AddVelocity = 0.0f;
		}
		else {
			AddVelocity = 0.0f;
		}
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
		PlayerSpeed += AddSpeed + AddVelocity;
	}

	//攻撃後の硬直(この間にリンク判定する)
	if (AttackInterval > 0) {
		AttackInterval--;
	}
	else {
		//リンクが切れる
		AttackInterval = 0;
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

void Player::AttackArea() {
	
	//位置を求めている
	AttackRadius = AttackSpeed * PI / 180.0f;
	AttackCircleX = cosf(AttackRadius) * AttackScale;
	AttackCircleY = sinf(AttackRadius) * AttackScale;
	AttackAreaX = AttackCircleX + playerPosX;
	AttackAreaY = AttackCircleY + playerPosY;
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

	for (int i = 0; i < EFFECTS_MAX; i++)
	{
		Effects[i]->Draw();
	}

	DrawBillboard3D(VGet(AttackAreaX, AttackAreaY, 0), 0.5f, 0.5f, 100, 0.0f, targettexture, true);
}

void Player::FormatDraw() {
	DrawFormatString(0, 0, GetColor(0, 0, 0), "InArea:%d", InArea);
	DrawFormatString(0, 20, GetColor(0, 0, 0), "InAreaStart:%d", InAreaStart);
	DrawFormatString(0, 40, GetColor(0, 0, 0), "inputX:%f", inputX);
	DrawFormatString(0, 60, GetColor(0, 0, 0), "inputY:%f", inputY);
	DrawFormatString(0, 80, GetColor(0, 0, 0), "joyangle:%f", joyangle);
	DrawFormatString(0, 100, GetColor(0, 0, 0), "Speed:%f", PlayerSpeed);
	//DrawFormatString(0, 60, GetColor(0, 0, 0), "AddSpeed:%f", AddSpeed);
	//DrawFormatString(0, 80, GetColor(0, 0, 0), "AddVelocity:%f", AddVelocity);
	DrawFormatString(0, 120, GetColor(0, 0, 0), "AttackStart:%d", AttackStart);
	DrawFormatString(0, 140, GetColor(0, 0, 0), "Attack:%d", Attack);
}