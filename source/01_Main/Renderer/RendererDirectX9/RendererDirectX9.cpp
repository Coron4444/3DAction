//================================================================================
//
//    レンダラーDirectX9クラス
//    Author : Araki Kai                                作成日 : 2018/05/08
//
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
// 非静的メンバ関数定義
//****************************************
//--------------------------------------------------
// +初期化関数
//--------------------------------------------------
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
	direct3d_present_parameters.AutoDepthStencilFormat = D3DFMT_D16;					//	今はこれで良い上のフォーマット
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

	/*

	

	*/

	return true;
}



//--------------------------------------------------
// +終了処理関数
//--------------------------------------------------
void RendererDirectX9::Uninit()
{
	// デバイスの解放
	SafeRelease::PlusRelease(&direct3d_device_);

	// Direct3Dインターフェースの解放
	SafeRelease::PlusRelease(&direct3d_interface_);
}



//--------------------------------------------------
// +描画開始関数
//--------------------------------------------------
bool RendererDirectX9::DrawBegin()
{
	// 画面クリア
	direct3d_device_->Clear(0,										// RECT構造体配列の矩形の数
							NULL,									// RECT構造体の先頭アドレス(画面全体はNULL)
							(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),	// TARGETは色のクリア、ZBUFFERはZバッファのクリア
							D3DCOLOR_RGBA(32, 64, 192, 255),		// クリアカラ―(TARGETがあるとき)
							1.0f,									// Zバッファのクリア値
							0);										// ステンシル値のクリア値

	// 描画の開始
	if (SUCCEEDED(direct3d_device_->BeginScene())) return true;

	return false;
}



//--------------------------------------------------
// +描画終了関数
//--------------------------------------------------
void RendererDirectX9::DrawEnd(bool is_begin_scene)
{
	// 描画の終了
	if (is_begin_scene) direct3d_device_->EndScene();

	// バックバッファをフロントバッファに描画
	direct3d_device_->Present(NULL, NULL, NULL, NULL);
}



//--------------------------------------------------
// +インタフェース取得関数
//--------------------------------------------------
LPDIRECT3D9 RendererDirectX9::GetInterface()
{
	return direct3d_interface_;
}



//--------------------------------------------------
// +ダイレクト3Dデバイス取得関数
//--------------------------------------------------
LPDIRECT3DDEVICE9 RendererDirectX9::GetDevice()
{
	return direct3d_device_;
}
