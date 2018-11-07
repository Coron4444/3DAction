//================================================================================
//
//    レンダラークラス
//    Author : Araki Kai                                作成日 : 2018/1/01
//
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "Renderer.h"
#include <SafeRelease/SafeRelease.h>



//****************************************
// 静的メンバ変数定義
//****************************************

Renderer* Renderer::instance_ = nullptr;
RendererInterface* Renderer::renderer_ = nullptr;



//****************************************
// 静的メンバ関数定義
//****************************************
//--------------------------------------------------
// +インスタンス取得関数
//--------------------------------------------------
Renderer* Renderer::GetInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new Renderer();
	}
	return instance_;
}



//--------------------------------------------------
// +インスタンス解放関数
//--------------------------------------------------
void Renderer::ReleaseInstance()
{
	SafeRelease::Normal(&instance_);
}



//****************************************
// 非静的メンバ関数定義
//****************************************
//--------------------------------------------------
// +初期化関数
//--------------------------------------------------
bool Renderer::Init(HINSTANCE hInstance, HWND hWnd, BOOL is_full_screen,
					int window_width, int window_height)
{
	if (renderer_ == nullptr) return false;
	return renderer_->Init(hInstance, hWnd, is_full_screen, window_width, window_height);
}



//--------------------------------------------------
// +終了処理関数
//--------------------------------------------------
void Renderer::Uninit()
{
	// レンダラーの解放
	SafeRelease::PlusUninit(&renderer_);

	// モードの初期化
	mode_ = MODE::NONE;
}



//--------------------------------------------------
// +描画開始関数
//--------------------------------------------------
bool Renderer::DrawBegin()
{
	if (renderer_ == nullptr) return false;
	return renderer_->DrawBegin();
}



//--------------------------------------------------
// +描画終了関数
//--------------------------------------------------

void Renderer::DrawEnd(bool is_begin_scene)
{
	if (renderer_ == nullptr) return;
	renderer_->DrawEnd(is_begin_scene);
}



//--------------------------------------------------
// +レンダラー設定関数
//--------------------------------------------------

void Renderer::SetRenderer(RendererFactory* factory, MODE mode)
{
	if (renderer_ == nullptr)
	{
		renderer_ = factory->Create();
		mode_ = mode;
	}

	SafeRelease::Normal(&factory);
}