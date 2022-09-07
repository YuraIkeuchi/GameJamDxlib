#include"Emitter.h"
#include"DxLib.h"

const int WIN_HEIGHT = 400;
Emitter::Emitter() {
	circleG = 0;
	isAlive = 0;
	//�v���C���[
	boxX = 100;
	boxY = 100;
	boxR = 20;
	boxR2 = 20;
}

bool Emitter::getIsAlive() { return isAlive; }

void Emitter::move(char keys[255]) {
	//�v���C���[�̈ړ�
	GetMousePoint(&boxX, &boxY);

	//�v���C���[�̃T�C�Y�ύX
	if (keys[KEY_INPUT_W] == 1) {
		boxR2++;
	}

	if (keys[KEY_INPUT_S] == 1 && boxR2 >= 5) {
		boxR2--;
	}

	if (keys[KEY_INPUT_A] == 1 && boxR >= 5) {
		boxR--;
	}

	if (keys[KEY_INPUT_D] == 1) {
		boxR++;;
	}
}

void Emitter::activate() {
	//�e�̔���
	isAlive = 1;
	circleX = GetRand(boxR * 2) + boxX - boxR;//GetRand(player->getBoxX() * 2) + player->getBoxX() - player->getBoxR();
	circleY = GetRand(boxR2 * 2) + boxY - boxR2;//GetRand(player->getBoxR2() * 2) + player->getBoxY() - player->getBoxR();
	circleR = 5;
	circleG = 0;
}

void Emitter::drop() {
	//�e�̗���
	if (isAlive == 1) {
		circleY = circleY + 9.8 * (circleG / 50.0);
		circleG++;

		if (circleY > WIN_HEIGHT) {
			isAlive = 0;
		}
	}
}

void Emitter::draw() {
	if (isAlive == 1) {
		DrawBox(boxX - boxR, boxY - boxR2, boxX + boxR, boxY + boxR2, GetColor(255, 255, 255), FALSE);
		DrawCircle(circleX, circleY, circleR, GetColor(255, 255, 255), TRUE);
	}
}