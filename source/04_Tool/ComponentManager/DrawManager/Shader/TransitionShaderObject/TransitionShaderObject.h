//================================================================================
//
//    �g�����W�V�����V�F�[�_�[�I�u�W�F�N�g�N���X
//    Author : Araki Kai                                �쐬�� : 2018/08/21
//
//================================================================================

#ifndef	_TRANSITION_SHADER_OBJECT_H_
#define _TRANSITION_SHADER_OBJECT_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include "../ShaderObjectCommonMethod/ShaderObjectCommonMethod.h"



//**********************************************************************
//
// �N���X��`
//
//**********************************************************************

class TransitionShaderObject
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �萔
	static const char* EFFECT_PATH;


//------------------------------------------------------------
private :
	// �f�t�H���g�R���X�g���N�^
	TransitionShaderObject() = delete;

	// �R�s�[�R���X�g���N�^
	TransitionShaderObject(const TransitionShaderObject& class_name) = delete;

	// ������Z�q�̃I�[�o�[���[�h
	TransitionShaderObject& operator = (const TransitionShaderObject& class_name) = delete;

	
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// ���J�����o�֐�
	static void Init();
	static void Uninit();
	static void Draw(Camera* camera);
	static void ResetArray();
	static void DistributeDrawComponent(DrawComponent* draw_component, Camera* camera);
	static void SortTransparent(Camera* camera);



//------------------------------------------------------------
private :
	// �����o�ϐ�
	static LimitedPointerArray<DrawComponent*, DrawComponentManager::DRAW_ARRAY_NUM> shader_;
	
	static LPDIRECT3DDEVICE9 device_;

	// �v�Z�p
	static D3DXMATRIX math_matrix_;

	// �G�t�F�N�g�t�@�C���n���h���Q
	static LPD3DXEFFECT effect_;
	static D3DXHANDLE   technique_;
	static D3DXHANDLE   matrix_W_;
	static D3DXHANDLE   diffuse_light_vector_;
};



#endif
