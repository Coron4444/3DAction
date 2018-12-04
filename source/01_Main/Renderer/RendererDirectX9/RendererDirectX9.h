//================================================================================
//!	@file	 RendererDirectX9.h
//!	@brief	 �����_���[DirectX9Class
//! @details 
//!	@author  Kai Araki									@date 2018/11/01
//================================================================================
#ifndef	_RENDERE_DIRECTX9_H_
#define _RENDERE_DIRECTX9_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <d3d9.h>
#include <d3dx9.h>
#include <assert.h>

#include "../RendererInterface/RendererInterface.h"
#include <Vector3D.h>



//************************************************************														   
//! @brief   �����_���[DirectX9Class
//!
//! @details DirectX9�p�����_���[Class
//************************************************************
class RendererDirectX9 : public RendererInterface
{
//****************************************														   
//! @brief   ���_Class
//!
//! @details ���_�p��Class
//****************************************
public:
	class VERTEX_3D
	{
	//====================
	// �ϐ�
	//====================
	public:
		Vec3   posisiont_;	//!< ���W
		Vec3   normal_;		//!< �@��
		Color4 color_;		//!< �J���[
		Vec2   texcoord_;	//!< �e�N�X�`�����W
	};


//====================
// �萔
//====================
public:
	static const DWORD FVF_VERTEX_3D;	//!< FVF


//====================
// �ϐ�
//====================
private:
	LPDIRECT3D9        direct3d_interface_ = nullptr;	//!< �C���^�[�t�F�[�X
	LPDIRECT3DDEVICE9  direct3d_device_ = nullptr;		//!< �f�o�C�X


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
			  int window_width, int window_height) override;

	//----------------------------------------
	//! @brief �I���֐�
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Uninit() override;

	//----------------------------------------
	//! @brief �`��J�n�֐�
	//! @param void �Ȃ�
	//! @retval bool �`��J�n�����̗L��
	//----------------------------------------
	bool DrawBegin() override;

	//----------------------------------------
	//! @brief �`��I���֐�
	//! @param[in] is_begin_scene �`��J�n�����t���O
	//! @retval void �Ȃ�
	//----------------------------------------
	void DrawEnd(bool is_begin_scene) override;

	//----------------------------------------
	//! @brief �o�b�N�o�b�t�@���t�����g�o�b�t�@�ɔ��f�֐�
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void Present() override;

	//----------------------------------------
	//! @brief �o�b�N�o�b�t�@���t�����g�o�b�t�@�ɔ��f�֐�
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void UseAlphaBlending(bool flag);

	//----------------------------------------
	//! @brief �A���t�@�����֐�(���`����)
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void SetAlphaBlending_Linear();

	//----------------------------------------
	//! @brief �A���t�@�����֐�(���Z����)
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void SetAlphaBlending_Add();

	//----------------------------------------
	//! @brief �A���t�@�����֐�(���Z����)
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void SetAlphaBlending_Sub();

	//----------------------------------------
	//! @brief �A���t�@�����֐�(��Z����)
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void SetAlphaBlending_Mul();

	//----------------------------------------
	//! @brief �A���t�@�����֐�(�Ă����ݍ���)
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void SetAlphaBlending_Baking();

	//----------------------------------------
	//! @brief �A���t�@�����֐�(�l�K�|�W���]����)
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void SetAlphaBlending_Nega();

	//----------------------------------------
	//! @brief �A���t�@�����֐�(�s��������)
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void SetAlphaBlending_Opacity();

	//----------------------------------------
	//! @brief �f�t�H���g�T���v���[�X�e�[�g�ݒ�֐�
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	void SetDefaultSamplerState();

	// �v���p�e�B
	LPDIRECT3D9 getpInterface() { return direct3d_interface_; }
	LPDIRECT3DDEVICE9 getpDevice() { return direct3d_device_; }
};



#endif