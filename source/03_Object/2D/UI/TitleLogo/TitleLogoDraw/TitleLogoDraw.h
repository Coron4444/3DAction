//================================================================================
//
//    �^�C�g�����S�`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/07/03
//
//================================================================================

#ifndef	_TITLE_LOGO_DRAW_H_
#define _TITLE_LOGO_DRAW_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <string>

#include <Component/DrawBase/DrawNone.h>
#include "../TitleLogo.h"

#include <ResourceManager\ResourceManager.h>



/*********************************************************//**
* @brief
* �^�C�g�����S�`��N���X
*
* �^�C�g�����S�̕`��N���X
*************************************************************/
class TitleLogoDraw : public DrawNone
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
	TitleLogo* title_logo_;				//!< �^�C�g�����S
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