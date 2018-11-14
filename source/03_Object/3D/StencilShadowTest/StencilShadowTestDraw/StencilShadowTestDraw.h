//================================================================================
//
//    �v���C���[�`��N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/27
//
//================================================================================

#ifndef	_STENCIL_SHADOW_TEST_DRAW_H_
#define _STENCIL_SHADOW_TEST_DRAW_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <string>

#include "../StencilShadowTest.h"

#include <Component/DrawBase/DrawBase.h>
#include <ResourceManager\ResourceManager.h>


class PlanePolygon;

//======================================================================
//
// �N���X��`
//
//======================================================================

class StencilShadowTestDraw : public DrawBase
{
//------------------------------------------------------------
private :
	// �萔
	static const std::string MODEL_NAME;
	static const std::string TEXTURE_PATH;
	static const std::string NORMAL_TEXTURE_NAME01;
	static const std::string NORMAL_TEXTURE_NAME02;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �����o�֐�
	void Init()					   override;
	void Uninit()				   override;
	void Draw(unsigned object_index, unsigned mesh_index) override;

	virtual void LimitedChangeCameraType(Camera* camera, unsigned object_index) 
	{ 
		if (object_index == 2)
		{
			save_camera_type_ = camera->GetType();
			camera->SetType(Camera::Type::TWO_DIMENSIONAL);
		}
	}
	const MATRIX* GetMatrix(unsigned object_index) override;
	virtual unsigned GetDrawObjectNum() { return 3; }
	unsigned		   GetMeshNum(unsigned object_index)							 override;
	D3DMATERIAL9*	   GetMaterial(unsigned object_index, unsigned mesh_index)		 override;
	LPDIRECT3DTEXTURE9 GetDecaleTexture(unsigned object_index, unsigned mesh_index) override;
	LPDIRECT3DTEXTURE9 GetNormalTexture(unsigned object_index, unsigned mesh_index) override;


//------------------------------------------------------------
private :
	// �����o�ϐ�
	ModelXObject* player_model_;
	PlanePolygon* plane_polygon_;
	TextureObject* normal_texture_[2];
	Transform temp_transform_;
};



#endif