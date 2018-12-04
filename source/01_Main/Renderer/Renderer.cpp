//================================================================================
//!	@file	 Renderer.cpp
//!	@brief	 �����_���[Class
//! @details Singleton
//!	@author  Kai Araki									@date 2018/11/01
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "Renderer.h"

#include <SafeRelease/SafeRelease.h>



//****************************************
// static�ϐ���`
//****************************************
Renderer* Renderer::instance_ = nullptr;
RendererInterface* Renderer::renderer_ = nullptr;



//****************************************
// static�֐���`
//****************************************
//--------------------------------------------------
// +�C���X�^���X����֐�
//--------------------------------------------------
void Renderer::ReleaseInstance()
{
	SafeRelease::Normal(&instance_);
}



//--------------------------------------------------
// +�C���X�^���X�擾�֐�
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
// �֐���`
//****************************************
//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
bool Renderer::Init(HINSTANCE hInstance, HWND hWnd, BOOL is_full_screen,
					int window_width, int window_height)
{
	if (renderer_ == nullptr) return false;
	return renderer_->Init(hInstance, hWnd, is_full_screen, window_width, window_height);
}



//--------------------------------------------------
// +�I�������֐�
//--------------------------------------------------
void Renderer::Uninit()
{
	// �����_���[�̉��
	SafeRelease::PlusUninit(&renderer_);

	// ���[�h�̏�����
	mode_ = MODE::NONE;
}



//--------------------------------------------------
// +�`��J�n�֐�
//--------------------------------------------------
bool Renderer::DrawBegin()
{
	if (renderer_ == nullptr) return false;
	return renderer_->DrawBegin();
}



//--------------------------------------------------
// +�`��I���֐�
//--------------------------------------------------

void Renderer::DrawEnd(bool is_begin_scene)
{
	if (renderer_ == nullptr) return;
	renderer_->DrawEnd(is_begin_scene);
}



//--------------------------------------------------
// +�o�b�N�o�b�t�@���t�����g�o�b�t�@�ɔ��f�֐�
//--------------------------------------------------
void Renderer::Present()
{
	if (renderer_ == nullptr) return;
	renderer_->Present();
}