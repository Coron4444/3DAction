//================================================================================
//
//    スカイドーム描画クラス
//    Author : Araki Kai                                作成日 : 2018/05/15
//
//================================================================================

#ifndef	_SKY_DOME_DRAW_H_
#define _SKY_DOME_DRAW_H_



//****************************************
// インクルード文
//****************************************
#include <string>

#include <Component/Draw/DrawNull/DrawNull.h>
#include "../SkyDome.h"



//****************************************
// クラス宣言
//****************************************
class ModelXObject;



/*********************************************************//**
* @brief
* プレイヤー描画クラス
*
* プレイヤーの描画クラス
*************************************************************/
class SkyDomeDraw : public DrawNull
{
//==============================
// 定数
//==============================
private:
	// 定数
	static const std::string MODEL_NAME;	//!< モデル名


//==============================
// 非静的メンバ関数
//==============================
private:
	ModelXObject* sky_dome_model_;		//!< モデルオブジェクト


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