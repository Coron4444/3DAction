//================================================================================
//
//    �����`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/06/19
//
//================================================================================

#ifndef	_NUMBER_DRAW_H_
#define _NUMBER_DRAW_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <string>

#include <Component/DrawBase/DrawNone.h>
#include "../Number.h"



/*********************************************************//**
* @brief
* �����`��N���X
*
* �����̕`��N���X
*************************************************************/
class NumberDraw : public DrawNone
{
//==============================
// ��ÓI�����o�֐�
//==============================
private:
	Number* number_;	//!< ����


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