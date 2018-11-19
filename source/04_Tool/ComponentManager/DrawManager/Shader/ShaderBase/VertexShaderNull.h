//================================================================================
//
//    �󔒒��_�V�F�[�_�[�N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/26
//
//================================================================================

#ifndef	_VERTEX_SHADER_NULL_H_
#define _VERTEX_SHADER_NULL_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "VertexShaderBase.h"



/*********************************************************//**
* @brief
* �󔒒��_�V�F�[�_�[�N���X
*
* �󔒒��_�V�F�[�_�[�N���X
*************************************************************/
class VertexShaderNull : public VertexShaderBase
{
//==============================
// ��ÓI�����o�֐�
//==============================
public:
	/**
	* @brief
	* �������֐�
	*/
	virtual void Init()	
	{
		ShaderBase::InitDevice();
	}

	/**
	* @brief
	* �I���֐�
	*/
	virtual void Uninit() {}

	/**
	* @brief
	* ���ʐݒ�֐�
	* @param
	* draw : �`����N���X
	* camera : �J����
	* object_index : �`��I�u�W�F�N�g�C���f�b�N�X
	*/
	virtual void CommonSetting(DrawBase* draw, Camera* camera,
							   unsigned object_index) {}

	/**
	* @brief
	* �ŗL�ݒ�֐�
	* @param
	* draw : �`����N���X
	* camera : �J����
	* object_index : �`��I�u�W�F�N�g�C���f�b�N�X
	* mesh_index : ���b�V���C���f�b�N�X
	*/
	virtual void SpecificSetting(DrawBase* draw, Camera* camera,
								 unsigned object_index, unsigned mesh_index) {}
};

#endif
