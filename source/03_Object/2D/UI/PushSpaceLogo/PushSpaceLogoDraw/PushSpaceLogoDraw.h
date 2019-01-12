//================================================================================
//
//    プッシュスペースロゴ描画クラス
//    Author : Araki Kai                                作成日 : 2018/09/02
//
//================================================================================

#ifndef	_PUSH_SPACE_LOGO_DRAW_H_
#define _PUSH_SPACE_LOGO_DRAW_H_



//****************************************
// インクルード文
//****************************************
#include <string>

#include <Component/Draw/DrawNull/DrawNull.h>
#include "../PushSpaceLogo.h"

#include <Texture/TextureManager/TextureManager.h>



/*********************************************************//**
* @brief
* プッシュスペースロゴ描画クラス
*
* プッシュスペースロゴの描画クラス
*************************************************************/
class PushSpaceLogoDraw : public DrawNull
{
//==============================
// 定数
//==============================
private:
	static const std::string TEXTURE_NAME;		//!< テクスチャ名
	static const float       SCALE;				//!< 拡縮


//==============================
// 非静的メンバ関数
//==============================
private:
	PushSpaceLogo* push_space_logo_;	//!< プッシュスペースロゴ
	TextureObject* diffuse_texture_;		//!< ディヒューズテクスチャ


//==============================
// 非静的メンバ関数
//==============================
public:
	/**
	* @brief
	* 初期化関数
	*/
	void Init() override;

	/**
	* @brief
	* 終了関数
	*/
	void Uninit() override;

	/**
	* @brief
	* 描画関数
	* @param
	* object_index : オブジェクトインデックス
	* mesh_index : メッシュインデックス
	*/
	void Draw(unsigned object_index, unsigned mesh_index) override;

	// プロパティ
	unsigned getMeshNum(unsigned object_index) override;
	MATRIX* getpMatrix(unsigned object_index) override;
	D3DMATERIAL9* getpMaterial(unsigned object_index, unsigned mesh_index) override;
	LPDIRECT3DTEXTURE9 getpDiffuseTexture(unsigned object_index, unsigned mesh_index) override;
};



#endif