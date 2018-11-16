//================================================================================
//
//    �s�N�Z���V�F�[�_�[���N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/26
//
//================================================================================

#ifndef	_PIXEL_SHADER_BASE_H_
#define _PIXEL_SHADER_BASE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "ShaderBase.h"



/*********************************************************//**
* @brief
* �s�N�Z���V�F�[�_�[���N���X
*
* �s�N�Z���V�F�[�_�[���N���X
*************************************************************/
class PixelShaderBase : public ShaderBase
{
//==============================
// ��ÓI�����o�ϐ�
//==============================
private:
	LPDIRECT3DPIXELSHADER9 pixel_shader_ = nullptr;	//!< �s�N�Z���V�F�[�_�[


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
		GetDevice()->SetPixelShader(pixel_shader_);
	}

	// �v���p�e�B
	LPDIRECT3DPIXELSHADER9 GetPixelShader() { return pixel_shader_; }
};

#endif
