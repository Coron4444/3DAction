//================================================================================
//
//    �`����N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/22
//
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

#ifdef _DEBUG
#include <ImGUI\imgui.h>
#include <ImGUI\imgui_impl_dx9.h>
#endif



/*********************************************************//**
* @brief
* �`����N���X
*
* �`��̊��N���X
*************************************************************/
class DrawBase : public ComponentBase
{
//==============================
// ��ÓI�����o�ϐ�
//==============================
private:
	DrawOrderList draw_order_list_;							//!< �`�撍�����X�g
	Camera::Type save_camera_type_ = Camera::Type::NONE;	//!< �J�����^�C�v�ۑ��p


//==============================
// ��ÓI�����o�֐�
//==============================
public:
	/**
	* @brief
	* ���z�f�X�g���N�^
	*/
	virtual ~DrawBase() {}

	/**
	* @brief
	* �X�V�֐�
	*/
	virtual void Update() = 0;

	/**
	* @brief
	* �`��֐�
	* @param
	* object_index : �I�u�W�F�N�g�C���f�b�N�X
	* mesh_index : ���b�V���C���f�b�N�X
	*/
	virtual void Draw(unsigned object_index, unsigned mesh_index) = 0;

	/**
	* @brief
	* �f�o�b�O�\���֐�
	*/
	virtual void DebugDisplay() {}

	/**
	* @brief
	* �`��O�ݒ�֐�
	* @param
	* camera : �J����
	* object_index : �I�u�W�F�N�g�C���f�b�N�X
	*/
	virtual void SettingBeforeDrawing(Camera* camera, unsigned object_index) = 0;

	/**
	* @brief
	* �`���ݒ�֐�
	* @param
	* camera : �J����
	* object_index : �I�u�W�F�N�g�C���f�b�N�X
	*/
	virtual void SettingAfterDrawing(Camera* camera, unsigned object_index) = 0;


	/**
	* @brief
	* ����J�����^�C�v�ύX�֐�
	* @param
	* camera : �J����
	* type : �J�����^�C�v
	*/
	void LimitedChangeCameraType(Camera* camera, Camera::Type type)
	{
		save_camera_type_ = camera->GetType();
		camera->SetType(type);
	}

	/**
	* @brief
	* �J�����^�C�v�����֐�
	* @param
	* camera : �J����
	*/
	void RevivalCameraType(Camera* camera)
	{
		if (save_camera_type_ == Camera::Type::NONE) return;
		camera->SetType(save_camera_type_);
	}

	// �v���p�e�B
	virtual unsigned GetObjectNum() = 0;
	virtual unsigned GetMeshNum(unsigned object_index) = 0;
	virtual const MATRIX* GetMatrix(unsigned object_index) = 0;
	virtual D3DMATERIAL9* GetMaterial(unsigned object_index, unsigned mesh_index) = 0;
	virtual LPDIRECT3DTEXTURE9 GetDecaleTexture(unsigned object_index, unsigned mesh_index) = 0;
	virtual LPDIRECT3DTEXTURE9 GetNormalTexture(unsigned object_index, unsigned mesh_index) = 0;
	DrawOrderList* GetDrawOrderList() { return &draw_order_list_; }
};



#endif