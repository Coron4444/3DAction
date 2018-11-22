//================================================================================
//
//    �󔒕`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/22
//
//================================================================================

#ifndef	_DRAW_NULL_H_
#define _DRAW_NULL_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <assert.h>
#include "../../Base/DrawBase/DrawBase.h"



/*********************************************************//**
* @brief
* �󔒕`��N���X
*
* �`��̋󔒃N���X
*************************************************************/
class DrawNull : public DrawBase
{
//==============================
// ��ÓI�����o�֐�
//==============================
public:
	/**
	* @brief
	* ���z�f�X�g���N�^
	*/
	virtual ~DrawNull() {}

	/**
	* @brief
	* �������֐�
	*/
	virtual void Init() override {}

	/**
	* @brief
	* �I���֐�
	*/
	virtual void Uninit() override {}

	/**
	* @brief
	* �X�V�֐�
	*/
	virtual void Update() {}

	/**
	* @brief
	* �`��֐�
	* @param
	* object_index : �I�u�W�F�N�g�C���f�b�N�X
	* mesh_index : ���b�V���C���f�b�N�X
	*/
	virtual void Draw(unsigned object_index, unsigned mesh_index) override
	{
		object_index = object_index;
		mesh_index = mesh_index;

		assert("�`��֐����������ł�");
	}

	/**
	* @brief
	* �f�o�b�O�\���֐�
	*/
	virtual void DebugDisplay() override {}

	/**
	* @brief
	* �`��O�ݒ�֐�
	* @param
	* camera : �J����
	* object_index : �I�u�W�F�N�g�C���f�b�N�X
	*/
	virtual void SettingBeforeDrawing(Camera* camera, unsigned object_index) override
	{
		camera = camera;
		object_index = object_index;
	}

	/**
	* @brief
	* �`���ݒ�֐�
	* @param
	* camera : �J����
	* object_index : �I�u�W�F�N�g�C���f�b�N�X
	*/
	virtual void SettingAfterDrawing(Camera* camera, unsigned object_index) override
	{
		camera = camera;
		object_index = object_index;
	}

	// �v���p�e�B
	virtual unsigned GetObjectNum() override { return 1; }
	virtual unsigned GetMeshNum(unsigned object_index) override
	{
		object_index = object_index;
		return 1;
	}
	virtual const MATRIX* GetMatrix(unsigned object_index) override
	{
		object_index = object_index;
		assert("�s��擾�v���p�e�B���������ł�");
		return nullptr;
	}
	virtual D3DMATERIAL9* GetMaterial(unsigned object_index, unsigned mesh_index)
	{
		object_index = object_index;
		mesh_index = mesh_index;
		return nullptr;
	}
	virtual LPDIRECT3DTEXTURE9 GetDecaleTexture(unsigned object_index, unsigned mesh_index)
	{
		object_index = object_index;
		mesh_index = mesh_index;
		return nullptr;
	}
	virtual LPDIRECT3DTEXTURE9 GetNormalTexture(unsigned object_index, unsigned mesh_index)
	{
		object_index = object_index;
		mesh_index = mesh_index;
		return nullptr;
	}
};



#endif