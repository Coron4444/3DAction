//================================================================================
//
//    �V�F�[�_�[���N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/26
//
//================================================================================

#ifndef	_SHADER_BASE_H_
#define _SHADER_BASE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <Renderer/Renderer.h>
#include <Component/Base/DrawBase/DrawBase.h>
#include <ComponentManager/DrawManager/Camera/Camera.h>

#include <SafeRelease/SafeRelease.h>



/*********************************************************//**
* @brief
* �V�F�[�_�[���N���X
*
* �V�F�[�_�[���N���X
*************************************************************/
class ShaderBase
{
//==============================
// ��ÓI�����o�ϐ�
//==============================
private:
	LPDIRECT3DDEVICE9 device_ = nullptr;			//!< �f�o�C�X
	LPD3DXCONSTANTTABLE	constant_table_ = nullptr;	//!< �萔�e�[�u��


//==============================
// ��ÓI�����o�֐�
//==============================
public:
	/**
	* @brief
	* �������֐�
	*/
	virtual void Init() = 0;

	/**
	* @brief
	* �I���֐�
	*/
	virtual void Uninit() = 0;

	/**
	* @brief
	* �V�F�[�_�[�ݒ�֐�
	*/
	virtual void SetShader() = 0;

	/**
	* @brief
	* ���ʐݒ�֐�
	* @param
	* draw : �`����N���X
	* camera : �J����
	* object_index : �`��I�u�W�F�N�g�C���f�b�N�X
	*/
	virtual void CommonSetting(DrawBase* draw, Camera* camera,
							   unsigned object_index) = 0;

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
								 unsigned object_index, unsigned mesh_index) = 0;

	/**
	* @brief
	* �V�F�[�_�[�R���p�C���֐�
	* @param
	* file_name : �t�@�C����
	* entry_function : �G���g���֐���
	* version : �V�F�[�_�[�o�[�W����
	* compiled_code : �R���p�C���ς݃R�[�h
	* @return �R���p�C�������Ȃ�true
	*/
	bool ShaderCompile(const char* file_name, const char* entry_function,
					   const char* version, LPD3DXBUFFER* compiled_code)
	{
		LPD3DXBUFFER compil_error = nullptr;
		HRESULT hr = D3DXCompileShaderFromFile(file_name,			// �t�@�C����
											   nullptr,				// �v���v���Z�b�T��`�ւ̃|�C���^
											   nullptr,				// ID3DXInclude(#include�^������)
											   entry_function,		// �G���g���֐���
											   version,				// �V�F�[�_�[�o�[�W����
											   0,					// �R���p�C���I�v�V����
											   compiled_code,		// �R���p�C���ς݃R�[�h
											   &compil_error,		// �G���[���
											   &constant_table_);	// �R���X�^���g�e�[�u��
		// ����������
		if (SUCCEEDED(hr)) return true;
		
		// �G���[���b�Z�[�W
		if (compil_error) 
		{
			// �R���p�C���G���[����
			MessageBox(NULL, (LPSTR)compil_error->GetBufferPointer(), "Error", MB_OK);
		}
		else 
		{
			// ���̑��̃G���[
			MessageBox(NULL, "�V�F�[�_�[�t�@�C�����ǂݍ��߂܂���", "Error", MB_OK);
		}
		return false;
}

	/**
	* @brief
	* �f�o�C�X�̏������֐�
	*/
	void InitDevice()
	{ 
		// �f�o�C�X�̎擾
		Renderer::GetInstance()->GetDevice(&device_);
		if (device_ == nullptr)
		{
			MessageBox(nullptr, "NotGetDevice!(VertexShaderBase.cpp)", "Error", MB_OK);
			return;
		}
	}

	// �v���p�e�B
	LPDIRECT3DDEVICE9 GetDevice() { return device_; }
	LPD3DXCONSTANTTABLE GetConstantTable() { return constant_table_; }
};

#endif
