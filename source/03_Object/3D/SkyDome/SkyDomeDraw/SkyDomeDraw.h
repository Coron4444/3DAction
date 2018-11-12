//================================================================================
//
//    �X�J�C�h�[���`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/05/15
//
//================================================================================

#ifndef	_SKY_DOME_DRAW_H_
#define _SKY_DOME_DRAW_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <string>

#include "../SkyDome.h"

#include <Component/DrawBase/DrawBase.h>
#include <ResourceManager\ResourceManager.h>



//======================================================================
//
// �N���X��`
//
//======================================================================

class SkyDomeDraw : public DrawBase
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �萔
	static const std::string MODEL_NAME;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �����o�֐�
	void Init()					   override;
	void Uninit()				   override;
	void Draw(unsigned mesh_index) override;

	unsigned		   GetMeshNum()							 override;
	D3DMATERIAL9*	   GetMaterial(unsigned mesh_index)		 override;
	LPDIRECT3DTEXTURE9 GetDecaleTexture(unsigned mesh_index) override;


//------------------------------------------------------------
private :
	// �����o�ϐ�
	ModelXObject* sky_dome_model_;


};



#endif