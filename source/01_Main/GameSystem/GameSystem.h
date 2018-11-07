//================================================================================
//
//    ゲームシステムクラス
//    Author : Araki Kai                                作成日 : 2018/05/08
//
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



/*********************************************************//**
* @brief
* ゲームシステムクラス
*
* ゲームシステム全体を管理する
* Renderer、SceneManager、Input、Sound、Debuger等を管理する
*************************************************************/
class GameSystem
{
//==============================
// 非静的メンバ変数
//==============================
private:
	SceneManager* scene_manager_ = nullptr;	//!< メインシーンの管理者



//==============================
// 非静的メンバ関数
//==============================
public:
	/**
	* @brief
	* 初期化関数
	* @param
	* hInstance : インスタンスハンドル
	* hWnd : Windowsハンドル
	* is_full_screen : フルスクリーンフラグ
	* window_width : Window幅
	* window_height : Window高さ
	*/
	bool Init(HINSTANCE hInstance, HWND hWnd, BOOL is_full_screen,
					 int window_width, int window_height);

	/**
	* @brief
	* 終了関数
	*/
	void Uninit();

	/**
	* @brief
	* 更新関数
	*/
	void Update();

	/**
	* @brief
	* 描画関数
	*/
	void Draw();

	/**
	* @brief
	* 後更新関数
	*/
	void LateUpdate();
};



#endif