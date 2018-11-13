//================================================================================
//
//    �Œ�@�\�s�N�Z���V�F�[�_�[�N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/26
//
//================================================================================

#ifndef	_FIXED_PIXEL_SHADER_H_
#define _FIXED_PIXEL_SHADER_H_



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
* �Œ�@�\�s�N�Z���V�F�[�_�[�N���X
*
* �Œ�@�\�̃s�N�Z���V�F�[�_�[�N���X
*************************************************************/
class FixedPixelShader
{
//==============================
// ��ÓI�����o�ϐ�
//==============================
private:
	LPDIRECT3DDEVICE9 device_;			//!< �f�o�C�X


//==============================
// ��ÓI�����o�֐�
//==============================
public:
	/**
	* @brief
	* �������֐�
	*/
	void Init();

	/**
	* @brief
	* �I���֐�
	*/
	void Uninit();

	/**
	* @brief
	* �V�F�[�_�[�ݒ�֐�
	*/
	void SetShader();

	/**
	* @brief
	* ���ʐݒ�֐�
	* @param
	* draw : �`����N���X
	* camera : �J����
	* object_index : �`��I�u�W�F�N�g�C���f�b�N�X
	*/
	void CommonSetting(DrawBase* draw, Camera* camera, unsigned object_index);

	/**
	* @brief
	* �ŗL�ݒ�֐�
	* @param
	* draw : �`����N���X
	* camera : �J����
	* object_index : �`��I�u�W�F�N�g�C���f�b�N�X
	* mesh_index : ���b�V���C���f�b�N�X
	*/
	void SpecificSetting(DrawBase* draw, Camera* camera, 
						 unsigned object_index, unsigned mesh_index);
};



#endif
