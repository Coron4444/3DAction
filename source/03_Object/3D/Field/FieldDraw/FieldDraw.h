//================================================================================
//
//    地面描画クラス
//    Author : Araki Kai                                作成日 : 2018/05/15
//
//================================================================================

#ifndef	_FIELD_DRAW_H_
#define _FIELD_DRAW_H_



//****************************************
// インクルード文
//****************************************s
#include <string>

#include <Component/Draw/DrawNull/DrawNull.h>
#include "../Field.h"

#include <ResourceManager\ResourceManager.h>



/*********************************************************//**
* @brief
* 地面描画クラス
*
* 地面の描画クラス
*************************************************************/
class FieldDraw : public DrawNull
{
//==============================
// 定数
//==============================
private:
	static const std::string TEXTURE_NAME;		//!< テクスチャ名


//==============================
// 非静的メンバ関数
//==============================
private:
	Field* field_;						//!< 地面
	TextureObject* decale_texture_;		//!< デカールテクスチャ


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
	const MATRIX* GetMatrix(unsigned object_index) override;
	unsigned GetMeshNum(unsigned object_index) override;
	D3DMATERIAL9* GetMaterial(unsigned object_index, unsigned mesh_index) override;
	LPDIRECT3DTEXTURE9 GetDecaleTexture(unsigned object_index, unsigned mesh_index) override;
};



#endif