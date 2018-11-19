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
	LPDIRECT3DPIXELSHADER9 pixel_shader_ = nullptr;		//!< �s�N�Z���V�F�[�_�[


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

	/**
	* @brief
	* �s�N�Z���V�F�[�_�[�R���p�C���֐�
	* @param
	* file_name : �t�@�C����
	* entry_function : �G���g���֐���
	* version : �V�F�[�_�[�o�[�W����
	* @return �R���p�C�������Ȃ�true
	*/
	bool PixelShaderCompile(const char* file_name, const char* entry_function,
							 const char* version)
	{
		LPD3DXBUFFER compiled_code;
		bool is_compile = ShaderBase::ShaderCompile(file_name, entry_function,
													version, &compiled_code);
		if (!is_compile) return false;

		HRESULT hr = ShaderBase::GetDevice()
			->CreatePixelShader((DWORD*)compiled_code->GetBufferPointer(),
								 &pixel_shader_);

		// ����������
		if (SUCCEEDED(hr)) return true;

		// �G���[���b�Z�[�W
		MessageBox(nullptr, "�s�N�Z���V�F�[�_�[�쐬���s", "Error", MB_OK);
		return false;
	}

	/**
	* @brief
	* �s�N�Z���V�F�[�_�[����֐�
	*/
	void ReleasePixelShader()
	{
		SafeRelease::PlusRelease(&pixel_shader_);
	}

	// �v���p�e�B
	LPDIRECT3DPIXELSHADER9 GetPixelShader() { return pixel_shader_; }
};

#endif
