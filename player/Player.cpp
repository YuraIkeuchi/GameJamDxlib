#include "Player.h"
#include "Easing.h"
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
	x = 0;
	y = 0;
	PlayerRadius = 0.0f;
	PlayerSpeed = 0.0f;
	PlayerScale = 80.0f;// LaneNum‚Æˆê‚É•Ï‚¦‚é‚±‚Æ
	PlayerCircleX = 0.0f;
	PlayerCircleY = 0.0f;
	//UŒ‚ŠÖŒW
	Attack = false;
	AttackStart = false;
	AfterScale = 0.0f;
	AfterSpeed = 0.0f;
	frame = 0.0f;
	AttackTimer = 0;
	AttackCount = 0;
	AttackInterval = 0;
	//“G‚ðŽ~‚ß‚é‚½‚ß‚Ì•Ï”
	Stop = false;
	StopInterval = 5;
	//ˆÚ“®ŠÖŒW
	AddSpeed = 1.0f;
	Speedframe = 0.0f;
	ChangeDir = false;
	Dir = RIGHT;
}

void Player::Update(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput) {
	//ˆÚ“®
	Move(keys, oldkeys,input,oldinput);
	//UŒ‚
	AttackMove(keys, oldkeys, input, oldinput);
}

void Player::Move(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput) {
	//ƒvƒŒƒCƒ„[
	//ƒT[ƒNƒ‹•ÏX
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

	//ˆÚ“®•ûŒü•ÏŠ·
	//(‰EŒü‚«‚É‚È‚é)
	if (input.RightTrigger && !oldinput.RightTrigger
		&& (Dir == LEFT)) {
		
		Speedframe = 0.0f;
		Dir = RIGHT;
		ChangeDir = true;
	}

	//(‰EŒü‚«‚É‚È‚é)
	if (input.LeftTrigger && !oldinput.LeftTrigger
		&& (Dir == RIGHT)) {
		Speedframe = 0.0f;
		Dir = LEFT;
		ChangeDir = true;
	}

	//Œü‚«‚ð•Ï‚¦‚½‚Æ‚«™X‚É•Ï‚í‚é
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

	//“G‚ðŽ~‚ß‚é
	if (input.Buttons[XINPUT_BUTTON_B] && !oldinput.Buttons[XINPUT_BUTTON_B] && !Stop) {
		Stop = true;
	}
	//“G‚ðŽ~‚ß‚Ä‚éŽžŠÔ
	if (Stop) {
		StopInterval--;
		if (StopInterval == 0) {
			Stop = false;
			StopInterval = 5;
		}
	}
	//ˆÚ“®—Ê‚ð‰ÁŽZ‚µ‚Ä‚¢‚é(UŒ‚Œã‚Ìd’¼ŒãˆÈŠO)
	if (AttackInterval == 0) {
		PlayerSpeed += AddSpeed;
	}

	//UŒ‚Œã‚Ìd’¼(‚±‚ÌŠÔ‚ÉƒŠƒ“ƒN”»’è‚·‚é)
	if (AttackInterval > 0) {
		AttackInterval--;
	}
	else {
		//ƒŠƒ“ƒN‚ªØ‚ê‚é
		AttackInterval = 0;
		AttackCount = 0;
	}

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

void Player::AttackMove(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput) {
	//“G‚ÉUŒ‚‚·‚é
	if (input.Buttons[XINPUT_BUTTON_A] && !oldinput.Buttons[XINPUT_BUTTON_A] && !Attack && !AttackStart) {
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

	//“G‚ÌˆÊ’u‚Ü‚Åeasing
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