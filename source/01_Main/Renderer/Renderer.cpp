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

#include <Renderer/RendererFactory/RendererFactoryInterface/RendererFactoryInterface.h>
#include <SafeRelease/SafeRelease.h>



//****************************************
// static変数定義
//****************************************
Renderer* Renderer::instance_ = nullptr;
RendererInterface* Renderer::renderer_ = nullptr;



//****************************************
// staticプロパティ定義
//****************************************
Renderer* Renderer::getpInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new Renderer();
	}
	return instance_;
}



//****************************************
// static関数定義
//****************************************
void Renderer::ReleaseInstance()
{
	SafeRelease::Normal(&instance_);
}



//****************************************
// プロパティ定義
//****************************************
RendererInterface* Renderer::getpRenderer()
{
	return renderer_;
}

void Renderer::setRenderer(RendererFactoryInterface* factory, MODE mode)
{
	if (renderer_ == nullptr)
	{
		renderer_ = factory->Create();
		mode_ = mode;
	}

	SafeRelease::Normal(&factory);
}



//****************************************
// 関数定義
//****************************************
Renderer::Renderer()
{
}



bool Renderer::Init(HINSTANCE hInstance, HWND hWnd, BOOL is_full_screen,
					int window_width, int window_height)
{
	if (renderer_ == nullptr) return false;
	return renderer_->Init(hInstance, hWnd, is_full_screen, window_width, window_height);
}



void Renderer::Uninit()
{
	// レンダラーの解放
	SafeRelease::PlusUninit(&renderer_);

	// モードの初期化
	mode_ = MODE::NONE;
}



bool Renderer::DrawBegin()
{
	if (renderer_ == nullptr) return false;
	return renderer_->DrawBegin();
}



void Renderer::DrawEnd(bool is_begin_scene)
{
	if (renderer_ == nullptr) return;
	renderer_->DrawEnd(is_begin_scene);
}



void Renderer::Present()
{
	if (renderer_ == nullptr) return;
	renderer_->Present();
}