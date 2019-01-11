//================================================================================
//!	@file	 GameSystem.h
//!	@brief	 ゲームシステムClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================
#ifndef	_GAME_SYSTEM_H_
#define _GAME_SYSTEM_H_



//****************************************
// インクルード文
//****************************************
#include <Windows.h>



//****************************************
// クラス宣言
//****************************************
class SceneManager;



//************************************************************														   
//! @brief   ゲームシステムClass
//!
//! @details ゲームシステム全体を管理する
//! @details Renderer、SceneManager、
//! @details Input、Sound、Debuger等を管理する
//************************************************************
class GameSystem
{
//====================
// 変数
//====================
private:
	SceneManager* scene_manager_ = nullptr;		//!< シーン管理者


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param hInstance	  インスタンスハンドル
	//! @param hWnd			  Windowsハンドル
	//! @param is_full_screen フルスクリーンフラグ
	//! @param window_width	  ウィンドウ幅
	//! @param window_height  ウィンドウ高さ
	//! @retval bool 初期化成功の有無
	//----------------------------------------
	bool Init(HINSTANCE hInstance, HWND hWnd, BOOL is_full_screen,
					 int window_width, int window_height);

	//----------------------------------------
	//! @brief 終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Uninit();

	//----------------------------------------
	//! @brief 更新関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Update();

	//----------------------------------------
	//! @brief 描画関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Draw();

	//----------------------------------------
	//! @brief 後更新関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void LateUpdate();
};



#endif