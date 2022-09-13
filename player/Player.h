#pragma once
#include "Share.h"
#include "DxLib.h"
#include "MoveEffect.h"
#include "StopEffect.h"

constexpr int EFFECTS_MAX = 31;
#include <vector>
#include <memory>
#include <list> // ヘッダファイルインクルード
using namespace std;         //  名前空間指定
class Player {
public:
	//コンストラクタ
	Player();
	//デストラクタ
	~Player();

	//初期化
	void Initialize(int soundBolume);
	//更新
	void Update(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput);
	//移動
	void Move(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput);
	//攻撃
	void AttackMove(char keys[255], char oldkeys[255], XINPUT_STATE input, XINPUT_STATE oldinput);
	//攻撃エリア
	void AttackArea();
	//スタン
	void PlayerStun();
	//描画
	void Draw();
	//FormatString用
	void FormatDraw();
public:
	//getter setter（結構増えちゃうかも申し訳ない)
	const float& GetScale() { return PlayerScale; }
	const float& GetSpeed() { return PlayerSpeed; }
	const float& GetAfterSpeed() { return AfterSpeed; }
	const bool& GetStop() { return Stop; }
	const bool& GetInArea() { return InArea; }
	const bool& GetInAreaStart() { return InAreaStart; }
	const bool& GetAttack() { return Attack; }
	const bool& GetInvisible() { return Invisible; }
	const bool& GetStun() { return Stun; }
	const bool& GetAttackStart() { return AttackStart; }
	const int& GetAttackInterval() { return AttackInterval; }
	const int& GetKnockCount() { return KnockCount; }
	const float& GetPositionX() { return playerPosX; }
	const float& GetPositionY() { return playerPosY; }
	const float& GetAttackAreaX() { return AttackAreaX; }
	const float& GetAttackAreaY() { return AttackAreaY; }

	void SetSpeed(float PlayerSpeed) { this->PlayerSpeed = PlayerSpeed; }
	void SetScale(float PlayerScale) { this->PlayerScale = PlayerScale; }
	void SetBoundDir(int BoundDir) { this->BoundDir = BoundDir; }
	void SetBoundPower(float BoundPower) { this->BoundPower = BoundPower; }
	void SetAfterScale(float AfterScale) { this->AfterScale = AfterScale; }
	void SetAfterSpeed(float AfterSpeed) { this->AfterSpeed = AfterSpeed; }
	void SetAttackStart(bool AttackStart) { this->AttackStart = AttackStart; }
	void SetAttackInterval(int AttackInterval) { this->AttackInterval = AttackInterval; }
	void SetKnockCount(int KnockCount) { this->KnockCount = KnockCount; }
	void SetFrame(float frame) { this->frame = frame; }
	void SetStun(bool Stun) { this->Stun = Stun; }
	void SetInArea(bool InArea) { this->InArea = InArea; }
	void SetAround(bool Around) { this->Around = Around; }
	void SetInAreaStart(bool InAreaStart) { this->InAreaStart = InAreaStart; }
	void SetSound(bool Sound) { this->PlayerSound = Sound; }

	void SetPlayer(int _player) { this->texture = _player; }
	void SetTargetArea(int _targetarea) { this->targettexture = _targetarea; }
private:
	//メンバ変数
	int texture = 0;
	int targettexture = 0;
	//座標
	float playerPosX;
	float playerPosY;
	//円運動のための変数
	float x;
	float y;
	float PlayerRadius;
	float PlayerSpeed;
	float PlayerScale;// LaneNumと一緒に変えること
	float PlayerCircleX;
	float PlayerCircleY;
	float BoundPower;
	//攻撃関係
	bool Attack;
	bool AttackStart;
	float AfterScale;
	float AfterSpeed;
	float frame;
	int AttackTimer;
	//一回内側に入ったかどうか
	bool InArea;
	bool InAreaStart;
	//二回目以降
	int AttackInterval;
	//ロックオン範囲(デバッグ表示用)
	float LockOnTexArea;
	//実際の表示エリア
	float LockOnArea;
	//敵を倒した数
	int KnockCount;
	//敵を止めるための変数
	bool Stop;
	int StopInterval;
	//移動関係
	float AddSpeed;
	float AddVelocity;
	float Speedframe;
	bool ChangeDir;
	int Dir;
	int PlayerRotDir;
	float PlayerRot;

	enum MoveDir {
		RIGHT,
		LEFT,
	};
	enum RotDir {
		ROTRIGHT,
		ROTLEFT,
	};
	//ダメージ関係
	bool Stun;
	int StunTimer;
	int StunCount;
	int BoundDir;
	bool Invisible;
	int InvisibleTimer;
	bool Around;
	enum HitDir {
		NOHIT,
		HITRIGHT,
		HITLEFT,
	};
	//攻撃エリア関係(ほんとは別クラスにやりたい)
	float AttackRadius;
	float AttackAreaX;
	float AttackAreaY;
	float AttackScale;
	float AttackSpeed;
	float AttackCircleX;
	float AttackCircleY;
	//コントローラ関係
	float InputX;
	float InputY;
	float Joyangle;

	unique_ptr<MoveEffect> Effects[EFFECTS_MAX] = {};
	unique_ptr<StopEffect> stopEffects = nullptr;
	int attackSound;
	bool PlayerSound;
	int enemyStopSound;
	int enemyHitSound;

	int stopTexture;
};