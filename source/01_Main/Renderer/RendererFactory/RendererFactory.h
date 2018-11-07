//================================================================================
//
//    �����_���[�t�@�N�g���[�N���X
//    Author : Araki Kai                                �쐬�� : 2018/11/01
//
//================================================================================

#ifndef	_RENDERE_FACTORY_H_
#define _RENDERE_FACTORY_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "../RendererInterface/RendererInterface.h"



/*********************************************************//**
* @brief
* �����_���[�t�@�N�g���[�N���X
*
* �����_���[�̃t�@�N�g���[
*************************************************************/
class RendererFactory
{
//==============================
// ��ÓI�����o�֐�
//==============================
public:
	/**
	* @brief
	* �����֐�
	*/
	virtual RendererInterface* Create() = 0;
};



#endif