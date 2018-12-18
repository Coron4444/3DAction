//================================================================================
//!	@file	 RendererDirectX9.cpp
//!	@brief	 レンダラーDirectX9Class
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "RendererDirectX9.h"

#include <SafeRelease/SafeRelease.h>



//****************************************
// 定数定義
//****************************************
const DWORD	RendererDirectX9::FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);



//****************************************
// プロパティ定義
//****************************************
LPDIRECT3D9 RendererDirectX9::getpInterface()
{
	return direct3d_interface_;
}



LPDIRECT3DDEVICE9 RendererDirectX9::getpDevice()
{
	return direct3d_device_;
}



//****************************************
// 関数定義
//****************************************
bool RendererDirectX9::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow,
							int nWindowWidth, int nWindowHeight)
{
	// 使っていない引数の処理
	hInstance = hInstance;

	// ダイレクト3Dインタフェースの取得
	direct3d_interface_ = Direct3DCreate9(D3D_SDK_VERSION);

	if (direct3d_interface_ == nullptr) return false;

	// 現在のディスプレイモードを取得
	D3DDISPLAYMODE direct3d_display_mode;
	HRESULT h_result = direct3d_interface_->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,		// ディスプレイ・アダプタを指定する(今回の指定は初期のディスプレイ・アダプタ)
																  &direct3d_display_mode);	// 現在のディスプレイ・アダプタの情報を受け取る変数の先頭アドレス

	if (FAILED(h_result)) return false;

	// デバイスのプレゼンテーションパラメータ(デバイスを作成するためのデータ)
	D3DPRESENT_PARAMETERS direct3d_present_parameters;
	ZeroMemory(&direct3d_present_parameters, sizeof(direct3d_present_parameters));
	direct3d_present_parameters.BackBufferWidth = nWindowWidth;							//　裏画面(バックバッファ)の幅
	direct3d_present_parameters.BackBufferHeight = nWindowHeight;						//	裏画面(バックバッファ)の高さ
	direct3d_present_parameters.BackBufferFormat = direct3d_display_mode.Format;		//	色数( バックバッファのフォーマット )
	direct3d_present_parameters.BackBufferCount = 1;									//	バックバッファの数
	direct3d_present_parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;						//	映像信号の同期(DISCARDは垂直同期を気にする)
	direct3d_present_parameters.EnableAutoDepthStencil = TRUE;							//	TRUEで良い
	direct3d_present_parameters.AutoDepthStencilFormat = D3DFMT_D24S8;					//	今はこれで良い上のフォーマット
	direct3d_present_parameters.Windowed = bWindow;										//	TRUEでウィンドウモード,FALSEでフルスクリーンモード
	direct3d_present_parameters.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	//	フルスクリーンモードの時のリフレッシュレートのHz数を変更
	direct3d_present_parameters.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		//	モニターのHz数に合わせて描画される(IMMEDIATEだと垂直同期を待たずに描画する)( D3DPRESENT_INTERVAL_ONE　にするとヘルツで動く )

	// デバイスオブジェクトの生成( ｢描画｣と｢頂点処理｣をハードウェアで行う
	h_result = direct3d_interface_->CreateDevice(D3DADAPTER_DEFAULT,					// ディスプレイ・アダプタを指定する( 今回の指定は初期のディスプレイ・アダプタ )
												 D3DDEVTYPE_HAL,						// デバイスタイプ( 今回の指定はハードウェアによる処理を行う )
												 hWnd,									// このデバイスでフォーカスを設定するウィンドウハンドル
												 D3DCREATE_HARDWARE_VERTEXPROCESSING,	// デバイスの作成を制御するフラグの組み合わせ( 今回の指定はハードウェアによる頂点処理を指定 )
												 &direct3d_present_parameters,			// デバイスの設定を指定した変数の先頭アドレス
												 &direct3d_device_);					// 作成したデバイスを受け取る変数の先頭アドレス

	if (FAILED(h_result))
	{
		MessageBox(hWnd, "ダイレクト3Dデバイスの\n作成に失敗しました!!", "Error", MB_OK);
		return false;
	}

	return true;
}



void RendererDirectX9::Uninit()
{
	// デバイスの解放
	SafeRelease::PlusRelease(&direct3d_device_);

	// Direct3Dインターフェースの解放
	SafeRelease::PlusRelease(&direct3d_interface_);
}



bool RendererDirectX9::DrawBegin()
{
	// 画面クリア
	direct3d_device_->Clear(0,										// RECT構造体配列の矩形の数
							NULL,									// RECT構造体の先頭アドレス(画面全体はNULL)
							(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL),	// TARGETは色のクリア、ZBUFFERはZバッファのクリア
							D3DCOLOR_RGBA(32, 64, 192, 255),		// クリアカラ―(TARGETがあるとき)
							1.0f,									// Zバッファのクリア値
							0);										// ステンシル値のクリア値

	// 描画の開始
	if (SUCCEEDED(direct3d_device_->BeginScene())) return true;

	return false;
}



void RendererDirectX9::DrawEnd(bool is_begin_scene)
{
	// 描画の終了
	if (is_begin_scene) direct3d_device_->EndScene();
}



void RendererDirectX9::Present()
{
	// バックバッファをフロントバッファに描画
	direct3d_device_->Present(NULL, NULL, NULL, NULL);
}



void RendererDirectX9::UseAlphaBlending(bool flag)
{
	direct3d_device_->SetRenderState(D3DRS_ALPHABLENDENABLE, flag);
}



void RendererDirectX9::SetAlphaBlending_Linear()
{
	// SRC --- 今から描くもの。
	// DEST--- すでに描画されている画面のこと。
	// 1は100%(255)のこと
	// 今回はSRC_αが0だから背景色が100%で出ている。

	// {(1 - SRC_α) * DEST_RGB} + (SRC_RGB * SRC_α) 
	direct3d_device_->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	direct3d_device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	direct3d_device_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
}



void RendererDirectX9::SetAlphaBlending_Add()
{
	// (DST_RGB * 1) - (SRC_RGB * SRC_α) 
	direct3d_device_->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	direct3d_device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	direct3d_device_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
}



void RendererDirectX9::SetAlphaBlending_Sub()
{
	// (DST_RGB * 1) - (SRC_RGB * SRC_α) 
	direct3d_device_->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	direct3d_device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	direct3d_device_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
}



void RendererDirectX9::SetAlphaBlending_Mul()
{
	//direct3d_device_-> SetRenderState( D3DRS_BLENDOP, 任意の値)
	// 下記2行で成立するため上記の設定に依存しない

	// (DST_RGB * SRC_RGB) + (SRC_RGB * 0)
	direct3d_device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);
	direct3d_device_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
}



void RendererDirectX9::SetAlphaBlending_Baking()
{
	//direct3d_device_-> SetRenderState(D3DRS_BLENDOP, 任意の値)
	// 下記2行で成立するため上記の設定に依存しない

	// (DST_RGB * DST_RGB) + ( SRC_RGB * 0 )
	direct3d_device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_DESTCOLOR);
	direct3d_device_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
}



void RendererDirectX9::SetAlphaBlending_Nega()
{
	//direct3d_device_->SetRenderState(D3DRS_BLENDOP, 任意の値)
	// 下記2行で成立するため上記の設定に依存しない

	// (DST_RGB * 0) + (1 - DST_RGB) * SRC_RGB
	direct3d_device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	direct3d_device_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVDESTCOLOR);
}



void RendererDirectX9::SetAlphaBlending_Opacity()
{
	//direct3d_device_->SetRenderState(D3DRS_BLENDOP, 任意の値)
	// 下記2行で成立するため上記の設定に依存しない

	// (DST_RGB * 0) + (SRC_RGB * 1)
	direct3d_device_->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	direct3d_device_->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
}



void RendererDirectX9::SetDefaultSamplerState()
{
	// 第二引数(UVの設定)
	// 第三引数テクスチャー座標外の処理
	// WRAP ( 複製 )
	// CLAMP( 一番最後のピクセルを引き延ばして参照する )
	// MIRROR( 鏡 )
	direct3d_device_->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	direct3d_device_->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	// フィルタリング
	// MIPマップ(あらかじめ小さい画像データを自動で用意しておく)
	direct3d_device_->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// デフォルトはPOINT(代表点1個を拾ってくる)
																				// LINEAR(周りの点を集約して、つまり色をブレンドして1点にする)よって色がぼけるが滑らか
	direct3d_device_->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// デフォルトはPOINT
	direct3d_device_->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);	// デフォルトはNONE(MIPマップを使わない)
																				// LINEAR（MIPマップ間を線形補完する）
}