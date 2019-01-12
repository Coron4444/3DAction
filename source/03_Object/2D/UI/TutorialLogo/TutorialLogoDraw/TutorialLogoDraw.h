//================================================================================
//
//    チュートリアルロゴ描画クラス
//    Author : Araki Kai                                作成日 : 2018/09/02
//
//================================================================================

#ifndef	_TUTORIAL_LOGO_DRAW_H_
#define _TUTORIAL_LOGO_DRAW_H_



//****************************************
// インクルード文
//****************************************
#include <string>

#include <Component/Draw/DrawNull/DrawNull.h>
#include "../../TutorialLogo/TutorialLogo.h"

#include <Polygon\PlanePolygon\PlanePolygon.h>
#include <Texture/TextureManager/TextureManager.h>



/*********************************************************//**
* @brief
* チュートリアルロゴ描画クラス
*
* チュートリアルロゴの描画クラス
*************************************************************/
class TutorialLogoDraw : public DrawNull
{
//==============================
// 定数
//==============================
private:
	static const unsigned TEXTURE_NUM = 2;				//!< テクスチャ数
	static const std::string TEXTURE_NAME[TEXTURE_NUM];	//!< テクスチャ名
	static const float SCALE;							//!< 拡縮


//==============================
// 非静的メンバ関数
//==============================
private:
	TutorialLogo* tutorial_logo_ = nullptr;					//!< チュートリアル
	TextureObject* diffuse_texture_[TEXTURE_NUM] = {nullptr};	//!< ディヒューズテクスチャ
	PlanePolygon* plane_polygon_ = nullptr;						//!< 平面ポリゴン
	unsigned texture_index_ = 0;


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
	* 更新関数
	*/
	void Update() override;

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