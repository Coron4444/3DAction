//================================================================================
//
//    コイン描画クラス
//    Author : Araki Kai                                作成日 : 2018/07/24
//
//================================================================================

#ifndef	_COIN_DRAW_H_
#define _COIN_DRAW_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include <string>

#include "../Coin.h"

#include <Component/DrawBase/DrawBase.h>
#include <ResourceManager/ResourceManager.h>



//======================================================================
//
// クラス定義
//
//======================================================================

class CoinDraw : public DrawBase
{
//------------------------------------------------------------
private :
	static const std::string DECALE_TEXTURE;
	static const std::string EFFECT;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// メンバ関数
	void Init()   override;
	void Uninit() override;
	void Draw(unsigned object_index, unsigned mesh_index) override;

	const MATRIX* GetMatrix(unsigned object_index) override;
	unsigned	  GetMeshNum()					   override;
	D3DMATERIAL9* GetMaterial(unsigned object_index, unsigned mesh_index) override;
	LPDIRECT3DTEXTURE9 GetDecaleTexture(unsigned object_index, unsigned mesh_index) override;


//------------------------------------------------------------
private :
	Coin* coin_;
	TextureObject* decale_texture_;
	EffekseerObject* effekseer_object_;

};



#endif