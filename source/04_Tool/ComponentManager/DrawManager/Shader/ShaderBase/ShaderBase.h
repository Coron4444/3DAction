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



//****************************************
// �N���X�錾
//****************************************
class Camera;
class DrawBase;



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

	// �v���p�e�B
	LPDIRECT3DDEVICE9* GetDevicePointer() { return &device_; }
	LPDIRECT3DDEVICE9 GetDevice() { return device_; }
	LPD3DXCONSTANTTABLE GetConstantTable() { return constant_table_; }
};

#endif
