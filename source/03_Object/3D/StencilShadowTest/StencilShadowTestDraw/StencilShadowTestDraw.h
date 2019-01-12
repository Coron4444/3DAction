//================================================================================
//
//    ステンシルシャドウ描画クラス
//    Author : Araki Kai                                作成日 : 2018/03/27
//
//================================================================================

#ifndef	_STENCIL_SHADOW_TEST_DRAW_H_
#define _STENCIL_SHADOW_TEST_DRAW_H_



//****************************************
// インクルード文
//****************************************
#include <string>

#include <Component/Draw/DrawNull/DrawNull.h>
#include "../StencilShadowTest.h"



//****************************************
// クラス宣言
//****************************************
class PlanePolygon;
class ModelXObject;



/*********************************************************//**
* @brief
* ステンシルシャドウ描画クラス
*
* ステンシルシャドウの描画クラス
*************************************************************/
class StencilShadowTestDraw : public DrawNull
{
//==============================
// 定数
//==============================
private:
	// 定数
	static const std::string MODEL_NAME;		//!< モデル名

//==============================
// 非静的メンバ関数
//==============================
private:
	ModelXObject* player_model_;			//!< モデルオブジェクト
	PlanePolygon* plane_polygon_;			//!< 板ポリゴン	
	Transform plane_polygon_transform_;		//!< 板ポリゴン用変形


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

	/**
	* @brief
	* 描画前設定関数
	* @param
	* camera : カメラ
	* object_index : オブジェクトインデックス
	*/
	virtual void SettingBeforeDrawing(Camera* camera, unsigned object_index) override;

	/**
	* @brief
	* 描画後設定関数
	* @param
	* camera : カメラ
	* object_index : オブジェクトインデックス
	*/
	virtual void SettingAfterDrawing(Camera* camera, unsigned object_index) override;

	// プロパティ
	unsigned getObjectNum() override;
	unsigned getMeshNum(unsigned object_index) override;
	MATRIX* getpMatrix(unsigned object_index) override;
	D3DMATERIAL9* getpMaterial(unsigned object_index, unsigned mesh_index) override;
	LPDIRECT3DTEXTURE9 getpDiffuseTexture(unsigned object_index, unsigned mesh_index) override;
};



#endif