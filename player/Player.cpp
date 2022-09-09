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
	PlayerScale = 320.0f;
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
	KnockCount = 0;
	LockOnTexArea = 0.0f;
	LockOnArea = 0.0f;
	//ˆê‰ñ“à‘¤‚É“ü‚Á‚½‚©‚Ç‚¤‚©
	InArea = false;
	InAreaStart = false;
	//“G‚ðŽ~‚ß‚é‚½‚ß‚Ì•Ï”
	Stop = false;
	StopInterval = 5;
	//ˆÚ“®ŠÖŒW
	AddSpeed = 1.0f;
	AddVelocity = 0.0f;
	Speedframe = 0.0f;
	ChangeDir = false;
	Dir = RIGHT;
	//ƒ_ƒ[ƒWŠÖŒW
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
}

void Player::Update(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput) {
	if (!Stun) {
		//ˆÚ“®
		Move(keys, oldkeys, input, oldinput);
		//UŒ‚
		AttackMove(keys, oldkeys, input, oldinput);
	}
	//ƒXƒ^ƒ“ŠÖŒW
	PlayerStun();
	AttackArea();
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

	//‚Ç‚ÌƒT[ƒNƒ‹‚É‚¢‚é‚©‚Å•ÏX‚·‚é‚à‚Ì‚ª‚ ‚é
	if (PlayerScale == 80.0f) {
		LockOnTexArea = 200.0f;
		if(Dir == RIGHT){
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
		PlayerSpeed += AddSpeed + AddVelocity;
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

void Player::AttackArea() {
	//ˆÊ’u‚ð‹‚ß‚Ä‚¢‚é
	AttackRadius = AttackSpeed * PI / 180.0f;
	AttackCircleX = cosf(AttackRadius) * AttackScale;
	AttackCircleY = sinf(AttackRadius) * AttackScale;
	AttackAreaX = AttackCircleX + playerPosX;
	AttackAreaY = AttackCircleY + playerPosY;
}

void Player::PlayerStun() {
	//ƒ_ƒ[ƒWH‚ç‚Á‚½‚Æ‚«“®‚¯‚È‚¢
	if (Stun) {
		StunTimer--;
		if (StunTimer <= 0) {
			StunTimer = 100;
			Stun = false;
			Invisible = true;
		}
	}
	//ƒXƒ^ƒ“I‚í‚Á‚½‚Æ‚«ˆê’èŽžŠÔ–³“G
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
	DrawBillboard3D(VGet(AttackAreaX, AttackAreaY, 0), 0.5f, 0.5f, 100, 0.0f, targettexture, true);
	//DrawCircle(playerPosX, playerPosY, 20, GetColor(0, 0, 0), true);
}

void Player::FormatDraw() {
	DrawFormatString(0, 0, GetColor(0, 0, 0), "InArea:%d", InArea);
	DrawFormatString(0, 20, GetColor(0, 0, 0), "InAreaStart:%d", InAreaStart);
	//DrawFormatString(0, 60, GetColor(0, 0, 0), "AddSpeed:%f", AddSpeed);
	//DrawFormatString(0, 80, GetColor(0, 0, 0), "AddVelocity:%f", AddVelocity);
	//DrawFormatString(0, 20, GetColor(0, 0, 0), "AttackStart:%d", AttackStart);
	//DrawFormatString(0, 40, GetColor(0, 0, 0), "Attack:%d", Attack);
}