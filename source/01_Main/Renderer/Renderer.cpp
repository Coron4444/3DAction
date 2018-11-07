//================================================================================
//
//    �����_���[�N���X
//    Author : Araki Kai                                �쐬�� : 2018/1/01
//
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "Renderer.h"
#include <SafeRelease/SafeRelease.h>



//****************************************
// �ÓI�����o�ϐ���`
//****************************************

Renderer* Renderer::instance_ = nullptr;
RendererInterface* Renderer::renderer_ = nullptr;



//****************************************
// �ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�C���X�^���X�擾�֐�
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
// +�C���X�^���X����֐�
//--------------------------------------------------
void Renderer::ReleaseInstance()
{
	SafeRelease::Normal(&instance_);
}



//****************************************
// ��ÓI�����o�֐���`
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
// +�����_���[�ݒ�֐�
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