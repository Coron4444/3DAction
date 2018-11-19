//================================================================================
//
//    �o���v�}�b�s���O�s�N�Z���V�F�[�_�[�N���X
//    Author : Araki Kai                                �쐬�� : 2018/11/17
//
//================================================================================

#ifndef	_PIXEL_SHADER_BUMP_MAPPING_H_
#define _PIXEL_SHADER_BUMP_MAPPING_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "../../ShaderBase/PixelShaderNull.h"



/*********************************************************//**
* @brief
* �o���v�}�b�s���O�s�N�Z���V�F�[�_�[�N���X
*
* �o���v�}�b�s���O�̃s�N�Z���V�F�[�_�[�N���X
*************************************************************/
class PixelShaderBumpMapping : public PixelShaderNull
{
//==============================
// �萔
//==============================
private:
	static const char* PATH;


//==============================
// ��ÓI�����o�ϐ�
//==============================
private:
	// �v�Z�p
	D3DXMATRIX math_matrix_;



//==============================
// ��ÓI�����o�֐�
//==============================
public:
	/**
	* @brief
	* �������֐�
	*/
	void Init();

	/**
	* @brief
	* �I���֐�
	*/
	void Uninit();

	/**
	* @brief
	* ���ʐݒ�֐�
	* @param
	* draw : �`����N���X
	* camera : �J����
	* object_index : �`��I�u�W�F�N�g�C���f�b�N�X
	*/
	void CommonSetting(DrawBase* draw, Camera* camera, unsigned object_index);

	/**
	* @brief
	* �ŗL�ݒ�֐�
	* @param
	* draw : �`����N���X
	* camera : �J����
	* object_index : �`��I�u�W�F�N�g�C���f�b�N�X
	* mesh_index : ���b�V���C���f�b�N�X
	*/
	void SpecificSetting(DrawBase* draw, Camera* camera, 
						 unsigned object_index, unsigned mesh_index);
};



#endif
