//================================================================================
//
//    �n�ʕ`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/05/15
//
//================================================================================

#ifndef	_FIELD_DRAW_H_
#define _FIELD_DRAW_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <string>

#include "../Field.h"

#include <Component/DrawBase/DrawBase.h>
#include <ResourceManager\ResourceManager.h>



//======================================================================
//
// �N���X��`
//
//======================================================================

class FieldDraw : public DrawBase
{
//------------------------------------------------------------
private :
	// �萔
	static const std::string TEXTURE_NAME;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �����o�֐�
	void Init()					   override;
	void Uninit()				   override;
	void Draw(unsigned object_index, unsigned mesh_index) override;

	const MATRIX* GetMatrix(unsigned object_index) override;
	unsigned		   GetMeshNum()							 override;
	D3DMATERIAL9*	   GetMaterial(unsigned object_index, unsigned mesh_index)		 override;
	LPDIRECT3DTEXTURE9 GetDecaleTexture(unsigned object_index, unsigned mesh_index) override;


//------------------------------------------------------------
private :
	// �����o�ϐ�
	TextureObject* decale_texture_;


};



#endif