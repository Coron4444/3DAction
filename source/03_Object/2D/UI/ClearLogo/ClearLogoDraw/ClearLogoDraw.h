//================================================================================
//
//    クリアロゴ描画クラス
//    Author : Araki Kai                                作成日 : 2018/06/19
//
//================================================================================

#ifndef	_CLEAR_LOGO_DRAW_H_
#define _CLEAR_LOGO_DRAW_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include <string>

#include "../ClearLogo.h"

#include <Component\DrawComponent\DrawComponent.h>
#include <ResourceManager\ResourceManager.h>



//======================================================================
//
// クラス定義
//
//======================================================================

class ClearLogoDraw : public DrawComponent
{
//------------------------------------------------------------
private :
	// 定数
	static const std::string TEXTURE_NAME;
	static const float       SCALE;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// メンバ関数
	void Init()   override;
	void Uninit() override;
	void Draw(unsigned mesh_index) override;

	unsigned		   GetMeshNum()							 override;
	D3DMATERIAL9*	   GetMaterial(unsigned mesh_index)		 override;
	LPDIRECT3DTEXTURE9 GetDecaleTexture(unsigned mesh_index) override;


//------------------------------------------------------------
private :
	// メンバ変数
	ClearLogo* clear_logo_;
	TextureObject* decale_texture_;


};



#endif