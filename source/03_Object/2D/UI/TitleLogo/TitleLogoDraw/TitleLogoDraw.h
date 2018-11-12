//================================================================================
//
//    �^�C�g�����S�`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/07/03
//
//================================================================================

#ifndef	_TITLE_LOGO_DRAW_H_
#define _TITLE_LOGO_DRAW_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <string>

#include "../TitleLogo.h"

#include <Component/DrawBase/DrawBase.h>
#include <ResourceManager\ResourceManager.h>



//======================================================================
//
// �N���X��`
//
//======================================================================

class TitleLogoDraw : public DrawBase
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
	void Draw(unsigned mesh_index) override;

	unsigned		   GetMeshNum()							 override;
	D3DMATERIAL9*	   GetMaterial(unsigned mesh_index)		 override;
	LPDIRECT3DTEXTURE9 GetDecaleTexture(unsigned mesh_index) override;


//------------------------------------------------------------
private :
	// �����o�ϐ�
	TitleLogo* title_logo_;
	TextureObject* decale_texture_;


};



#endif