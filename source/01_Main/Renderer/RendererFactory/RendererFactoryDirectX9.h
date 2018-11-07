//================================================================================
//
//    �����_���[�t�@�N�g���[DirectX9�N���X
//    Author : Araki Kai                                �쐬�� : 2018/11/01
//
//================================================================================

#ifndef	_RENDERE_FACTORY_DIRECTX9_H_
#define _RENDERE_FACTORY_DIRECTX9_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "../RendererFactory/RendererFactory.h"
#include "../RendererDirectX9/RendererDirectX9.h"



/*********************************************************//**
* @brief
* �����_���[�t�@�N�g���[DirectX9�N���X
*
* �����_���[DirectX9�̃t�@�N�g���[
*************************************************************/
class RendererFactoryDirectX9 : public RendererFactory
{
//==============================
// ��ÓI�����o�֐�
//==============================
public:
	/**
	* @brief
	* �����֐�
	*/
	RendererInterface* Create() override
	{
		return new RendererDirectX9();
	}
};



#endif