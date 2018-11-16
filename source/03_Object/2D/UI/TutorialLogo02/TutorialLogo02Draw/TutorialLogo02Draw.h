//================================================================================
//
//    チュートリアルロゴ02描画クラス
//    Author : Araki Kai                                作成日 : 2018/09/02
//
//================================================================================

#ifndef	_TUTORIAL_LOGO_02_DRAW_H_
#define _TUTORIAL_LOGO_02_DRAW_H_



//****************************************
// インクルード文
//****************************************
#include <string>

#include <Component/DrawBase/DrawNull.h>
#include "../TutorialLogo02.h"

#include <ResourceManager\ResourceManager.h>



/*********************************************************//**
* @brief
* チュートリアルロゴ02描画クラス
*
* チュートリアルロゴ02の描画クラス
*************************************************************/
class TutorialLogo02Draw : public DrawNull
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
	TutorialLogo02* tutorial_logo_;		//!< チュートリアルロゴ02
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