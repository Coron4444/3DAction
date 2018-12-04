//================================================================================
//!	@file	 RendererFactoryInterface.h
//!	@brief	 �����_���[����InterfaceClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/01
//================================================================================
#ifndef	_RENDERE_FACTORY_INTERFACE_H_
#define _RENDERE_FACTORY_INTERFACE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "../RendererInterface/RendererInterface.h"



//************************************************************														   
//! @brief   �����_���[����InterfaceClass
//!
//! @details �����_���[������InterfaceClass
//************************************************************
class RendererFactoryInterface
{
//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief ���z�f�X�g���N�^
	//! @param void �Ȃ�
	//----------------------------------------
	virtual ~RendererFactoryInterface() {}

	//----------------------------------------
	//! @brief �����֐�
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual RendererInterface* Create() = 0;
};



#endif