//================================================================================
//
//    レンダラークラス
//    Author : Araki Kai                                作成日 : 2018/11/01
//
//================================================================================

#ifndef	_RENDERE_H_
#define _RENDERE_H_



//****************************************
// インクルード文
//****************************************
#include "RendererInterface/RendererInterface.h"
#include "RendererFactory/RendererFactory.h"
#include "RendererDirectX9/RendererDirectX9.h"
#include <Vector3D.h>



/*********************************************************//**
* @brief
* レンダラークラス
*
* レンダラークラス
*************************************************************/
class Renderer
{
//==============================
// 列挙型定義
//==============================
public:
	enum MODE
	{
		NONE = -1,
		DIRECTX9,
		DIRECTX11,
		OPEN_GL,
		MAX
	};


//==============================
// 静的メンバ変数
//==============================
private:
	static Renderer* instance_;				//!< インスタンス
	static RendererInterface* renderer_;	//!< レンダラー



//==============================
// メンバ変数
//==============================
private:
	MODE mode_ = MODE::NONE;		//!< モード



//==============================
// 静的メンバ関数
//==============================
public:
	static Renderer* GetInstance();
	static void ReleaseInstance();



//==============================
// 非静的メンバ関数
//==============================
private:
	/**
	* @brief
	* コンストラクタ
	*/
	Renderer() {}
	Renderer(const Renderer& class_name) = delete;
	Renderer& operator = (const Renderer& class_name) = delete;


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
	* 描画開始関数
	*/
	bool DrawBegin();

	/**
	* @brief
	* 描画終了関数
	* @param
	* is_begin_scene : 描画開始が成功しているかフラグ
	*/
	void DrawEnd(bool is_begin_scene);

	/**
	* @brief
	* バックバッファをフロントバッファに反映関数
	*/
	void Present();

	/**
	* @brief
	* レンダラー設定関数
	* @param
	* factory : レンダラーファクトリー
	* mode : モード
	*/
	void SetRenderer(RendererFactory* factory, MODE mode);

	/**
	* @brief
	* レンダラー取得関数
	*/
	RendererInterface* GetRenderer() { return renderer_; }

	/**
	* @brief
	* インターフェース取得関数
	*/
	template <class Type>
	void GetInterface(Type** pointer)
	{
		if (renderer_ == nullptr) return;
		switch (mode_)
		{
			case Renderer::DIRECTX9:
			{
				*pointer = ((RendererDirectX9*)renderer_)->GetInterface();
				break;
			}
			case Renderer::DIRECTX11:
			{
				break;
			}
			case Renderer::OPEN_GL:
			{
				break;
			}
			default:
			{
				break;
			}
		}
	}

	/**
	* @brief
	* デバイス取得関数
	*/
	template <class Type>
	void GetDevice(Type** pointer)
	{
		if (renderer_ == nullptr) return;
		switch (mode_)
		{
			case Renderer::DIRECTX9:
			{
				*pointer = ((RendererDirectX9*)renderer_)->GetDevice();
				break;
			}
			case Renderer::DIRECTX11:
			{
				break;
			}
			case Renderer::OPEN_GL:
			{
				break;
			}
			default:
			{
				break;
			}
		}
	}
};



#endif