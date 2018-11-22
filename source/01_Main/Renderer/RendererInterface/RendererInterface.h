//================================================================================
//
//    �����_���[�C���^�[�t�F�[�X�N���X
//    Author : Araki Kai                                �쐬�� : 2018/05/08
//
//================================================================================

#ifndef	_RENDERER_INTERFACE_H_
#define _RENDERER_INTERFACE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <Windows.h>



/*********************************************************//**
* @brief
* �����_���[�C���^�[�t�F�[�X�N���X
*
* �����_���[�̃C���^�[�t�F�[�X
*************************************************************/
class RendererInterface
{
//==============================
// ��ÓI�����o�֐�
//==============================
public:
	/**
	* @brief
	* �������z�f�X�g���N�^
	*/
	virtual ~RendererInterface() = 0;
	
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
	virtual bool Init(HINSTANCE hInstance, HWND hWnd, BOOL is_full_screen,
					  int window_width, int window_height) = 0;

	/**
	* @brief
	* �I���֐�
	*/
	virtual void Uninit() = 0;

	/**
	* @brief
	* �`��J�n�֐�
	*/
	virtual bool DrawBegin() = 0;

	/**
	* @brief
	* �`��I���֐�
	* @param
	* is_begin_scene : �`��J�n���������Ă��邩�t���O
	*/
	virtual void DrawEnd(bool is_begin_scene) = 0;	

	/**
	* @brief
	* �o�b�N�o�b�t�@���t�����g�o�b�t�@�ɔ��f�֐�
	*/
	virtual void Present() = 0;;
};



//****************************************
// ��ÓI�����o�֐���`(inline)
//****************************************
//--------------------------------------------------
// +�������z�f�X�g���N�^
//--------------------------------------------------
inline RendererInterface::~RendererInterface()
{
}



#endif



