//================================================================================
//
//    �Q�[���V�X�e���N���X
//    Author : Araki Kai                                �쐬�� : 2018/05/08
//
//================================================================================



//****************************************
// �C���N���[�h��
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
// ��ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
bool GameSystem::Init(HINSTANCE hInstance, HWND hWnd, BOOL is_full_screen,
					  int window_width, int window_height)
{
	// �����_���[�̏�����
	Renderer::GetInstance()->SetRenderer(new RendererFactoryDirectX9(),
										 Renderer::MODE::DIRECTX9);
	bool is_init = Renderer::GetInstance()->Init(hInstance, hWnd, is_full_screen,
												 window_width, window_height);

#ifdef _DEBUG
	assert(is_init && "DirectX9�p�����_���[�̏������Ɏ��s!!");
#else
	is_init = is_init;
#endif

	// �T�E���h�̏�����
	InitSound(hWnd);

	// �L�[�{�[�h���͂̏�����
	InitKeyboard(hInstance, hWnd);

	// ImGUI�̏�����
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

	// �V�[���}�l�[�W���[�̐���
	scene_manager_ = new SceneManager(new TitleScene(new TitleSceneState_Start()));

	return true;
}



//--------------------------------------------------
// +�I���֐�
//--------------------------------------------------
void GameSystem::Uninit()
{
	// �V�[���}�l�[�W���[�̉��
	SafeRelease::Normal(&scene_manager_);

	// ImGUI�̏I��
#ifdef _DEBUG
	ImGui_ImplDX9_Shutdown();
#endif

	// �L�[�{�[�h���͂̏I������
	UninitKeyboard();

	// �T�E���h�̏I������
	UninitSound();

	// �����_���[�̏I��
	Renderer::GetInstance()->Uninit();
	Renderer::ReleaseInstance();
}



//--------------------------------------------------
// +�X�V�֐�
//--------------------------------------------------
void GameSystem::Update()
{
	// ImGUI�̍X�V
#ifdef _DEBUG
	ImGui_ImplDX9_NewFrame();
#endif

	// �L�[�{�[�h�̓��͏���
	UpdateKeyboard();

	// �Q�[���p�b�h�̓��͏���
	SetController();

	// �V�[���̍X�V
	scene_manager_->UpdateScene();
}



//--------------------------------------------------
// +�`��֐�
//--------------------------------------------------
void GameSystem::Draw()
{
	// �`��J�n
	bool is_begin = Renderer::GetInstance()->DrawBegin();

	// �V�[���̕`��
	scene_manager_->DrawScene();

	// ImGUI�̕`��
#ifdef _DEBUG
	ImGui::Render();
#endif

	// �`��I��
	Renderer::GetInstance()->DrawEnd(is_begin);
}



//--------------------------------------------------
// +��X�V�֐�
//--------------------------------------------------
void GameSystem::LateUpdate()
{
	scene_manager_->Update();
}