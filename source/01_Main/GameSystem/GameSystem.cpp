//================================================================================
//!	@file	 GameSystem.cpp
//!	@brief	 ゲームシステムClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================



//****************************************
// インクルード文
//****************************************
#include <assert.h>

#include "GameSystem.h"

#include <Renderer/Renderer.h>
#include <Renderer/RendererFactory/RendererFactoryDirectX9/RendererFactoryDirectX9.h>
#include <SafeRelease/SafeRelease.h>
#include <Controller/Controller.h>
#include <Keyboard/Keyboard.h>
#include <Sound/Sound.h>
#include <SceneManager/SceneManager.h>
#include <Scenes/TitleScene/TitleScene.h>
#include <Scenes/TitleScene/TitleSceneState/TitleSceneState_Start/TitleSceneState_Start.h>
#include <Scenes/GameScene/GameScene.h>
#include <Scenes/GameScene/GameSceneState/GameSceneState_Start/GameSceneState_Start.h>


//#ifdef _DEBUG
#include <ImGUI/imgui.h>
#include <ImGUI/imgui_impl_dx9.h>
//#endif



//****************************************
// 関数定義
//****************************************
bool GameSystem::Init(HINSTANCE hInstance, HWND hWnd, BOOL is_full_screen,
					  int window_width, int window_height)
{
	// レンダラーの初期化
	Renderer::getpInstance()->setRenderer(new RendererFactoryDirectX9(),
										  Renderer::MODE::DIRECTX9);
	bool is_init = Renderer::getpInstance()->Init(hInstance, hWnd, is_full_screen,
												  window_width, window_height);

#ifdef _DEBUG
	assert(is_init && "DirectX9用レンダラーの初期化に失敗!!");
#else
	is_init = is_init;
#endif

	// サウンドの初期化
	InitSound(hWnd);

	// キーボード入力の初期化
	InitKeyboard(hInstance, hWnd);

	// ImGUIの初期化
//#ifdef _DEBUG
	LPDIRECT3DDEVICE9 device = nullptr;
	Renderer::getpInstance()->getDevice(&device);
	if (device == nullptr)
	{
		MessageBox(nullptr, "NotGetDevice!(GameSystem.cpp)", "Error", MB_OK);
		return false;
	}
	ImGui_ImplDX9_Init(hWnd, device);
//#endif

	// シーンマネージャーの生成
	scene_manager_ = new SceneManager();
	scene_manager_->Init(new TitleScene(new TitleSceneState_Start()));

	return true;
}



void GameSystem::Uninit()
{
	// シーンマネージャーの解放
	SafeRelease::PlusUninit(&scene_manager_);

	// ImGUIの終了
//#ifdef _DEBUG
	ImGui_ImplDX9_Shutdown();
//#endif

	// キーボード入力の終了処理
	UninitKeyboard();

	// サウンドの終了処理
	UninitSound();

	// レンダラーの終了
	Renderer::getpInstance()->Uninit();
	Renderer::ReleaseInstance();
}



void GameSystem::Update()
{
	// ImGUIの更新
//#ifdef _DEBUG
	ImGui_ImplDX9_NewFrame();
//#endif

	// キーボードの入力処理
	UpdateKeyboard();

	// ゲームパッドの入力処理
	SetController();

	// シーンの更新
	scene_manager_->UpdateScene();
}



void GameSystem::Draw()
{
	// 描画開始
	//bool is_begin = Renderer::GetInstance()->DrawBegin();

	// シーンの描画
	scene_manager_->DrawScene();

	// 描画終了
	//Renderer::GetInstance()->DrawEnd(is_begin);

	// ImGUIの描画
//#ifdef _DEBUG
	ImGui::Render();
//#endif

	// バックバッファをフロントバッファに反映
	Renderer::getpInstance()->Present();
}



void GameSystem::LateUpdate()
{
	scene_manager_->Update();
}