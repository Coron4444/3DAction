//================================================================================
//
//    タイトルロゴ描画クラス
//    Author : Araki Kai                                作成日 : 2018/07/03
//
//================================================================================

#ifndef	_TITLE_LOGO_DRAW_H_
#define _TITLE_LOGO_DRAW_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include <string>

#include "../TitleLogo.h"

#include <Component/DrawBase/DrawBase.h>
#include <ResourceManager\ResourceManager.h>



//======================================================================
//
// クラス定義
//
//======================================================================

class TitleLogoDraw : public DrawBase
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
	TitleLogo* title_logo_;
	TextureObject* decale_texture_;


};



#endif