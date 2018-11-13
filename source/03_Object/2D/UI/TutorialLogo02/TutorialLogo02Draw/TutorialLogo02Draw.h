//================================================================================
//
//    �`���[�g���A�����S02�`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/09/02
//
//================================================================================

#ifndef	_TUTORIAL_LOGO_02_DRAW_H_
#define _TUTORIAL_LOGO_02_DRAW_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <string>

#include "../TutorialLogo02.h"

#include <Component/DrawBase/DrawBase.h>
#include <ResourceManager\ResourceManager.h>



//======================================================================
//
// �N���X��`
//
//======================================================================

class TutorialLogo02Draw : public DrawBase
{
//------------------------------------------------------------
private :
	// �萔
	static const std::string TEXTURE_NAME;
	static const float       SCALE;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �����o�֐�
	void Init()   override;
	void Uninit() override;
	void Draw(unsigned object_index, unsigned mesh_index) override;

	const MATRIX* GetMatrix(unsigned object_index) override;
	unsigned		   GetMeshNum()							 override;
	D3DMATERIAL9*	   GetMaterial(unsigned object_index, unsigned mesh_index)		 override;
	LPDIRECT3DTEXTURE9 GetDecaleTexture(unsigned object_index, unsigned mesh_index) override;


//------------------------------------------------------------
private :
	// �����o�ϐ�
	TutorialLogo02* title_logo_;
	TextureObject* decale_texture_;


};



#endif