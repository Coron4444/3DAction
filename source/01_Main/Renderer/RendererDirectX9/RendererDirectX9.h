//================================================================================
//
//    レンダラーDirectX9クラス
//    Author : Araki Kai                                作成日 : 2018/05/08
//
//================================================================================

#ifndef	_RENDERE_DIRECTX9_H_
#define _RENDERE_DIRECTX9_H_



//****************************************
// インクルード文
//****************************************
#include <d3d9.h>
#include <d3dx9.h>
#include <assert.h>

#include "../RendererInterface/RendererInterface.h"
#include <Vector3D.h>



/*********************************************************//**
* @brief
* レンダラーDirectX9クラス
*
* DirectX9用レンダラークラス
*************************************************************/
class RendererDirectX9 : public RendererInterface
{
//==============================
// 非静的メンバ変数
//==============================
private:
	LPDIRECT3D9        direct3d_interface_ = nullptr;	//!< インターフェース
	LPDIRECT3DDEVICE9  direct3d_device_ = nullptr;		//!< デバイス


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:
	// 定数
	static const DWORD FVF_VERTEX_3D;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:
	// 頂点構造体
	struct VERTEX_3D
	{
		Vec3   posisiont_;	// 座標
		Vec3   normal_;		// 法線
		Color4 color_;		// カラー
		Vec2   texcoord_;	// テクスチャ座標
	};


//==============================
// 非静的メンバ関数
//==============================
public:
	// レンダラー関係
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
	* インターフェース取得関数
	*/
	LPDIRECT3D9 GetInterface();

	/**
	* @brief
	* デバイス取得関数
	*/
	LPDIRECT3DDEVICE9 GetDevice();

	/**
	* @brief
	* アルファ合成フラグ関数
	*/
	void UseAlphaBlending(bool flag);

	/**
	* @brief
	* アルファ合成関数(線形合成)
	*/
	void SetAlphaBlending_Linear();
	
	/**
	* @brief
	* アルファ合成関数(加算合成)
	*/
	void SetAlphaBlending_Add();

	/**
	* @brief
	* アルファ合成関数(減算合成)
	*/
	void SetAlphaBlending_Sub();
	
	/**
	* @brief
	* アルファ合成関数(乗算合成)
	*/
	void SetAlphaBlending_Mul();
	
	/**
	* @brief
	* アルファ合成関数(焼きこみ合成)
	*/
	void SetAlphaBlending_Baking();
	
	/**
	* @brief
	* アルファ合成関数(ネガポジ反転合成)
	*/
	void SetAlphaBlending_Nega();
	
	/**
	* @brief
	* アルファ合成関数(不透明合成)
	*/
	void SetAlphaBlending_Opacity();

	/**
	* @brief
	* デフォルトサンプラーステート設定関数
	*/
	void SetDefaultSamplerState();
};



#endif