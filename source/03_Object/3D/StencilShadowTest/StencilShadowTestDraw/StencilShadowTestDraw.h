//================================================================================
//
//    プレイヤー描画クラス
//    Author : Araki Kai                                作成日 : 2018/03/27
//
//================================================================================

#ifndef	_STENCIL_SHADOW_TEST_DRAW_H_
#define _STENCIL_SHADOW_TEST_DRAW_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include <string>

#include "../StencilShadowTest.h"

#include <Component/DrawBase/DrawBase.h>
#include <ResourceManager\ResourceManager.h>


class PlanePolygon;

//======================================================================
//
// クラス定義
//
//======================================================================

class StencilShadowTestDraw : public DrawBase
{
//------------------------------------------------------------
private :
	// 定数
	static const std::string MODEL_NAME;
	static const std::string TEXTURE_PATH;
	static const std::string NORMAL_TEXTURE_NAME01;
	static const std::string NORMAL_TEXTURE_NAME02;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// メンバ関数
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
	// メンバ変数
	ModelXObject* player_model_;
	PlanePolygon* plane_polygon_;
	TextureObject* normal_texture_[2];
	Transform temp_transform_;
};



#endif