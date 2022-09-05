#include "DxLib.h"
#include "math.h"
const char TITLE[] = "学籍番号名前：タイトル";

const int WIN_WIDTH = 800; //ウィンドウ横幅
const int WIN_HEIGHT = 600;//ウィンドウ縦幅

const int Enemy_Max = 3;
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	ChangeWindowMode(TRUE);						//ウィンドウモードに設定
	//ウィンドウサイズを手動では変更できず、かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetMainWindowText(TITLE);					// タイトルを変更
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);	//画面サイズの最大サイズ、カラービット数を設定（モニターの解像度に合わせる）
	SetWindowSizeExtendRate(1.0);				//画面サイズを設定（解像度との比率で設定）
	SetBackgroundColor(0xFF, 0xFF, 0xFF);		// 画面の背景色を設定する

	//Dxライブラリの初期化
	if (DxLib_Init() == -1) { return -1; }

	//（ダブルバッファ）描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	//画像などのリソースデータの変数宣言と読み込み



	//ゲームループで使う変数の宣言
	char keys[256] = { 0 }; //最新のキーボード情報用
	char oldkeys[256] = { 0 };//1ループ（フレーム）前のキーボード情報
	float PI = 3.14f;

	float x = WIN_WIDTH / 2;
	float y = WIN_HEIGHT / 2;

	float playerPosX = WIN_WIDTH / 2;
	float playerPosY = WIN_HEIGHT / 2;

	float Playerradius = 0.0f;
	float PlayerSpeed = 0.0f;
	float Playerscale = 80.0f;// LaneNumと一緒に変えること
	float PlayerCircleX = 0.0f;
	float PlayerCircleY = 0.0f;
	float add = 1.0f;


	float EnemyPosX[Enemy_Max];
	float EnemyPosY[Enemy_Max];
	float Enemyradius[Enemy_Max];
	float EnemySpeed[Enemy_Max];
	float EnemySaveSpeed[Enemy_Max];
	float Enemyscale[Enemy_Max]; //LaneNumと一緒に変えること
	float EnemyCircleX[Enemy_Max];
	float EnemyCircleY[Enemy_Max];
	float Enemyadd[Enemy_Max];
	bool EnemyAlive[Enemy_Max];
	int EnemyTimer[Enemy_Max];
	bool EnemyMove[Enemy_Max];
	bool EnemySet[Enemy_Max];
	int TargetLine[Enemy_Max];
	for (int i = 0; i < Enemy_Max; i++) {
		EnemyPosX[i] = 0.0f;
		EnemyPosY[i] = 0.0f;
		Enemyradius[i] = 0.0f;
		EnemySpeed[i] = 0.0f;
		Enemyscale[i] = 500.0f;
		EnemyCircleX[i] = 0.0f;
		EnemyCircleY[i] = 0.0f;
		Enemyadd[i] = 0.0f;
		EnemyAlive[i] = false;
		EnemyTimer[i] = 0;
		EnemyMove[i] = false;
		EnemySet[i] = false;
		TargetLine[i] = 0;
		EnemySaveSpeed[i] = 0.0f;
	}
	// ゲームループ
	while (1)
	{
		//最新のキーボード情報だったものは１フレーム前のキーボード情報として保存
		for (int i = 0; i < 256; i++) {
			oldkeys[i] = keys[i];
		}
		//最新のキーボード情報を取得
		GetHitKeyStateAll(keys);

		//画面クリア
		ClearDrawScreen();
		//---------  ここからプログラムを記述  ----------//

		//更新処理
		if (keys[KEY_INPUT_DOWN] == 1 && oldkeys[KEY_INPUT_DOWN] == 0) {
			if (Playerscale > 81.0f) {
				Playerscale -= 40.0f;
			}
		}

		if (keys[KEY_INPUT_UP] == 1 && oldkeys[KEY_INPUT_UP] == 0) {
			if (Playerscale < 201.0f) {
				Playerscale += 40.0f;
			}
		}
	
		if (keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0) {
			add = -add;
		}

		PlayerSpeed += add;

		//プレイヤー
		Playerradius = PlayerSpeed * PI / 180.0f;
		PlayerCircleX = cosf(Playerradius) * Playerscale;
		PlayerCircleY = sinf(Playerradius) * Playerscale;
		playerPosX = PlayerCircleX + x;
		playerPosY = PlayerCircleY + y;
		//エネミー
		for (int i = 0; i < Enemy_Max; i++) {
			if (!EnemyAlive[i]) {
				EnemyTimer[i]++;

				if (EnemyTimer[i] == 200) {
					Enemyscale[i] = rand() % 400 + 200;
					EnemySpeed[i] = rand() % 360;
					Enemyadd[i] = 1;
					TargetLine[i] = 4;
					EnemyAlive[i] = true;
					EnemyTimer[i] = false;
					EnemySet[i] = true;
				}
			}

			if (EnemySet[i]) {
				if (TargetLine[i] == 0) {
					if (Enemyscale[i] >= 80.0f) {
						Enemyscale[i] -= 5.0f;
					}
					else {
						EnemySet[i] = false;
						EnemyMove[i] = true;
						EnemySaveSpeed[i] = EnemySpeed[i];
						Enemyscale[i] = 80.0f;
					}
				}
				else if (TargetLine[i] == 1) {
					if (Enemyscale[i] >= 120.0f) {
						Enemyscale[i] -= 5.0f;
					}
					else {
						EnemySet[i] = false;
						EnemyMove[i] = true;
						Enemyscale[i] = 120.0f;
					}
				}
				else if (TargetLine[i] == 2) {
					if (Enemyscale[i] >= 160.0f) {
						Enemyscale[i] -= 5.0f;
					}
					else {
						EnemySet[i] = false;
						EnemyMove[i] = true;
						EnemySaveSpeed[i] = EnemySpeed[i];
						Enemyscale[i] = 160.0f;
					}
				}
				else if (TargetLine[i] == 3) {
					if (Enemyscale[i] >= 200.0f) {
						Enemyscale[i] -= 5.0f;
					}
					else {
						EnemySet[i] = false;
						EnemyMove[i] = true;
						EnemySaveSpeed[i] = EnemySpeed[i];
						Enemyscale[i] = 200.0f;
					}
				}
				else if (TargetLine[i] == 4) {
					if (Enemyscale[i] >= 240.0f) {
						Enemyscale[i] -= 5.0f;
					}
					else {
						EnemySet[i] = false;
						EnemyMove[i] = true;
						EnemySaveSpeed[i] = EnemySpeed[i];
						Enemyscale[i] = 240.0f;
					}
				}
			}
		}

		for (int i = 0; i < Enemy_Max; i++) {
			if (EnemyMove[i]) {
				if (EnemySpeed[i] == EnemySaveSpeed[i] + 360.0f) {
					Enemyscale[i] -= 40.0f;
					EnemySaveSpeed[i] = EnemySpeed[i];
				}
			}
		}

		for (int i = 0; i < Enemy_Max; i++) {
			Enemyradius[i] = EnemySpeed[i] * PI / 180.0f;
			EnemyCircleX[i] = cosf(Enemyradius[i]) * Enemyscale[i];
			EnemyCircleY[i] = sinf(Enemyradius[i]) * Enemyscale[i];
			EnemyPosX[i] = EnemyCircleX[i] + x;
			EnemyPosY[i] = EnemyCircleY[i] + y;
			if (EnemyMove[i]) {
				EnemySpeed[i] += Enemyadd[i];
			}
		}


		//描画処理
		DrawCircle(x, y, 240,GetColor(255,0,0), false);
		DrawCircle(x, y, 200, GetColor(255, 0, 0), false);
		DrawCircle(x, y, 160, GetColor(0, 255, 0), false);
		DrawCircle(x, y, 120, GetColor(0, 0, 255), false);
		DrawCircle(x, y, 80, GetColor(0, 0, 255), false);
		DrawCircle(playerPosX, playerPosY, 10, GetColor(0, 0, 0), true);
		for (int i = 0; i < Enemy_Max; i++) {
			DrawCircle(EnemyPosX[i], EnemyPosY[i], 10, GetColor(255, 255, 0), true);
			DrawFormatString(0, (20 * i) + 40, GetColor(0, 0, 0), "Save[%d]:%f", i,EnemySaveSpeed[i]);
			DrawFormatString(0, (20 * i) + 100, GetColor(0, 0, 0), "Speed[%d]:%f", i, EnemySpeed[i]);
		}
		DrawFormatString(0, 0, GetColor(0, 0, 0), "scale:%f", Playerscale);
		DrawFormatString(0, 20, GetColor(0, 0, 0), "add:%f", add);
		//---------  ここまでにプログラムを記述  ---------//
		ScreenFlip();//（ダブルバッファ）裏面
		// 20ミリ秒待機（疑似60FPS）
		WaitTimer(20);
		// Windows システムからくる情報を処理する
		if (ProcessMessage() == -1)
		{
			break;
		}
		// ＥＳＣキーが押されたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
		{
			break;
		}
	}
	//Dxライブラリ終了処理
	DxLib_End();

	return 0;
}