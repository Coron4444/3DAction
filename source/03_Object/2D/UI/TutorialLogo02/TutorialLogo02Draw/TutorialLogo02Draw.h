//================================================================================
//
//    チュートリアルロゴ02描画クラス
//    Author : Araki Kai                                作成日 : 2018/09/02
//
//================================================================================

#ifndef	_TUTORIAL_LOGO_02_DRAW_H_
#define _TUTORIAL_LOGO_02_DRAW_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include <string>

#include "../TutorialLogo02.h"

#include <Component/DrawBase/DrawBase.h>
#include <ResourceManager\ResourceManager.h>



//======================================================================
//
// クラス定義
//
//======================================================================

class TutorialLogo02Draw : public DrawBase
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
	void Draw(unsigned object_index, unsigned mesh_index) override;

	const MATRIX* GetMatrix(unsigned object_index) override;
	unsigned		   GetMeshNum()							 override;
	D3DMATERIAL9*	   GetMaterial(unsigned object_index, unsigned mesh_index)		 override;
	LPDIRECT3DTEXTURE9 GetDecaleTexture(unsigned object_index, unsigned mesh_index) override;


//------------------------------------------------------------
private :
	// メンバ変数
	TutorialLogo02* title_logo_;
	TextureObject* decale_texture_;


};



#endif