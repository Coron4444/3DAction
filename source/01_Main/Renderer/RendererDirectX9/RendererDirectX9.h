//================================================================================
//!	@file	 RendererDirectX9.h
//!	@brief	 レンダラーDirectX9Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/01
//================================================================================
#ifndef	_RENDERE_DIRECTX9_H_
#define _RENDERE_DIRECTX9_H_



//****************************************
// インクルード文
//****************************************
#include <d3d9.h>
#include <d3dx9.h>

#include "../RendererInterface/RendererInterface.h"
#include <Vector3D.h>



//************************************************************														   
//! @brief レンダラーDirectX9Class
//!
//! @details DirectX9用レンダラーClass
//************************************************************
class RendererDirectX9 : public RendererInterface
{
//====================
// クラス定義
//====================
public:
	//****************************************														   
	//! @brief 頂点Class
	//!
	//! @details 頂点用のClass
	//****************************************
	class VERTEX_3D
	{
	//====================
	// 変数
	//====================
	public:
		Vec3   posisiont_;	//!< 座標
		Vec3   normal_;		//!< 法線
		Color4 color_;		//!< カラー
		Vec2   texcoord_;	//!< テクスチャ座標
	};


//====================
// 定数
//====================
public:
	static const DWORD FVF_VERTEX_3D;	//!< FVF


//====================
// 変数
//====================
private:
	LPDIRECT3D9        direct3d_interface_ = nullptr;	//!< インターフェース
	LPDIRECT3DDEVICE9  direct3d_device_ = nullptr;		//!< デバイス


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief インターフェースポインタ取得関数
	//! @details
	//! @param void なし
	//! @retval LPDIRECT3D9 インタフェース
	//----------------------------------------
	LPDIRECT3D9 getpInterface();

	//----------------------------------------
	//! @brief デバイスポインタ取得関数
	//! @details
	//! @param void なし
	//! @retval LPDIRECT3DDEVICE9 デバイス
	//----------------------------------------
	LPDIRECT3DDEVICE9 getpDevice();


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @details インターフェース及びデバイスの生成
	//! @param hInstance	  インスタンスハンドル
	//! @param hWnd			  Windowsハンドル
	//! @param is_full_screen フルスクリーンフラグ
	//! @param window_width	  ウィンドウ幅
	//! @param window_height  ウィンドウ高さ
	//! @retval bool 初期化成功の有無
	//----------------------------------------
	bool Init(HINSTANCE hInstance, HWND hWnd, BOOL is_full_screen,
			  int window_width, int window_height) override;

	//----------------------------------------
	//! @brief 終了関数
	//! @details 各種開放
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Uninit() override;

	//----------------------------------------
	//! @brief 描画開始関数
	//! @details
	//! @param void なし
	//! @retval bool 描画開始成功の有無
	//----------------------------------------
	bool DrawBegin() override;

	//----------------------------------------
	//! @brief 描画終了関数
	//! @details
	//! @param is_begin_scene 描画開始成功フラグ
	//! @retval void なし
	//----------------------------------------
	void DrawEnd(bool is_begin_scene) override;

	//----------------------------------------
	//! @brief バックバッファをフロントバッファに反映関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Present() override;

	//----------------------------------------
	//! @brief バックバッファをフロントバッファに反映関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void UseAlphaBlending(bool flag);

	//----------------------------------------
	//! @brief アルファ合成関数(線形合成)
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void SetAlphaBlending_Linear();

	//----------------------------------------
	//! @brief アルファ合成関数(加算合成)
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void SetAlphaBlending_Add();

	//----------------------------------------
	//! @brief アルファ合成関数(減算合成)
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void SetAlphaBlending_Sub();

	//----------------------------------------
	//! @brief アルファ合成関数(乗算合成)
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void SetAlphaBlending_Mul();

	//----------------------------------------
	//! @brief アルファ合成関数(焼きこみ合成)
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void SetAlphaBlending_Baking();

	//----------------------------------------
	//! @brief アルファ合成関数(ネガポジ反転合成)
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void SetAlphaBlending_Nega();

	//----------------------------------------
	//! @brief アルファ合成関数(不透明合成)
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void SetAlphaBlending_Opacity();

	//----------------------------------------
	//! @brief デフォルトサンプラーステート設定関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void SetDefaultSamplerState();
};



#endif