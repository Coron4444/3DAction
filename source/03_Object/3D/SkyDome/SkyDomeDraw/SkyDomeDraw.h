//================================================================================
//
//    スカイドーム描画クラス
//    Author : Araki Kai                                作成日 : 2018/05/15
//
//================================================================================

#ifndef	_SKY_DOME_DRAW_H_
#define _SKY_DOME_DRAW_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include <string>

#include "../SkyDome.h"

#include <Component/DrawBase/DrawBase.h>
#include <ResourceManager\ResourceManager.h>



//======================================================================
//
// クラス定義
//
//======================================================================

class SkyDomeDraw : public DrawBase
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// 定数
	static const std::string MODEL_NAME;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// メンバ関数
	void Init()					   override;
	void Uninit()				   override;
	void Draw(unsigned mesh_index) override;

	unsigned		   GetMeshNum()							 override;
	D3DMATERIAL9*	   GetMaterial(unsigned mesh_index)		 override;
	LPDIRECT3DTEXTURE9 GetDecaleTexture(unsigned mesh_index) override;


//------------------------------------------------------------
private :
	// メンバ変数
	ModelXObject* sky_dome_model_;


};



#endif