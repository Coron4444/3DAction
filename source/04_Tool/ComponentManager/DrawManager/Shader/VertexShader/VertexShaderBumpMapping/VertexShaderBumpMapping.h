//================================================================================
//
//    �o���v�}�b�s���O���_�V�F�[�_�[�N���X
//    Author : Araki Kai                                �쐬�� : 2018/11/17
//
//================================================================================

#ifndef	_VERTEX_SHADER_BUMP_MAPPING_H_
#define _VERTEX_SHADER_BUMP_MAPPING_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "../../ShaderBase/VertexShaderNull.h"



//****************************************
// �N���X�錾
//****************************************
class ModelXObject;



/*********************************************************//**
* @brief
* �o���v�}�b�s���O���_�V�F�[�_�[�N���X
*
* �o���v�}�b�s���O�̒��_�V�F�[�_�[�N���X
*************************************************************/
class VertexShaderBumpMapping : public VertexShaderNull
{
//==============================
// �萔
//==============================
private:
	static const char* PATH;
	static const D3DVERTEXELEMENT9 DECLARATION[];


//==============================
// ��ÓI�����o�ϐ�
//==============================
private:
	// �v�Z�p
	D3DXMATRIX math_matrix_;

	// ���_�錾�I�u�W�F�N�g
	IDirect3DVertexDeclaration9* declaration_object_;

//==============================
// �ÓI�����o�֐�
//==============================
public:
	/**
	* @brief
	* ���_�錾�p���b�V���X�V�֐�
	* @param
	* model_x : X���f���I�u�W�F�N�g
	*/
	static void UpdateMeshDeclaration(ModelXObject* model_x);


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
