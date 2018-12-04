//================================================================================
//!	@file	 DrawBase.h
//!	@brief	 �`��BaseClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
//================================================================================
#ifndef	_DRAW_BASE_H_
#define _DRAW_BASE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "../ComponentBase/ComponentBase.h"
#include "DrawOrderList/DrawOrderList.h"
#include <ComponentManager/DrawManager/Camera/Camera.h>

#include <Vector3D.h>



//************************************************************														   
//! @brief   �`��BaseClass
//!
//! @details �`���BaseClass
//************************************************************
class DrawBase : public ComponentBase
{
//====================
// �ϐ�
//====================
private:
	DrawOrderList draw_order_list_;							//!< �`�撍�����X�g
	Camera::Type save_camera_type_ = Camera::Type::NONE;	//!< �J�����^�C�v�ۑ��p


//====================
// �֐�
//====================
public:
	//----------------------------------------
	//! @brief ���z�f�X�g���N�^
	//! @param void �Ȃ�
	//----------------------------------------
	virtual ~DrawBase() {}

	//----------------------------------------
	//! @brief �`��֐�
	//! @param[in] object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @param[in] mesh_index   ���b�V���C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void Draw(unsigned object_index, unsigned mesh_index) = 0;

	//----------------------------------------
	//! @brief �`��O�ݒ�֐�
	//! @param[in, out] camera       �J����
	//! @param[in]      object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void SettingBeforeDrawing(Camera* camera, unsigned object_index) = 0;

	//----------------------------------------
	//! @brief �`���ݒ�֐�
	//! @param[in, out] camera       �J����
	//! @param[in]      object_index �I�u�W�F�N�g�C���f�b�N�X
	//! @retval void �Ȃ�
	//----------------------------------------
	virtual void SettingAfterDrawing(Camera* camera, unsigned object_index) = 0;

	//----------------------------------------
	//! @brief ����J�����^�C�v�ύX�֐�
	//! @param[in, out] camera  �J����
	//! @param[in]      type �@ �J�����^�C�v
	//! @retval void �Ȃ�
	//----------------------------------------
	void LimitedChangeCameraType(Camera* camera, Camera::Type type)
	{
		save_camera_type_ = camera->GetType();
		camera->SetType(type);
	}

	//----------------------------------------
	//! @brief �J�����^�C�v�����֐�
	//! @param[in, out] camera �J����
	//! @retval void �Ȃ�
	//----------------------------------------
	void RevivalCameraType(Camera* camera)
	{
		if (save_camera_type_ == Camera::Type::NONE) return;
		camera->SetType(save_camera_type_);
	}

	// �v���p�e�B
	virtual unsigned getObjectNum() = 0;
	virtual unsigned getMeshNum(unsigned object_index) = 0;
	virtual MATRIX* getpMatrix(unsigned object_index) = 0;
	virtual D3DMATERIAL9* getpMaterial(unsigned object_index, unsigned mesh_index) = 0;
	virtual LPDIRECT3DTEXTURE9 getpDecaleTexture(unsigned object_index, unsigned mesh_index) = 0;
	virtual LPDIRECT3DTEXTURE9 getpNormalTexture(unsigned object_index, unsigned mesh_index) = 0;
	DrawOrderList* getpDrawOrderList() { return &draw_order_list_; }
};



#endif