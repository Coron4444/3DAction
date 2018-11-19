//================================================================================
//
//    �R�C���`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/07/24
//
//================================================================================

#ifndef	_COIN_DRAW_H_
#define _COIN_DRAW_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <string>

#include <Component/Draw/DrawNull/DrawNull.h>
#include "../Coin.h"

#include <ResourceManager/ResourceManager.h>



/*********************************************************//**
* @brief
* �R�C�����S�`��N���X
*
* �R�C�����S�̕`��N���X
*************************************************************/
class CoinDraw : public DrawNull
{
//==============================
// �萔
//==============================
private:
	static const std::string DECALE_TEXTURE;	//!< �f�J�[���e�N�X�`����
	static const std::string EFFECT;			//!< �G�t�F�N�g��


//==============================
// ��ÓI�����o�֐�
//==============================
private:
	Coin* coin_;						//!< �R�C��
	TextureObject* decale_texture_;		//!< �f�J�[���e�N�X�`��
	EffekseerObject* effekseer_object_;	//!< �G�t�F�N�V�A�I�u�W�F�N�g


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
	* @param
	* object_index : �I�u�W�F�N�g�C���f�b�N�X
	* mesh_index : ���b�V���C���f�b�N�X
	*/
	void Draw(unsigned object_index, unsigned mesh_index) override;

	/**
	* @brief
	* �`��O�ݒ�֐�
	* @param
	* camera : �J����
	* object_index : �I�u�W�F�N�g�C���f�b�N�X
	*/
	virtual void SettingBeforeDrawing(Camera* camera, unsigned object_index) override;


	// �v���p�e�B
	const MATRIX* GetMatrix(unsigned object_index) override;
	unsigned GetMeshNum(unsigned object_index) override;
	D3DMATERIAL9* GetMaterial(unsigned object_index, unsigned mesh_index) override;
	LPDIRECT3DTEXTURE9 GetDecaleTexture(unsigned object_index, unsigned mesh_index) override;
};



#endif