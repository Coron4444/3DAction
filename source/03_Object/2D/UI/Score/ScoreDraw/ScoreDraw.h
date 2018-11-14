//================================================================================
//
//    �X�R�A�`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/06/20
//
//================================================================================

#ifndef	_SCORE_DRAW_H_
#define _SCORE_DRAW_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <Component/DrawBase/DrawNone.h>
#include "../Score.h"

#include <ResourceManager\ResourceManager.h>



/*********************************************************//**
* @brief
* �X�R�A�`��N���X
*
* �X�R�A�̕`��N���X
*************************************************************/
class ScoreDraw : public DrawNone
{
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
};



#endif