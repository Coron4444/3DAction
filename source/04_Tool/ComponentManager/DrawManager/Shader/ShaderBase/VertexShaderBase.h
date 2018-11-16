//================================================================================
//
//    ���_�V�F�[�_�[���N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/26
//
//================================================================================

#ifndef	_VERTEX_SHADER_BASE_H_
#define _VERTEX_SHADER_BASE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "ShaderBase.h"



/*********************************************************//**
* @brief
* ���_�V�F�[�_�[���N���X
*
* ���_�V�F�[�_�[���N���X
*************************************************************/
class VertexShaderBase : public ShaderBase
{
//==============================
// ��ÓI�����o�ϐ�
//==============================
private:
	LPDIRECT3DVERTEXSHADER9 vertex_shader_ = nullptr;	//!< ���_�V�F�[�_�[


//==============================
// ��ÓI�����o�֐�
//==============================
public:
	/**
	* @brief
	* �V�F�[�_�[�ݒ�֐�
	*/
	void SetShader() override
	{
		GetDevice()->SetVertexShader(vertex_shader_);
	}

	// �v���p�e�B
	LPDIRECT3DVERTEXSHADER9 GetVertexShader() { return vertex_shader_; }
};

#endif
