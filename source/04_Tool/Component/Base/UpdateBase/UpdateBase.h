//================================================================================
//
//    �X�V���N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/26
//
//================================================================================

#ifndef	_UPDATE_BASE_H_
#define _UPDATE_BASE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "../ComponentBase/ComponentBase.h"

#ifdef _DEBUG
#include <ImGUI\imgui.h>
#include <ImGUI\imgui_impl_dx9.h>
#endif



/*********************************************************//**
* @brief
* �X�V���N���X
*
* �X�V�̊��N���X
*************************************************************/
class UpdateBase : public ComponentBase
{
//==============================
// ��ÓI�����o�֐�
//==============================
public:
	/**
	* @brief
	* ���z�f�X�g���N�^
	*/
	virtual ~UpdateBase() {}

	/**
	* @brief
	* �X�V�֐�
	*/
	virtual void Update() = 0;

	/**
	* @brief
	* ��X�V�֐�
	*/
	virtual void LateUpdate() = 0;

	/**
	* @brief
	* �f�o�b�O�\���֐�
	*/
	virtual void DebugDisplay() = 0;
};



#endif