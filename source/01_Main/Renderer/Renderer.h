//================================================================================
//!	@file	 Renderer.h
//!	@brief	 レンダラーClass
//! @details Singleton
//!	@author  Kai Araki									@date 2018/11/01
//================================================================================
#ifndef	_RENDERE_H_
#define _RENDERE_H_



//****************************************
// インクルード文
//****************************************
#include <renderer/RendererFactory/RendererFactoryDirectX9/RendererFactoryDirectX9.h>
#include <SafeRelease/SafeRelease.h>
#include <Vector3D.h>



//************************************************************														   
//! @brief   レンダラーClass
//!
//! @details レンダラーのClass(Singleton)
//************************************************************
class Renderer
{
//====================
// 列挙型定義
//====================
public:
	enum MODE
	{
		NONE = -1,
		DIRECTX9,
		DIRECTX11,
		OPEN_GL,
		MAX
	};


//====================
// static変数
//====================
private:
	static Renderer* instance_;				//!< インスタンス
	static RendererInterface* renderer_;	//!< レンダラー


//====================
// 変数
//====================
private:
	MODE mode_ = MODE::NONE;		//!< モード


//====================
// static関数
//====================
public:
	//----------------------------------------
	//! @brief インスタンス解放関数
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	static void ReleaseInstance();

	// プロパティ
	static Renderer* getpInstance();


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @param[in] hInstance	  インスタンスハンドル
	//! @param[in] hWnd			  Windowsハンドル
	//! @param[in] is_full_screen フルスクリーンフラグ
	//! @param[in] window_width	  ウィンドウ幅
	//! @param[in] window_height  ウィンドウ高さ
	//! @retval bool 初期化成功の有無
	//----------------------------------------
	bool Init(HINSTANCE hInstance, HWND hWnd, BOOL is_full_screen,
			  int window_width, int window_height);

	//----------------------------------------
	//! @brief 終了関数
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Uninit();

	//----------------------------------------
	//! @brief 描画開始関数
	//! @param void なし
	//! @retval bool 描画開始成功の有無
	//----------------------------------------
	bool DrawBegin();

	//----------------------------------------
	//! @brief 描画終了関数
	//! @param[in] is_begin_scene 描画開始成功フラグ
	//! @retval void なし
	//----------------------------------------
	void DrawEnd(bool is_begin_scene);

	//----------------------------------------
	//! @brief バックバッファをフロントバッファに反映関数
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Present();

	// プロパティ
	RendererInterface* getpRenderer() { return renderer_; }
	void setRenderer(RendererFactoryInterface* factory, MODE mode)
	{
		if (renderer_ == nullptr)
		{
			renderer_ = factory->Create();
			mode_ = mode;
		}

		SafeRelease::Normal(&factory);
	}
	template <class Type>
	void getInterface(Type** pointer)
	{
		if (renderer_ == nullptr) return;
		switch (mode_)
		{
			case Renderer::DIRECTX9:
			{
				*pointer = ((RendererDirectX9*)renderer_)->getpInterface();
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
	template <class Type>
	void getDevice(Type** pointer)
	{
		if (renderer_ == nullptr) return;
		switch (mode_)
		{
			case Renderer::DIRECTX9:
			{
				*pointer = ((RendererDirectX9*)renderer_)->getpDevice();
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

private:
	//----------------------------------------
	//! @brief コンストラクタ
	//! @param void なし
	//----------------------------------------
	Renderer() {}

//====================
// 消去済み関数
//====================
private:
	Renderer(const Renderer& class_name) = delete;
	Renderer& operator = (const Renderer& class_name) = delete;
};



#endif