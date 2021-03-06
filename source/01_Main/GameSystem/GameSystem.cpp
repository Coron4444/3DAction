//================================================================================
//
//    ゲームシステムクラス
//    Author : Araki Kai                                作成日 : 2018/05/08
//
//================================================================================



//****************************************
// インクルード文
//****************************************
#include <assert.h>

#include "GameSystem.h"
#include <SafeRelease/SafeRelease.h>
#include <Renderer/Renderer.h>
#include <Renderer/RendererFactory/RendererFactoryDirectX9.h>
#include <Keyboard\Keyboard.h>
#include <Controller\Controller.h>
#include <Sound\Sound.h>
#include <SceneManager\SceneManager.h>
#include <Scenes\TitleScene\TitleScene.h>
#include <Scenes/TitleScene/TitleSceneState/TitleSceneState_Start/TitleSceneState_Start.h>
#include <Scenes\GameScene\GameScene.h>
#include <Scenes/GameScene/GameSceneState/GameSceneState_Start/GameSceneState_Start.h>


#ifdef _DEBUG
#include <ImGUI\imgui.h>
#include <ImGUI\imgui_impl_dx9.h>
#endif



//****************************************
// 非静的メンバ関数定義
//****************************************
//--------------------------------------------------
// +初期化関数
//--------------------------------------------------
bool GameSystem::Init(HINSTANCE hInstance, HWND hWnd, BOOL is_full_screen,
					  int window_width, int window_height)
{
	// レンダラーの初期化
	Renderer::GetInstance()->SetRenderer(new RendererFactoryDirectX9(),
										 Renderer::MODE::DIRECTX9);
	bool is_init = Renderer::GetInstance()->Init(hInstance, hWnd, is_full_screen,
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
#ifdef _DEBUG
	LPDIRECT3DDEVICE9 device = nullptr;
	Renderer::GetInstance()->GetDevice(&device);
	if (device == nullptr)
	{
		MessageBox(nullptr, "NotGetDevice!(GameSystem.cpp)", "Error", MB_OK);
		return false;
	}
	ImGui_ImplDX9_Init(hWnd, device);
#endif

	// シーンマネージャーの生成
	scene_manager_ = new SceneManager(new TitleScene(new TitleSceneState_Start()));

	return true;
}



//--------------------------------------------------
// +終了関数
//--------------------------------------------------
void GameSystem::Uninit()
{
	// シーンマネージャーの解放
	SafeRelease::Normal(&scene_manager_);

	// ImGUIの終了
#ifdef _DEBUG
	ImGui_ImplDX9_Shutdown();
#endif

	// キーボード入力の終了処理
	UninitKeyboard();

	// サウンドの終了処理
	UninitSound();

	// レンダラーの終了
	Renderer::GetInstance()->Uninit();
	Renderer::ReleaseInstance();
}



//--------------------------------------------------
// +更新関数
//--------------------------------------------------
void GameSystem::Update()
{
	// ImGUIの更新
#ifdef _DEBUG
	ImGui_ImplDX9_NewFrame();
#endif

	// キーボードの入力処理
	UpdateKeyboard();

	// ゲームパッドの入力処理
	SetController();

	// シーンの更新
	scene_manager_->UpdateScene();
}



//--------------------------------------------------
// +描画関数
//--------------------------------------------------
void GameSystem::Draw()
{
	// 描画開始
	bool is_begin = Renderer::GetInstance()->DrawBegin();

	// シーンの描画
	scene_manager_->DrawScene();

	// ImGUIの描画
#ifdef _DEBUG
	ImGui::Render();
#endif

	// 描画終了
	Renderer::GetInstance()->DrawEnd(is_begin);
}



//--------------------------------------------------
// +後更新関数
//--------------------------------------------------
void GameSystem::LateUpdate()
{
	scene_manager_->Update();
}