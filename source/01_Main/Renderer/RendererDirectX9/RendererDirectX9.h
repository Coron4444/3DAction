//================================================================================
//
//    �����_���[DirectX9�N���X
//    Author : Araki Kai                                �쐬�� : 2018/05/08
//
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



/*********************************************************//**
* @brief
* �����_���[DirectX9�N���X
*
* DirectX9�p�����_���[�N���X
*************************************************************/
class RendererDirectX9 : public RendererInterface
{
//==============================
// ��ÓI�����o�ϐ�
//==============================
private:
	LPDIRECT3D9        direct3d_interface_ = nullptr;	//!< �C���^�[�t�F�[�X
	LPDIRECT3DDEVICE9  direct3d_device_ = nullptr;		//!< �f�o�C�X


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:
	// �萔
	static const DWORD FVF_VERTEX_3D;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public:
	// ���_�\����
	struct VERTEX_3D
	{
		Vec3   posisiont_;	// ���W
		Vec3   normal_;		// �@��
		Color4 color_;		// �J���[
		Vec2   texcoord_;	// �e�N�X�`�����W
	};


//==============================
// ��ÓI�����o�֐�
//==============================
public:
	// �����_���[�֌W
	/**
	* @brief
	* �������֐�
	* @param
	* hInstance : �C���X�^���X�n���h��
	* hWnd : Windows�n���h��
	* is_full_screen : �t���X�N���[���t���O
	* window_width : Window��
	* window_height : Window����
	*/
	bool Init(HINSTANCE hInstance, HWND hWnd, BOOL is_full_screen,
			  int window_width, int window_height);

	/**
	* @brief
	* �I���֐�
	*/
	void Uninit();

	/**
	* @brief
	* �`��J�n�֐�
	*/
	bool DrawBegin();

	/**
	* @brief
	* �`��I���֐�
	* @param
	* is_begin_scene : �`��J�n���������Ă��邩�t���O
	*/
	void DrawEnd(bool is_begin_scene);


	/**
	* @brief
	* �C���^�[�t�F�[�X�擾�֐�
	*/
	LPDIRECT3D9 GetInterface();

	/**
	* @brief
	* �f�o�C�X�擾�֐�
	*/
	LPDIRECT3DDEVICE9 GetDevice();

	/**
	* @brief
	* �A���t�@�����t���O�֐�
	*/
	void UseAlphaBlending(bool flag);

	/**
	* @brief
	* �A���t�@�����֐�(���`����)
	*/
	void SetAlphaBlending_Linear();
	
	/**
	* @brief
	* �A���t�@�����֐�(���Z����)
	*/
	void SetAlphaBlending_Add();

	/**
	* @brief
	* �A���t�@�����֐�(���Z����)
	*/
	void SetAlphaBlending_Sub();
	
	/**
	* @brief
	* �A���t�@�����֐�(��Z����)
	*/
	void SetAlphaBlending_Mul();
	
	/**
	* @brief
	* �A���t�@�����֐�(�Ă����ݍ���)
	*/
	void SetAlphaBlending_Baking();
	
	/**
	* @brief
	* �A���t�@�����֐�(�l�K�|�W���]����)
	*/
	void SetAlphaBlending_Nega();
	
	/**
	* @brief
	* �A���t�@�����֐�(�s��������)
	*/
	void SetAlphaBlending_Opacity();

	/**
	* @brief
	* �f�t�H���g�T���v���[�X�e�[�g�ݒ�֐�
	*/
	void SetDefaultSamplerState();
};



#endif