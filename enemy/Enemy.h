#pragma once
#include "Share.h"
#include "Player.h"
#include "AttackEffect.h"
#include "BreakEffect.h"
#include "TimeEffect.h"
#include "Particle.h"
class Enemy {
public:
	//コンストラクタ
	Enemy();
	//デストラクタ
	~Enemy();
	//初期化
	void Initialize();
	//更新
	void Update(Player* player);
	//チュートリアル更新
	void TutorialUpdate(Player* player);
	//生成
	void ResPorn();
	//生成場所設置
	void Pattern(float Speed, int TargetLine, int Dir);
	//移動
	void Move(Player* player);
	//攻撃範囲内
	void InArea(Player* player);
	//標的
	void Target(Player* player);
	//停止
	void Stop(Player* player);
	//当たり判定(エネミーが死ぬ)
	bool Collide(Player* player);
	//当たり判定(プレイヤーがスタンする)
	bool PlayerCollide(Player* player);
	//ロックオン当たり判定(プレイヤーがスタンする)
	bool LockOnCollide(Player* player);
	void VanishEnemy();
	//描画
	void Draw(Player* player);
	//FormatString用
	void FormatDraw(int EnemyCount);
public:
	//getter setter
	const float& GetScale() { return EnemyScale; }
	const float& GetPositionX() { return EnemyPosX; }
	const float& GetPositionY() { return EnemyPosY; }
	const bool& GetAttackArea() { return InAttackArea; }
	const bool& GetDeathEnemy() { return DeathEnemy; }
	void SetStop(bool Stop) { this->EnemyStop = Stop; }
	void SetDir(int Dir) { this->Dir = Dir; }
	void SetEnemyTimer(int EnemyTimer) { this->EnemyTimer = EnemyTimer; }
	void SetTutorialMove(bool TutorialMove) { this->TutorialMove = TutorialMove; }
	void SetSpeed(float EnemySpeed) { this->EnemySpeed = EnemySpeed; }
	void SetDeathEnemy(bool DeathEnemy) { this->DeathEnemy = DeathEnemy; }
	void SetTargetLine(int TargetLine) { this->TargetLine = TargetLine; }
	void SetEnemyTex(int tex) { this->texture = tex; }
	void SetRespornTex(int tex) { this->Resporntexture = tex; }
	void SetTargetEnemyTex(int tex) { this->Targettexture = tex; }
	void SetStopTex(int tex) { this->Stoptexture = tex; }
private:
	int texture = 0;
	int Resporntexture = 0;
	int Targettexture = 0;
	int Stoptexture = 0;
	//メンバ変数
	//座標
	float EnemyPosX;
	float EnemyPosY;
	//大きさ
	float size;
	//円運動のための変数
	float x;
	float y;
	float EnemyRadius;
	//0から360までの円周
	float EnemySpeed;
	//一周したかどうかの判定を取るための円周
	float EnemyRoundSpeed;
	float EnemyScale;
	float EnemyCircleX;
	float EnemyCircleY;
	float EnemyAdd;
	//チュートリアルの変数
	bool TutorialMove;
	//リスポーン関係
	bool EnemyAlive;
	bool DeathEnemy;
	int EnemyTimer;
	bool EnemyMove;
	bool EnemySet;
	int TargetLine;
	//敵が止まっているか
	bool EnemyStop;
	int EnemyStopTimer;
	float StopPos;
	float SizeAngle;
	float SizeAngle2;
	//保存用変数
	float EnemySaveSpeed;
	//プレイヤーと敵の位置の距離
	float DistanceScale;
	float DistanceSpeed;
	//攻撃範囲
	bool InAttackArea;

	int Dir;

	//円の半径の移動関係
	float AfterScale;
	bool MoveLine;
	bool Vanish;
	float frame;
	//照準に関する変数
	bool TargetShrink;
	float Targetframe;
	float TargetSize;
	//パーティクル関係
	int ParticleCount;
	float ParticlePosX;
	float ParticlePosY;
	enum MoveDir {
		RIGHT,
		LEFT,
	};

	enum PlayerDir {
		PLAYERRIGHT,
		PLAYERLEFT,
	};
	unique_ptr<TimeEffect> timeEffects;
	unique_ptr<AttackEffect> effects;
	unique_ptr<BreakEffect> breakEffects;
	unique_ptr<Particle> particle;
};