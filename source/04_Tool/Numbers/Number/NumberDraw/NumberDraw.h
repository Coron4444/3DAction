//================================================================================
//
//    �����`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/06/19
//
//================================================================================

#ifndef	_NUMBER_DRAW_H_
#define _NUMBER_DRAW_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <string>

#include "../Number.h"
#include <Component\DrawComponent\DrawComponent.h>



//======================================================================
//
// �N���X��`
//
//======================================================================

class NumberDraw : public DrawComponent
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �����o�֐�
	void Init()   override;
	void Uninit() override;
	void Draw(unsigned mesh_index) override;

	unsigned		   GetMeshNum()							 override;
	D3DMATERIAL9*	   GetMaterial(unsigned mesh_index)		 override;
	LPDIRECT3DTEXTURE9 GetDecaleTexture(unsigned mesh_index) override;


//------------------------------------------------------------
private :
	// �����o�ϐ�
	Number* number_;
};



#endif