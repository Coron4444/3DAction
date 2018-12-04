//================================================================================
//!	@file	 RendererInterface.h
//!	@brief	 �����_���[InterfaceClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================
#ifndef	_RENDERER_INTERFACE_H_
#define _RENDERER_INTERFACE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <Windows.h>



//************************************************************														   
//! @brief   �����_���[InterfaceClass
//!
//! @details �����_���[��InterfaceClass
//************************************************************
class RendererInterface
{
//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief ���z�f�X�g���N�^
	//! @param void �Ȃ�
	//----------------------------------------
	virtual ~RendererInterface() {}
	
	//----------------------------------------
	//! @brief �������֐�
	//! @param[in] hInstance	  �C���X�^���X�n���h��
	//! @param[in] hWnd			  Windows�n���h��
	//! @param[in] is_full_screen �t���X�N���[���t���O
	//! @param[in] window_width	  �E�B���h�E��
	//! @param[in] window_height  �E�B���h�E����
	//! @retval bool �����������̗L��
	//----------------------------------------
	virtual bool Init(HINSTANCE hInstance, HWND hWnd, BOOL is_full_screen,
					  int window_width, int window_height) = 0;

	//----------------------------------------
	//! @brief �I���֐�
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void Uninit() = 0;

	//----------------------------------------
	//! @brief �`��J�n�֐�
	//! @param void �Ȃ�
	//! @retval bool �`��J�n�����̗L��
	//----------------------------------------
	virtual bool DrawBegin() = 0;

	//----------------------------------------
	//! @brief �`��I���֐�
	//! @param[in] is_begin_scene �`��J�n�����t���O
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void DrawEnd(bool is_begin_scene) = 0;

	//----------------------------------------
	//! @brief �o�b�N�o�b�t�@���t�����g�o�b�t�@�ɔ��f�֐�
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void Present() = 0;
};



#endif



