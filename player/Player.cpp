#include "Player.h"
#include "Easing.h"
#include <DxLib.h>
#include "math.h"
//コンストラクタ
Player::Player() {
	attackSound = LoadSoundMem("Resources/sound/attack.mp3");
	enemyStopSound = LoadSoundMem("Resources/sound/enemyStop.mp3");
	stopTexture = LoadGraph("Resources/stop.png");
}
//デストラクタ
Player::~Player() {
}

void Player::Initialize(int soundBolume)
{
	playerPosX = WIN_WIDTH / 2;
	playerPosY = WIN_HEIGHT / 2;
	//円運動のための変数
	x = 0;
	y = 0;
	PlayerRadius = 0.0f;
	PlayerSpeed = 5.0f;
	PlayerScale = 320.0f;
	PlayerCircleX = 0.0f;
	PlayerCircleY = 0.0f;
	PlayerRot = 0.0f;
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
	PlayerRotDir = ROTRIGHT;
	//ダメージ関係
	Stun = false;
	StunTimer = 100;
	StunCount = 0;
	Invisible = false;
	InvisibleTimer = 100;
	Around = false;
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
	stopEffects = new StopEffect();
	stopEffects->SetTexture(stopTexture);
	InputX = 0.0f;
	InputY = 0.0f;
	Joyangle = 0.0f;
	ChangeVolumeSoundMem(soundBolume * 1.2, attackSound);
	ChangeVolumeSoundMem(soundBolume * 1.2, enemyStopSound);
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
		Effects[i]->SetAngle(PlayerRot);
	}
	stopEffects->SetEmitPos(VGet(playerPosX, playerPosY, 0));
	stopEffects->Update();
}

void Player::Move(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput) {
	/*float X = (float)input.ThumbLX;
	float Y = -(float)input.ThumbLY;
	joyangle = atan2((float)X, (float)Y) - PI / 2;*/

	InputX = (float)input.ThumbLX / 32768;
	InputY = (float)input.ThumbLY / 32768;
	Joyangle = ((atan2(InputX, InputY) * (180.0f / PI))) + 90;
	if(InputX == 0.0f && InputY == 0.0f){
		if (Dir == RIGHT) {
			AttackSpeed = PlayerSpeed + 90.0f;
		}
		else {
			AttackSpeed = PlayerSpeed + 270.0f;
		}
	}
	else {
		AttackSpeed = Joyangle;
	}
	PlayerRot += 0.1f;
	//プレイヤー
	//サークル変更
	/*if (input.Buttons[XINPUT_BUTTON_DPAD_DOWN] && !oldinput.Buttons[XINPUT_BUTTON_DPAD_DOWN]) {
		if (PlayerScale > 81.0f) {
			PlayerScale -= 80.0f;
		}
	}

	if (input.Buttons[XINPUT_BUTTON_DPAD_UP] && !oldinput.Buttons[XINPUT_BUTTON_DPAD_UP]) {
		if (PlayerScale < 319.0f) {
			PlayerScale += 80.0f;
		}
	}*/

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
		PlayerRotDir = ROTRIGHT;
		ChangeDir = true;
	}

	//(右向きになる)
	if (input.LeftTrigger && !oldinput.LeftTrigger
		&& (Dir == RIGHT)) {
		Speedframe = 0.0f;
		Dir = LEFT;
		PlayerRotDir = ROTLEFT;
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
		stopEffects->active(VGet(playerPosX, playerPosY, 0));
		PlaySoundMem(enemyStopSound, DX_PLAYTYPE_BACK);
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
	//プレイヤーの向き(通常時とスティック動かしているときで変わる)
	//if (AttackStart || KnockCount != 0) {
	//	InputX = 0.0f;
	//	InputY = 0.0f;
	//}
	//if ((InputX == 0.0f) && (InputY == 0.0f)) {
	//	if (PlayerRotDir == ROTRIGHT) {
	//		PlayerRot = -((PlayerSpeed - 90.0f) / 180.0f) * PI;
	//	}
	//	else if (PlayerRotDir == ROTLEFT) {
	//		PlayerRot = -((PlayerSpeed - 270.0f) / 180.0f) * PI;
	//	}
	//}
	//else {
	//	PlayerRot = -((AttackSpeed - 180.0f) / 180.0f) * PI;
	//}

	//攻撃後の硬直(この間にリンク判定する)
	if (AttackInterval > 0) {
		StartJoypadVibration(DX_INPUT_PAD1, 500, 2000);
		AttackInterval--;
		PlaySoundMem(attackSound, DX_PLAYTYPE_BACK);
	}
	else {
		//リンクが切れる
		AttackInterval = 0;
		StopJoypadVibration(DX_INPUT_PAD1);
	}

	//0から360まで範囲を指定する
	if (!Around) {
		if (PlayerSpeed > 360.0f) {
			PlayerSpeed = 0.0f;
		}

		if (PlayerSpeed < 0.0f) {
			PlayerSpeed = 360.0f;
		}
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
			PlayerRotDir = Dir;
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
		if (StunTimer % 10 == 0) {
			StunCount++;
		}
		if (StunTimer <= 0) {
			StunCount = 0;
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

	if (StunCount % 2 == 0) {
		DrawBillboard3D(VGet(playerPosX, playerPosY, 0), 0.5f, 0.5f, 50, PlayerRot, texture, true);

		for (int i = 0; i < EFFECTS_MAX; i++)
		{
			Effects[i]->Draw();
		}
	}

	stopEffects->Draw();

	DrawBillboard3D(VGet(AttackAreaX, AttackAreaY, 0), 0.5f, 0.5f, 100, 0.0f, targettexture, true);
}

void Player::FormatDraw() {
	/*DrawFormatString(0, 0, GetColor(0, 0, 0), "Speed:%f", PlayerSpeed);
	DrawFormatString(0, 20, GetColor(0, 0, 0), "Speed:%f", AfterSpeed);
	DrawFormatString(0, 40, GetColor(0, 0, 0), "Attack:%d", Attack);*/
	//DrawFormatString(0, 20, GetColor(0, 0, 0), "Speed:%f", AfterSpeed);
	//DrawFormatString(0, 40, GetColor(0, 0, 0), "frame:%f", frame);
	//DrawFormatString(0, 60, GetColor(0, 0, 0), "PlayerRot:%f", PlayerRot);
	//DrawFormatString(0, 80, GetColor(0, 0, 0), "Knock:%d", KnockCount);
	//DrawFormatString(0, 100, GetColor(0, 0, 0), "AttackStart:%d", AttackStart);
}