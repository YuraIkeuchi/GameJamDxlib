#pragma once
class Emitter {
private:
	//�e�̕`��
	int circleX;
	int circleY;
	int circleR;
	int circleG;
	bool isAlive;
	//�v���C���[�̍��W
	int boxX;
	int boxY;
	int boxR;
	int boxR2;
public:
	Emitter();

	bool getIsAlive();
	void move(char keys[255]);
	void activate();
	void drop();
	void draw();

	void setBoxX(int boxX);
	void setBoxY(int boxY);
	void setBoxR(int boxR);
	void setBoxR2(int boxR2);
};