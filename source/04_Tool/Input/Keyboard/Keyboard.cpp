//================================================================================
//
//    キーボード入力
//    Author : Araki Kai                                作成日 : 2017/07/25
//
//================================================================================



//**********************************************************************
//
// インクルード文
//
//**********************************************************************

#include "Keyboard.h"



//**********************************************************************
//
// マクロ定義
//
//**********************************************************************

#define	NUM_KEY_MAX			(256)	// キーの最大数
#define	LIMIT_COUNT_REPEAT	(20)	// リピートカウントリミッター



//**********************************************************************
//
// プロトタイプ宣言
//
//**********************************************************************

//================================================================================
//
// [ 入力処理の初期化関数 ]
//
// ｢ 引数 ｣
//
// ･hInstance : インスタンスハンドル
// ･hWnd : ウィンドウハンドル
//
// ｢ 戻り値 ｣
//
// ･HRESULT型 : エラーチェック用
//
//【 詳細 】
//
// ･入力処理を使用するときの初期化
//
//================================================================================

HRESULT InitInput(HINSTANCE hInstance, HWND hWnd);



//================================================================================
//
// [ 入力処理の終了処理関数 ]
//
// ｢ 引数 ｣
//
// ･なし
//
// ｢ 戻り値 ｣
//
// ･なし
//
//【 詳細 】
//
// ･入力処理の使用を終了するときの処理
//
//================================================================================

void UninitInput(void);



//================================================================================
//
// [ 入力処理の更新関数 ]
//
// ｢ 引数 ｣
//
// ･なし
//
// ｢ 戻り値 ｣
//
// ･なし
//
//【 詳細 】
//
// ･入力処理の更新
//
//================================================================================

void UpdateInput(void);



//**********************************************************************
//
// グローバル変数
//
//**********************************************************************

// DirectInputオブジェクトへのポインタ
LPDIRECTINPUT8 g_pInput = NULL;


// 入力デバイス(キーボード)へのポインタ
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;


// キーボードの入力情報ワーク
BYTE g_aKeyState[NUM_KEY_MAX];


// キーボードのトリガー情報ワーク
BYTE g_aKeyStateTrigger[NUM_KEY_MAX];


// キーボードのリリース情報ワーク
BYTE g_aKeyStateRelease[NUM_KEY_MAX];


// キーボードのリピート情報ワーク
BYTE g_aKeyStateRepeat[NUM_KEY_MAX];


// キーボードのリピートカウンタ
int g_aKeyStateRepeatCnt[NUM_KEY_MAX];






//================================================================================
//
// [ 入力処理の初期化関数 ]
//
// ｢ 引数 ｣
//
// ･hInstance : インスタンスハンドル
// ･hWnd : ウィンドウハンドル
//
// ｢ 戻り値 ｣
//
// ･HRESULT型 : エラーチェック用
//
//【 詳細 】
//
// ･入力処理を使用するときの初期化
//
//================================================================================

HRESULT InitInput(HINSTANCE hInstance, HWND hWnd)
{
	// 使われていない引数対策
	hWnd = hWnd;


	// UNREFERENCED_PARAMETER( hWnd ); これでも警告は消せる
	if(g_pInput == NULL)
	{
		// DirectInputオブジェクトの作成
		if(FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
										IID_IDirectInput8, (void**)&g_pInput, NULL)))
		{
			return E_FAIL;
		}
	}


	return S_OK;
}



//================================================================================
//
// [ 入力処理の終了処理関数 ]
//
// ｢ 引数 ｣
//
// ･なし
//
// ｢ 戻り値 ｣
//
// ･なし
//
//【 詳細 】
//
// ･入力処理の使用を終了するときの処理
//
//================================================================================

void UninitInput(void)
{
	if(g_pInput != NULL)
	{// DirectInputオブジェクトの開放
		g_pInput->Release();
		g_pInput = NULL;
	}
}



//================================================================================
//
// [ 入力処理の更新関数 ]
//
// ｢ 引数 ｣
//
// ･なし
//
// ｢ 戻り値 ｣
//
// ･なし
//
//【 詳細 】
//
// ･入力処理の更新
//
//================================================================================

void UpdateInput(void)
{

}



//================================================================================
//
// [ キーボードの初期化関数 ]
//
// ｢ 引数 ｣
//
// ･hInstance : インスタンスハンドル
// ･hWnd : ウィンドウハンドル
//
// ｢ 戻り値 ｣
//
// ･HRESULT型 : エラーチェック用
//
//【 詳細 】
//
// ･キーボードを使用するときの初期化
//
//================================================================================

HRESULT InitKeyboard(HINSTANCE hInstance, HWND hWnd)
{

	// 入力処理の初期化
	if(FAILED(InitInput(hInstance, hWnd)))
	{
		MessageBox(hWnd, "DirectInputオブジェクトが作れねぇ！", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}


	// デバイスの作成
	if(FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		MessageBox(hWnd, "キーボードがねぇ！", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}


	// データフォーマットを設定
	if(FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		MessageBox(hWnd, "キーボードのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}


	// 協調モードを設定（フォアグラウンド＆非排他モード）重要!!
	if(FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		MessageBox(hWnd, "キーボードの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}


	// キーボードへのアクセス権を獲得(入力制御開始)
	g_pDevKeyboard->Acquire();


	return S_OK;
}



//================================================================================
//
// [ キーボードの終了処理関数 ]
//
// ｢ 引数 ｣
//
// ･なし
//
// ｢ 戻り値 ｣
//
// ･なし
//
//【 詳細 】
//
// ･キーボードの使用を終了するときの処理
//
//================================================================================

void UninitKeyboard(void)
{
	if(g_pDevKeyboard != NULL)
	{// 入力デバイス(キーボード)の開放
		// キーボードへのアクセス権を開放(入力制御終了)
		g_pDevKeyboard->Unacquire();

		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}


	// 入力処理の終了処理
	UninitInput();
}



//================================================================================
//
// [ キーボードの更新関数 ]
//
// ｢ 引数 ｣
//
// ･なし
//
// ｢ 戻り値 ｣
//
// ･なし
//
//【 詳細 】
//
// ･キーボードの更新
//
//================================================================================

void UpdateKeyboard(void)
{
	BYTE aKeyState[NUM_KEY_MAX];


	// デバイスからデータを取得
	if(SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for(int nCnKey = 0; nCnKey < NUM_KEY_MAX; nCnKey++)
		{
			// キートリガー・リリース情報を生成
			g_aKeyStateTrigger[nCnKey] = (g_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & aKeyState[nCnKey];
			g_aKeyStateRelease[nCnKey] = (g_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & g_aKeyState[nCnKey];


			// キーリピート情報を生成
			if(aKeyState[nCnKey])
			{
				if(g_aKeyStateRepeatCnt[nCnKey] < LIMIT_COUNT_REPEAT)
				{
					g_aKeyStateRepeatCnt[nCnKey]++;
					if(g_aKeyStateRepeatCnt[nCnKey] == 1
					|| g_aKeyStateRepeatCnt[nCnKey] >= LIMIT_COUNT_REPEAT)
					{// キーを押し始めた最初のフレーム、または一定時間経過したらキーリピート情報ON
						g_aKeyStateRepeat[nCnKey] = aKeyState[nCnKey];
					}
					else
					{
						g_aKeyStateRepeat[nCnKey] = 0;
					}
				}
			}
			else
			{
				g_aKeyStateRepeatCnt[nCnKey] = 0;
				g_aKeyStateRepeat[nCnKey] = 0;
			}


			// キープレス情報を保存
			g_aKeyState[nCnKey] = aKeyState[nCnKey];
		}
	}
	else
	{
		// キーボードへのアクセス権を取得
		g_pDevKeyboard->Acquire();
	}
}



//================================================================================
//
// [ キーボードのプレス状態を取得する関数 ]
//
// ｢ 引数 ｣
//
// ･nkey : プレス状態を確認したいキーボードのボタンID
//
// ｢ 戻り値 ｣
//
// ･bool : プレスされてるかフラグを返す
//
//【 詳細 】
//
// ･渡されたキーボードボタンが押されているかを判断する
// ･押されているときはtrue、押されていないときはfalseを返す
//
//================================================================================

bool GetKeyboardPress(int nKey)
{
	return (g_aKeyState[nKey] & 0x80) ? true: false;
}



//================================================================================
//
// [ キーボードのトリガー状態を取得する関数 ]
//
// ｢ 引数 ｣
//
// ･nkey : トリガー状態を確認したいキーボードのボタンID
//
// ｢ 戻り値 ｣
//
// ･bool : トリガーされてるかフラグを返す
//
//【 詳細 】
//
// ･渡されたキーボードボタンが押された瞬間かどうかを判断する
// ･押した瞬間はtrue、それ以外はfalseを返す
//
//================================================================================

bool GetKeyboardTrigger(int nKey)
{
	return (g_aKeyStateTrigger[nKey] & 0x80) ? true: false;
}



//================================================================================
//
// [ キーボードのリピート状態を取得する関数 ]
//
// ｢ 引数 ｣
//
// ･nkey : リピート状態を確認したいキーボードのボタンID
//
// ｢ 戻り値 ｣
//
// ･bool : リピートされてるかフラグを返す
//
//【 詳細 】
//
// ･渡されたキーボードボタンが押されてから一定時間そのままかを判断する
// ･押されてから一定時間そのままのときtrue、押した瞬間はfalseを返す
//
//================================================================================

bool GetKeyboardRepeat(int nKey)
{
	return (g_aKeyStateRepeat[nKey] & 0x80) ? true: false;
}



//================================================================================
//
// [ キーボードのリリ−ス状態を取得する関数 ]
//
// ｢ 引数 ｣
//
// ･nkey : リリ−ス状態を確認したいキーボードのボタンID
//
// ｢ 戻り値 ｣
//
// ･bool : リリ−スされてるかフラグを返す
//
//【 詳細 】
//
// ･渡されたキーボードボタンが離された瞬間かどうかを判断する
// ･離した瞬間はtrue、それ以外はfalseを返す
//
//================================================================================

bool GetKeyboardRelease(int nKey)
{
	return (g_aKeyStateRelease[nKey] & 0x80) ? true: false;
}
