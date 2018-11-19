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

	/**
	* @brief
	* ���_�V�F�[�_�[�R���p�C���֐�
	* @param
	* file_name : �t�@�C����
	* entry_function : �G���g���֐���
	* version : �V�F�[�_�[�o�[�W����
	* @return �R���p�C�������Ȃ�true
	*/
	bool VertexShaderCompile(const char* file_name, const char* entry_function,
							 const char* version)
	{
		LPD3DXBUFFER compiled_code;
		bool is_compile = ShaderBase::ShaderCompile(file_name, entry_function,
													version, &compiled_code);
		if (!is_compile) return false;

		HRESULT hr = ShaderBase::GetDevice()
			->CreateVertexShader((DWORD*)compiled_code->GetBufferPointer(),
								 &vertex_shader_);

		// ����������
		if (SUCCEEDED(hr)) return true;

		// �G���[���b�Z�[�W
		MessageBox(nullptr, "���_�V�F�[�_�[�쐬���s", "Error", MB_OK);
		return false;
	}

	/**
	* @brief
	* ���_�V�F�[�_�[����֐�
	*/
	void ReleaseVertexShader()
	{
		SafeRelease::PlusRelease(&vertex_shader_);
	}

	// �v���p�e�B
	LPDIRECT3DVERTEXSHADER9 GetVertexShader() { return vertex_shader_; }
};

#endif
