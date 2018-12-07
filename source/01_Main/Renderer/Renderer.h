//================================================================================
//!	@file	 Renderer.h
//!	@brief	 �����_���[Class
//! @details Singleton
//!	@author  Kai Araki									@date 2018/11/01
//================================================================================
#ifndef	_RENDERE_H_
#define _RENDERE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <renderer/RendererFactory/RendererFactoryDirectX9/RendererFactoryDirectX9.h>
#include <SafeRelease/SafeRelease.h>
#include <Vector3D.h>



//************************************************************														   
//! @brief   �����_���[Class
//!
//! @details �����_���[��Class(Singleton)
//************************************************************
class Renderer
{
//====================
// �񋓌^��`
//====================
public:
	enum MODE
	{
		NONE = -1,
		DIRECTX9,
		DIRECTX11,
		OPEN_GL,
		MAX
	};


//====================
// static�ϐ�
//====================
private:
	static Renderer* instance_;				//!< �C���X�^���X
	static RendererInterface* renderer_;	//!< �����_���[


//====================
// �ϐ�
//====================
private:
	MODE mode_ = MODE::NONE;		//!< ���[�h


//====================
// static�֐�
//====================
public:
	//----------------------------------------
	//! @brief �C���X�^���X����֐�
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	static void ReleaseInstance();

	// �v���p�e�B
	static Renderer* getpInstance();


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief �������֐�
	//! @param[in] hInstance	  �C���X�^���X�n���h��
	//! @param[in] hWnd			  Windows�n���h��
	//! @param[in] is_full_screen �t���X�N���[���t���O
	//! @param[in] window_width	  �E�B���h�E��
	//! @param[in] window_height  �E�B���h�E����
	//! @retval bool �����������̗L��
	//----------------------------------------
	bool Init(HINSTANCE hInstance, HWND hWnd, BOOL is_full_screen,
			  int window_width, int window_height);

	//----------------------------------------
	//! @brief �I���֐�
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Uninit();

	//----------------------------------------
	//! @brief �`��J�n�֐�
	//! @param void �Ȃ�
	//! @retval bool �`��J�n�����̗L��
	//----------------------------------------
	bool DrawBegin();

	//----------------------------------------
	//! @brief �`��I���֐�
	//! @param[in] is_begin_scene �`��J�n�����t���O
	//! @retval void �Ȃ�
	//----------------------------------------
	void DrawEnd(bool is_begin_scene);

	//----------------------------------------
	//! @brief �o�b�N�o�b�t�@���t�����g�o�b�t�@�ɔ��f�֐�
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Present();

	// �v���p�e�B
	RendererInterface* getpRenderer() { return renderer_; }
	void setRenderer(RendererFactoryInterface* factory, MODE mode)
	{
		if (renderer_ == nullptr)
		{
			renderer_ = factory->Create();
			mode_ = mode;
		}

		SafeRelease::Normal(&factory);
	}
	template <class Type>
	void getInterface(Type** pointer)
	{
		if (renderer_ == nullptr) return;
		switch (mode_)
		{
			case Renderer::DIRECTX9:
			{
				*pointer = ((RendererDirectX9*)renderer_)->getpInterface();
				break;
			}
			case Renderer::DIRECTX11:
			{
				break;
			}
			case Renderer::OPEN_GL:
			{
				break;
			}
			default:
			{
				break;
			}
		}
	}
	template <class Type>
	void getDevice(Type** pointer)
	{
		if (renderer_ == nullptr) return;
		switch (mode_)
		{
			case Renderer::DIRECTX9:
			{
				*pointer = ((RendererDirectX9*)renderer_)->getpDevice();
				break;
			}
			case Renderer::DIRECTX11:
			{
				break;
			}
			case Renderer::OPEN_GL:
			{
				break;
			}
			default:
			{
				break;
			}
		}
	}

private:
	//----------------------------------------
	//! @brief �R���X�g���N�^
	//! @param void �Ȃ�
	//----------------------------------------
	Renderer() {}

//====================
// �����ς݊֐�
//====================
private:
	Renderer(const Renderer& class_name) = delete;
	Renderer& operator = (const Renderer& class_name) = delete;
};



#endif