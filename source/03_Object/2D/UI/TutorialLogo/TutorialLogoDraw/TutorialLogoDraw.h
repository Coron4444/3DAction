//================================================================================
//
//    �`���[�g���A�����S�`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/09/02
//
//================================================================================

#ifndef	_TUTORIAL_LOGO_DRAW_H_
#define _TUTORIAL_LOGO_DRAW_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <string>

#include <Component/Draw/DrawNull/DrawNull.h>
#include "../../TutorialLogo/TutorialLogo.h"

#include <Polygon\PlanePolygon\PlanePolygon.h>
#include <ResourceManager\ResourceManager.h>



/*********************************************************//**
* @brief
* �`���[�g���A�����S�`��N���X
*
* �`���[�g���A�����S�̕`��N���X
*************************************************************/
class TutorialLogoDraw : public DrawNull
{
//==============================
// �萔
//==============================
private:
	static const unsigned TEXTURE_NUM = 2;				//!< �e�N�X�`����
	static const std::string TEXTURE_NAME[TEXTURE_NUM];	//!< �e�N�X�`����
	static const float SCALE;							//!< �g�k


//==============================
// ��ÓI�����o�֐�
//==============================
private:
	TutorialLogo* tutorial_logo_ = nullptr;					//!< �`���[�g���A��
	TextureObject* decale_texture_[TEXTURE_NUM] = {nullptr};	//!< �f�J�[���e�N�X�`��
	PlanePolygon* plane_polygon_ = nullptr;						//!< ���ʃ|���S��
	unsigned texture_index_ = 0;


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
	* �X�V�֐�
	*/
	void Update() override;

	/**
	* @brief
	* �`��֐�
	* @param
	* object_index : �I�u�W�F�N�g�C���f�b�N�X
	* mesh_index : ���b�V���C���f�b�N�X
	*/
	void Draw(unsigned object_index, unsigned mesh_index) override;

	// �v���p�e�B
	const MATRIX* GetMatrix(unsigned object_index) override;
	unsigned GetMeshNum(unsigned object_index) override;
	D3DMATERIAL9* GetMaterial(unsigned object_index, unsigned mesh_index) override;
	LPDIRECT3DTEXTURE9 GetDecaleTexture(unsigned object_index, unsigned mesh_index) override;
};



#endif