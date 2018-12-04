//================================================================================
//!	@file	 DrawNull.h
//!	@brief	 �󔒕`��Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_DRAW_NULL_H_
#define _DRAW_NULL_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <assert.h>

#include "../../Base/DrawBase/DrawBase.h"



//************************************************************														   
//! @brief   �󔒕`��Class
//!
//! @details �`��̋�Class
//************************************************************
class DrawNull : public DrawBase
{
//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief ���z�f�X�g���N�^
	//! @param void �Ȃ�
	//----------------------------------------
	virtual ~DrawNull() {}

	//----------------------------------------
	//! @brief �������֐�
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void Init() override {}

	//----------------------------------------
	//! @brief �I���֐�
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void Uninit() override {}

	//----------------------------------------
	//! @brief �X�V�֐�
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void Update() {}

	//----------------------------------------
	//! @brief �f�o�b�O�\���֐�
	//! @param void �Ȃ�
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void DebugDisplay() {}

	//----------------------------------------
	//! @brief �`��֐�
	//! @param[in] object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @param[in] mesh_index   ���b�V���C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void Draw(unsigned object_index, unsigned mesh_index) override
	{
		object_index = object_index;
		mesh_index = mesh_index;

		assert("�`��֐����������ł�");
	}

	//----------------------------------------
	//! @brief �`��O�ݒ�֐�
	//! @param[in, out] camera       �J����
	//! @param[in]      object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void SettingBeforeDrawing(Camera* camera, unsigned object_index) override
	{
		camera = camera;
		object_index = object_index;
	}

	//----------------------------------------
	//! @brief �`���ݒ�֐�
	//! @param[in, out] camera       �J����
	//! @param[in]      object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void SettingAfterDrawing(Camera* camera, unsigned object_index) override
	{
		camera = camera;
		object_index = object_index;
	}

	// �v���p�e�B
	virtual unsigned getObjectNum() override { return 1; }
	virtual unsigned getMeshNum(unsigned object_index) override
	{
		object_index = object_index;
		return 1;
	}
	virtual MATRIX* getpMatrix(unsigned object_index) override
	{
		object_index = object_index;
		assert("�s��擾�v���p�e�B���������ł�");
		return nullptr;
	}
	virtual D3DMATERIAL9* getpMaterial(unsigned object_index, 
									   unsigned mesh_index) override
	{
		object_index = object_index;
		mesh_index = mesh_index;
		return nullptr;
	}
	virtual LPDIRECT3DTEXTURE9 getpDecaleTexture(unsigned object_index, 
												 unsigned mesh_index) override
	{
		object_index = object_index;
		mesh_index = mesh_index;
		return nullptr;
	}
	virtual LPDIRECT3DTEXTURE9 getpNormalTexture(unsigned object_index, 
												unsigned mesh_index) override
	{
		object_index = object_index;
		mesh_index = mesh_index;
		return nullptr;
	}
};



#endif