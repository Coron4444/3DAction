//================================================================================
//!	@file	 main.cpp
//!	@brief	 メイン
//! @details 
//!	@author  Kai Araki									@date 2017/09/01
//================================================================================



//****************************************
// インクルード文
//****************************************
#include <windows.h>
#include <crtdbg.h>
#include <assert.h>

#include "main.h"

#include <SafeRelease/SafeRelease.h>
#include <GameSystem\GameSystem.h>



//****************************************
// 定数定義
//****************************************
static const char* CLASS_NAME = "DirectXProject";
static const char* WINDOW_NAME = "DirectXゲーム";
static const DWORD WINDOW_STYLE = WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME | WS_MAXIMIZEBOX);



//****************************************
// プロトタイプ宣言
//****************************************
HWND Create_Window(HINSTANCE hInstance, int nCmdShow);
void RegistrationWindowClassEx(HINSTANCE hInstance);
void SetClientAreaSize(int* window_width, int* window_height);
void SetWindowPositionCenter(int* window_position_x, int* window_position_y,
							 int* window_width, int* window_height);
void MessageAndGameLoop(HINSTANCE hInstance, HWND window_handle, MSG* message);
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// ImGUIマウス操作
//#ifdef _DEBUG
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
//#endif



//--------------------------------------------------
// -アプリケーションのエントリー関数
//--------------------------------------------------
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevinstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 使っていない引数の処理
	lpCmdLine = lpCmdLine;
	hPrevinstance = hPrevinstance;

	// メモリリーク検出
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);
	//_CrtSetBreakAlloc(11526);


	// ウィンドウの作成
	HWND window_handle = Create_Window(hInstance, nCmdShow);

	// メッセージ&ゲームループ
	MSG message;
	MessageAndGameLoop(hInstance, window_handle, &message);

	return (int)message.wParam;
}



//--------------------------------------------------
// -ウィンドウの作成関数
//--------------------------------------------------
HWND Create_Window(HINSTANCE hInstance, int nCmdShow)
{
	// ウィンドウ用データ
	int window_position_x = 0;
	int window_position_y = 0;
	int window_width = 0;
	int window_height = 0;

	// ウィンドウクラスExの登録
	RegistrationWindowClassEx(hInstance);

	// クライアント領域のサイズ設定
	SetClientAreaSize(&window_width, &window_height);

	// ウィンドウの場所を中央に変更
	SetWindowPositionCenter(&window_position_x, &window_position_y,
							&window_width, &window_height);

	// ウィンドウの作成(登録されているウィンドウクラスを基盤とする)
	HWND window_handle = CreateWindowEx(0,					// 拡張ウィンドウスタイル
										CLASS_NAME,			// ウィンドウの名前
										WINDOW_NAME,		// ウィンドウ上部に表示される名前
										WINDOW_STYLE,		// ウィンドウスタイル
										window_position_x,	// ウィンドウのＸ座標
										window_position_y,	// ウィンドウのＹ座標
										window_width, 		// ウィンドウの幅
										window_height,		// ウィンドウの高さ
										NULL,				// 親ウィンドウのハンドル
										NULL,				// メニューの有無
										hInstance,			// インスタンスハンドル
										NULL);				// メッセージに渡されるパラメータ

	// ウィンドウを表示状態にする
	ShowWindow(window_handle, nCmdShow);

	// ウィンドウのクライアント領域を更新する
	UpdateWindow(window_handle);

	return window_handle;
}



//--------------------------------------------------
// -WindowClassExの登録関数(Windowの汎用的は設定)
//--------------------------------------------------
void RegistrationWindowClassEx(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);					// 構造体のサイズ
	wcex.style = CS_VREDRAW | CS_HREDRAW;				// ウィンドウスタイル
	wcex.lpfnWndProc = WndProc;							// このウィンドウのメッセージを受け取るコールバック関数へのポインタ
	wcex.cbClsExtra = 0;								// ウィンドウクラス構造体の後ろに割り当てる補足バイト数
	wcex.cbWndExtra = 0;								// ウィンドウインスタンスの後ろに割り当てる補足バイト数
	wcex.hInstance = hInstance;							// このウィンドウの為のウィンドウプロシージャのあるインスタンスハンドル
	wcex.hIcon = NULL;									// アイコンのハンドル
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);			// マウスカーソルのハンドル
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);	// ウィンドウ背景色(背景描画用ブラシのハンドル)
	wcex.lpszMenuName = NULL;							// デフォルトメニュー名
	wcex.lpszClassName = CLASS_NAME;					// ウィンドウの名前
	wcex.hIconSm = NULL;								// 16×16の小さいサイズのアイコン


	// WNDCLASSEX型のwcexの中身を登録
	RegisterClassEx(&wcex);
}



//--------------------------------------------------
// -クライアント領域のサイズ設定関数
//--------------------------------------------------
void SetClientAreaSize(int* window_width, int* window_height)
{
	// クライアント領域の座標を示す矩形データ
	RECT wr = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

	// 指定したクライアント領域のサイズ+メニューバーなどの領域のサイズを合計した矩形データを算出
	AdjustWindowRect(&wr,			// クライアント領域の座標を示す矩形データ 
					 WINDOW_STYLE,	// ウィンドウスタイル
					 FALSE);		// メニューの有無

	// 算出された矩形からウィンドウサイズを算出
	*window_width = wr.right - wr.left;
	*window_height = wr.bottom - wr.top;
}



//--------------------------------------------------
// -ウィンドウ座標を中央に設定関数
//--------------------------------------------------
void SetWindowPositionCenter(int* window_position_x, int* window_position_y,
							 int* window_width, int* window_height)
{
	// デスクトップサイズ(デスクトップの矩形データ)の取得
	RECT desktop_rect;
	GetWindowRect(GetDesktopWindow(), &desktop_rect);

	// ウィンドウを中央にするときのウィンドウの座標を算出
	*window_position_x = (desktop_rect.right - *window_width) / 2;
	*window_position_y = (desktop_rect.bottom - *window_height) / 2;

	// ウィンドウ座標が画面より大きいかどうか
	if ((desktop_rect.right - desktop_rect.left) < *window_position_x)
	{
		*window_position_x = 0;
	}
	if ((desktop_rect.bottom - desktop_rect.top) < *window_position_y)
	{
		*window_position_y = 0;
	}
}



//--------------------------------------------------
// -メッセージ&ゲームループ関数
//--------------------------------------------------
void MessageAndGameLoop(HINSTANCE hInstance, HWND window_handle, MSG* message)
{
	// ゲームシステムの作成
	GameSystem* game_system = new GameSystem();

	// ゲームシステムの初期化
	bool is_init = game_system->Init(hInstance, window_handle, TRUE, SCREEN_WIDTH, SCREEN_HEIGHT);
	assert(is_init && "初期化に失敗しました!!(main.cpp)");

	// タイマー用変数
	DWORD time = timeGetTime();
	DWORD old_time = timeGetTime();

	// タイマーの性能を上げる
	timeBeginPeriod(1);

	for (; ;)
	{
		// メッセージ処理
		if (PeekMessage(message, NULL, 0, 0, PM_REMOVE))
		{
			// 終了メッセージが来たら抜ける
			if (message->message == WM_QUIT)
			{
				break;
			}
			else
			{
				TranslateMessage(message);
				DispatchMessage(message);
			}
		}
		else
		{// ゲーム処理

			// 現在の時間を保存
			time = timeGetTime();

			// 1000ms / 60ごとに処理(60FPS)
			if ((time - old_time) >= (1000 / 60))
			{
				// ゲームシステムの更新
				game_system->Update();

				// ゲームシステムの描画
				game_system->Draw();

				// 後更新
				game_system->LateUpdate();

				// 前回の時刻の更新
				old_time = time;
			}
		}
	}

	// ゲームシステムの終了処理
	game_system->Uninit();
	SafeRelease::Normal(&game_system);

	// タイマーの性能を戻す
	timeEndPeriod(1);
}



//--------------------------------------------------
// -ウィンドウプロシージャ関数
//--------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

//#ifdef _DEBUG
	// ImGUIマウス操作
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam)) return true;
//#endif

	switch (uMsg)
	{
		case WM_DESTROY:
		{// ウィンドウ破棄メッセージ

			PostQuitMessage(0);
			break;
		}
		case WM_KEYDOWN:
		{// キーボード入力

			switch (wParam)
			{
				case VK_ESCAPE:
				{// Escキー

					int nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO | MB_DEFBUTTON2);

					if (nID == IDYES)
					{
						DestroyWindow(hWnd);
					}
					break;
				}
			}
			break;
		}
		case WM_CLOSE:
		{// ×ボタン

			int nID = MessageBox(hWnd, "終了しますか？", "終了メッセージ", MB_YESNO | MB_DEFBUTTON2);

			if (nID == IDYES)
			{
				DestroyWindow(hWnd);
			}
			else
			{
				return 0;
			}
			break;
		}
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}