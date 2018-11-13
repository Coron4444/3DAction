//================================================================================
//
//    �X�R�A�`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/06/20
//
//================================================================================

#ifndef	_SCORE_DRAW_H_
#define _SCORE_DRAW_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <string>

#include "../Score.h"

#include <Component/DrawBase/DrawBase.h>
#include <ResourceManager\ResourceManager.h>



//======================================================================
//
// �N���X��`
//
//======================================================================

class ScoreDraw : public DrawBase
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �����o�֐�
	void Init()   override;
	void Uninit() override;
	void Draw(unsigned object_index, unsigned mesh_index) override;

	const MATRIX* GetMatrix(unsigned object_index) override;
};



#endif