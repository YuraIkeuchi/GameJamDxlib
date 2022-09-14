#include"SceneManager.h"
#include "Vector3.h"
#include"FPS.h"

const char TITLE[] = "3002_リーサル";

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	ChangeWindowMode(TRUE);						//ウィンドウモードに設定
	//ウィンドウサイズを手動では変更できず、かつウィンドウサイズに合わせて拡大できないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);
	SetMainWindowText(TITLE);			
	SetWindowIconID(333);
	// タイトルを変更
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);	//画面サイズの最大サイズ、カラービット数を設定（モニターの解像度に合わせる）
	SetWindowSizeExtendRate(1.0);				//画面サイズを設定（解像度との比率で設定）
	SetBackgroundColor(0xFF, 0xFF, 0xFF);		// 画面の背景色を設定する

	//Dxライブラリの初期化
	if (DxLib_Init() == -1) { return -1; }

	//（ダブルバッファ）描画先グラフィック領域は裏面を指定
	SetDrawScreen(DX_SCREEN_BACK);

	//ゲームループで使う変数の宣言
	char keys[256] = { 0 }; //最新のキーボード情報用
	char oldkeys[256] = { 0 };//1ループ（フレーム）前のキーボード情報
	
	SceneManager *scene = new SceneManager;
	scene->StaticInit();

	struct XINPUT_STICK
	{
		unsigned char LeftTrigger; // 左トリガー( 0～255 )
		unsigned char RightTrigger; // 右トリガー( 0～255 )
		short ThumbLX; // 左スティックの横軸値( -32768 ～ 32767 )
		short ThumbLY; // 左スティックの縦軸値( -32768 ～ 32767 )
		short ThumbRX; // 右スティックの横軸値( -32768 ～ 32767 )
		short ThumbRY; // 右スティックの縦軸値( -32768 ～ 32767 )
	};

	//ボタン
	XINPUT_STATE input = { 0 };
	
	FPS fps(30.0f,800);

	// ゲームループ
	while (1)
	{
		//最新のキーボード情報だったものは１フレーム前のキーボード情報として保存
		for (int i = 0; i < 256; i++) {
			oldkeys[i] = keys[i];
		}
		//最新のキーボード情報を取得
		GetHitKeyStateAll(keys);
		//コントローラー情報
		XINPUT_STATE oldinput = input;
		GetJoypadXInputState(DX_INPUT_PAD1, &input);

		//画面クリア
		ClearDrawScreen();
	
		//カメラ
		Vector3 cameraOrgPosition(0.0f, 10.0f, -100.0f);
		Vector3 cameraPosition = cameraOrgPosition;

		Vector3 cameraOrgUp(0.0f, 1.0f, 0.0f);
		Vector3 cameraUp = cameraOrgUp;

		Vector3 cameraTarget(0.0f, 0.0f, 0.0f);

		float cameraUpAngle = 0.0f;

		//クリップ面
		SetCameraNearFar(1.0f, 10000.0f);
		SetCameraScreenCenter(WIN_WIDTH / 2.0f, WIN_HEIGHT / 2.0f);
		SetCameraPositionAndTargetAndUpVec(
			cameraPosition,
			cameraTarget,
			cameraUp);


		//---------  ここからプログラムを記述  ----------//

		if (scene->GetSceneTime() == 0)
		{
			scene->Init();
		}
		scene->Update(keys, oldkeys, input, oldinput);
		scene->Draw();

		fps.getFps();
		fps.wait();
		//---------  ここまでにプログラムを記述  ---------//
		ScreenFlip();//（ダブルバッファ）裏面
		// 20ミリ秒待機（疑似60FPS）
		//WaitTimer(20);
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
	delete scene;
	scene = nullptr;

	return 0;
}
