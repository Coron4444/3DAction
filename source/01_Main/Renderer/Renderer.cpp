//================================================================================
//!	@file	 Renderer.cpp
//!	@brief	 レンダラーClass
//! @details Singleton
//!	@author  Kai Araki									@date 2018/11/01
//================================================================================



//****************************************
// インクルード文
//****************************************
#include "Renderer.h"

#include <SafeRelease/SafeRelease.h>



//****************************************
// static変数定義
//****************************************
Renderer* Renderer::instance_ = nullptr;
RendererInterface* Renderer::renderer_ = nullptr;



//****************************************
// static関数定義
//****************************************
//--------------------------------------------------
// +インスタンス解放関数
//--------------------------------------------------
void Renderer::ReleaseInstance()
{
	SafeRelease::Normal(&instance_);
}



//--------------------------------------------------
// +インスタンス取得関数
//--------------------------------------------------
Renderer* Renderer::getpInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new Renderer();
	}
	return instance_;
}



//****************************************
// 関数定義
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
// +バックバッファをフロントバッファに反映関数
//--------------------------------------------------
void Renderer::Present()
{
	if (renderer_ == nullptr) return;
	renderer_->Present();
}