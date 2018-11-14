//================================================================================
//
//    �`��NONE�N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/22
//
//================================================================================

#ifndef	_DRAW_NONE_H_
#define _DRAW_NONE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <assert.h>
#include "DrawBase.h"



/*********************************************************//**
* @brief
* �`��NONE�N���X
*
* �`���NONE�N���X
*************************************************************/
class DrawNone : public DrawBase
{
//==============================
// ��ÓI�����o�֐�
//==============================
public:
	/**
	* @brief
	* ���z�f�X�g���N�^
	*/
	virtual ~DrawNone() {}

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
	* �`��֐�
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
	*/
	virtual void SettingBeforeDrawing(Camera* camera, unsigned object_index) override
	{
		camera = camera;
		object_index = object_index;
	}

	/**
	* @brief
	* �`���ݒ�֐�
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