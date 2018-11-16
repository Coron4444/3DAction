//================================================================================
//
//    �Œ�@�\���_�V�F�[�_�[�N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/26
//
//================================================================================

#ifndef	_VERTEX_SHADER_FIXED_H_
#define _VERTEX_SHADER_FIXED_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "../../ShaderBase/VertexShaderNull.h"



//****************************************
// �N���X�錾
//****************************************
class Camera;
class DrawBase;



/*********************************************************//**
* @brief
* �Œ�@�\���_�V�F�[�_�[�N���X
*
* �Œ�@�\�̒��_�V�F�[�_�[�N���X
*************************************************************/
class VertexShaderFixed : public VertexShaderNull
{
//==============================
// ��ÓI�����o�ϐ�
//==============================
private:
	D3DLIGHT9 directional_light_;	//!< �f�B���N�V���i�����C�g


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

private :
	// �e�N�X�`���ݒ�
	void SetTexture(DrawBase* draw, unsigned object_index, unsigned mesh_index);

	// �}�e���A���ݒ�
	void SetMaterial(DrawBase* draw, unsigned object_index, unsigned mesh_index);

	// �g�U�Ɩ��X�V
	void UpdateDirectionalLignt();
};



#endif
