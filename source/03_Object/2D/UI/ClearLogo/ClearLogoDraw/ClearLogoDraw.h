//================================================================================
//
//    �N���A���S�`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/06/19
//
//================================================================================

#ifndef	_CLEAR_LOGO_DRAW_H_
#define _CLEAR_LOGO_DRAW_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <string>

#include <Component/DrawBase/DrawNone.h>
#include "../ClearLogo.h"

#include <ResourceManager\ResourceManager.h>



/*********************************************************//**
* @brief
* �N���A���S�`��N���X
*
* �N���A���S�̕`��N���X
*************************************************************/
class ClearLogoDraw : public DrawNone
{
//==============================
// �萔
//==============================
private :
	static const std::string TEXTURE_NAME;		//!< �e�N�X�`����
	static const float       SCALE;				//!< �g�k


//==============================
// ��ÓI�����o�֐�
//==============================
private:
	ClearLogo* clear_logo_;				//!< �N���A���S
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