#include "DxLib.h"
#include "math.h"
#include "Share.h"
#include "Player.h"
#include "Enemy.h"
#include "StageCircle.h"
#include<time.h>

const char TITLE[] = "学籍番号名前：タイトル";

const int Enemy_Max = 5;
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
	
	//クラス宣言
	// 	//エネミー
	Enemy* enemy[Enemy_Max];
	for (int i = 0; i < Enemy_Max; i++) {
		enemy[i] = new Enemy();
	}
	//プレイヤー
	Player* player = nullptr;
	player = new Player();
	//ステージ上の円
	StageCircle* stagecircle = nullptr;
	stagecircle = new StageCircle();

	float x = WIN_WIDTH / 2;
	float y = WIN_HEIGHT / 2;

	srand(time(NULL));
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
		//プレイヤー
		player->Update(keys, oldkeys);
		//エネミー
		for (int i = 0; i < Enemy_Max; i++) {
			enemy[i]->Update(player);
		}
	
		//描画処理
		//ステージ上の円
		stagecircle->Draw();

		//プレイヤー
		player->Draw();
		player->FormatDraw();

		//エネミー
		for (int i = 0; i < Enemy_Max; i++) {
			enemy[i]->Draw();
			enemy[i]->FormatDraw(i);
		}
		
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
