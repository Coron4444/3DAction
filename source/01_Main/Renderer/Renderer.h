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
#include <Renderer/RendererDirectX9/RendererDirectX9.h>



//****************************************
// クラス宣言
//****************************************
class RendererInterface;
class RendererFactoryInterface;



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
// staticプロパティ
//====================
public:
	//----------------------------------------
	//! @brief インスタンス取得関数
	//! @details
	//! @param void なし
	//! @retval Renderer* レンダラーインスタンス
	//----------------------------------------
	static Renderer* getpInstance();


//====================
// static関数
//====================
public:
	//----------------------------------------
	//! @brief インスタンス解放関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	static void ReleaseInstance();

	
//====================
// 変数
//====================
private:
	MODE mode_ = MODE::NONE;	//!< モード


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief レンダラー取得関数
	//! @details
	//! @param void なし
	//! @retval RendererInterface* レンダラー
	//----------------------------------------
	RendererInterface* getpRenderer();

	//----------------------------------------
	//! @brief レンダラー設定関数
	//! @details
	//! @param *factory レンダラーファクトリー
	//! @param *mode    レンダラーモード
	//! @retval void なし
	//----------------------------------------
	void setRenderer(RendererFactoryInterface* factory, MODE mode);

	//----------------------------------------
	//! @brief インターフェース取得関数
	//! @details
	//! @param **out_pointer 取得用
	//! @retval void なし
	//----------------------------------------
	template <class Type>
	void getInterface(Type** out_pointer)
	{
		if (renderer_ == nullptr) return;
		switch (mode_)
		{
			case Renderer::DIRECTX9:
			{
				*out_pointer = ((RendererDirectX9*)renderer_)->getpInterface();
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

	//----------------------------------------
	//! @brief デバイス取得関数
	//! @details
	//! @param **out_pointer 取得用
	//! @retval void なし
	//----------------------------------------
	template <class Type>
	void getDevice(Type** out_pointer)
	{
		if (renderer_ == nullptr) return;
		switch (mode_)
		{
			case Renderer::DIRECTX9:
			{
				*out_pointer = ((RendererDirectX9*)renderer_)->getpDevice();
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


//====================
// 関数
//====================
private:
	//----------------------------------------
	//! @brief コンストラクタ
	//! @param void なし
	//----------------------------------------
	Renderer();

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
	//! @brief 描画開始関数
	//! @details
	//! @param void なし
	//! @retval bool 描画開始成功の有無
	//----------------------------------------
	bool DrawBegin();

	//----------------------------------------
	//! @brief 描画終了関数
	//! @details
	//! @param is_begin_scene 描画開始成功フラグ
	//! @retval void なし
	//----------------------------------------
	void DrawEnd(bool is_begin_scene);

	//----------------------------------------
	//! @brief バックバッファをフロントバッファに反映関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Present();


//====================
// 消去済み関数
//====================
private:
	Renderer(const Renderer& class_name) = delete;
	Renderer& operator = (const Renderer& class_name) = delete;
};



#endif