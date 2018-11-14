//================================================================================
//
//    �`���[�g���A�����S01�`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/09/02
//
//================================================================================

#ifndef	_TUTORIAL_LOGO_01_DRAW_H_
#define _TUTORIAL_LOGO_01_DRAW_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <string>

#include <Component/DrawBase/DrawNone.h>
#include "../TutorialLogo01.h"

#include <ResourceManager\ResourceManager.h>



/*********************************************************//**
* @brief
* �`���[�g���A�����S01�`��N���X
*
* �`���[�g���A�����S01�̕`��N���X
*************************************************************/
class TutorialLogo01Draw : public DrawNone
{
//==============================
// �萔
//==============================
private:
	static const std::string TEXTURE_NAME;		//!< �e�N�X�`����
	static const float       SCALE;				//!< �g�k


//==============================
// ��ÓI�����o�֐�
//==============================
private:
	TutorialLogo01* tutorial_logo_;		//!< �`���[�g���A�����S01
	TextureObject* decale_texture_;		//!< �f�J�[���e�N�X�`��


//==============================
// ��ÓI�����o�֐�
//==============================
public:
	/**
	* @brief
	* �������֐�
	*/
	void Init() override;

	/**
	* @brief
	* �I���֐�
	*/
	void Uninit() override;

	/**
	* @brief
	* �`��֐�
	*/
	void Draw(unsigned object_index, unsigned mesh_index) override;

	// �v���p�e�B
	const MATRIX* GetMatrix(unsigned object_index) override;
	unsigned GetMeshNum(unsigned object_index) override;
	D3DMATERIAL9* GetMaterial(unsigned object_index, unsigned mesh_index) override;
	LPDIRECT3DTEXTURE9 GetDecaleTexture(unsigned object_index, unsigned mesh_index) override;
};



#endif