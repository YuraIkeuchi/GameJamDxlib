#include "Particle.h"
constexpr auto ALPHA_MAX = 255;
Particle::Particle() {

}

void Particle::Initialize() {
	for (int i = 0; i < Particle_Max; i++) {
		Alive[i] = false;
		speed[i] = 0.0f;
		alpha[i] = ALPHA_MAX;
		scale[i] = 50.0f;
		particlePosX[i] = 0.0f;
		particlePosY[i] = 0.0f;
		x[i] = 0.0f;
		y[i] = 0.0f;
		radius[i] = 0.0f;
	}

	StartPosX = 0.0f;
	StartPosY = 0.0f;
	ParticleType = 0;
	EndCount = 0;
	ParticleBreak = false;
	StartScale = 30.0f;
	AddScale = 2.0f;
}

void Particle::Update(float StartPosX, float StartPosY, int Timer, int TargetTimer) {

	NormalParticle(StartPosX,StartPosY, Timer, TargetTimer);
	
}

void Particle::Draw() {
	for (int i = 0; i < Particle_Max; i++) {
		if (Alive[i]) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha[i]);		//ブレンドモードをα(128/255)に設定
			if (alpha[i] <= 200.0f) {
				DrawBillboard3D(VGet(particlePosX[i], particlePosY[i], 0.0f), 0.5f, 0.5f, particleR[i], 0.0f, texture, true);
			}
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		//ブレンドモードをオフ
		}
	}

	//DrawFormatString(0, 200, GetColor(0, 0, 0), "Alive:%f", particleR[0]);
	//DrawFormatString(0, 220, GetColor(0, 0, 0), "angle[0]:%f", angle[0]);
	//DrawFormatString(0, 240, GetColor(0, 0, 0), "angle[1]:%f", angle[1]);
	//DrawFormatString(0, 260, GetColor(0, 0, 0), "speed:%f", speed[0]);
	//DrawFormatString(0, 260, GetColor(0, 0, 0), "PosY:%f", PosY[0]);
}


void Particle::NormalParticle(float StartPosX, float StartPosY, int Timer, int TargetTimer) {
	this->StartPosX = StartPosX;
	this->StartPosY = StartPosY;
	if (Timer >= TargetTimer) {
		for (int i = 0; i < Particle_Max; i++) {
			if (!Alive[i]) {
				angle[i] = GetRand(360);//角度調整
				Alive[i] = true;//フラグの変更
				alpha[i] = ALPHA_MAX;//ブレンド値の初期化
				speed[i] = 0.1f;//スピードの初期化
				particleR[i] = 25.0f;//半径
				particlePosX[i] = this->StartPosX;
				particlePosY[i] = this->StartPosY;
				break;
			}

		}
	}

	for (int i = 0; i < Particle_Max; i++) {
		if (Alive[i]) {
			particlePosX[i] += cos(angle[i]) * speed[i];//位置に角度とスピードを足してる
			particlePosY[i] += sin(angle[i]) * speed[i];//位置に角度とスピードを足してる
			alpha[i] -= 2;//ブレンド値を減らしてる
			speed[i] += 0.01f;//弾の速さを上げてる
			particleR[i] -= 0.1f;//半径の大きさを下げる
			if (alpha[i] <= 0) {
				Alive[i] = 0;
				particleR[i] = 0.0f;
			}
		}
	}
}
