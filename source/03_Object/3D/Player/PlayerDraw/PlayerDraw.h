//================================================================================
//
//    プレイヤー描画クラス
//    Author : Araki Kai                                作成日 : 2018/03/27
//
//================================================================================

#ifndef	_PLAYER_DRAW_H_
#define _PLAYER_DRAW_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include <string>

#include "../Player.h"

#include <Component\DrawComponent\DrawComponent.h>
#include <ResourceManager\ResourceManager.h>



//======================================================================
//
// クラス定義
//
//======================================================================

class PlayerDraw : public DrawComponent
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
	void Draw(unsigned mesh_index) override;

	unsigned		   GetMeshNum()							 override;
	D3DMATERIAL9*	   GetMaterial(unsigned mesh_index)		 override;
	LPDIRECT3DTEXTURE9 GetDecaleTexture(unsigned mesh_index) override;
	LPDIRECT3DTEXTURE9 GetNormalTexture(unsigned mesh_index) override;


//------------------------------------------------------------
private :
	// メンバ変数
	ModelXObject* player_model_;
	TextureObject* normal_texture_[2];

};



#endif