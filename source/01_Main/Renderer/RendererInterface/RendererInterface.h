//================================================================================
//
//    レンダラーインターフェースクラス
//    Author : Araki Kai                                作成日 : 2018/05/08
//
//================================================================================

#ifndef	_RENDERER_INTERFACE_H_
#define _RENDERER_INTERFACE_H_



//****************************************
// インクルード文
//****************************************
#include <Windows.h>



/*********************************************************//**
* @brief
* レンダラーインターフェースクラス
*
* レンダラーのインターフェース
*************************************************************/
class RendererInterface
{
//==============================
// 非静的メンバ関数
//==============================
public:
	/**
	* @brief
	* 純粋仮想デストラクタ
	*/
	virtual ~RendererInterface() = 0;
	
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
	virtual bool Init(HINSTANCE hInstance, HWND hWnd, BOOL is_full_screen,
					  int window_width, int window_height) = 0;

	/**
	* @brief
	* 終了関数
	*/
	virtual void Uninit() = 0;

	/**
	* @brief
	* 描画開始関数
	*/
	virtual bool DrawBegin() = 0;

	/**
	* @brief
	* 描画終了関数
	* @param
	* is_begin_scene : 描画開始が成功しているかフラグ
	*/
	virtual void DrawEnd(bool is_begin_scene) = 0;	

	/**
	* @brief
	* バックバッファをフロントバッファに反映関数
	*/
	virtual void Present() = 0;;
};



//****************************************
// 非静的メンバ関数定義(inline)
//****************************************
//--------------------------------------------------
// +純粋仮想デストラクタ
//--------------------------------------------------
inline RendererInterface::~RendererInterface()
{
}



#endif



