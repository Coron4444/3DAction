//================================================================================
//
//    コイン描画クラス
//    Author : Araki Kai                                作成日 : 2018/07/24
//
//================================================================================

#ifndef	_COIN_DRAW_H_
#define _COIN_DRAW_H_



//****************************************
// インクルード文
//****************************************
#include <string>

#include <Component/Draw/DrawNull/DrawNull.h>
#include "../Coin.h"

#include <ResourceManager/ResourceManager.h>



/*********************************************************//**
* @brief
* コインロゴ描画クラス
*
* コインロゴの描画クラス
*************************************************************/
class CoinDraw : public DrawNull
{
//==============================
// 定数
//==============================
private:
	static const std::string DECALE_TEXTURE;	//!< デカールテクスチャ名
	static const std::string EFFECT;			//!< エフェクト名


//==============================
// 非静的メンバ関数
//==============================
private:
	Coin* coin_;						//!< コイン
	TextureObject* decale_texture_;		//!< デカールテクスチャ
	EffekseerObject* effekseer_object_;	//!< エフェクシアオブジェクト


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


	// プロパティ
	const MATRIX* GetMatrix(unsigned object_index) override;
	unsigned GetMeshNum(unsigned object_index) override;
	D3DMATERIAL9* GetMaterial(unsigned object_index, unsigned mesh_index) override;
	LPDIRECT3DTEXTURE9 GetDecaleTexture(unsigned object_index, unsigned mesh_index) override;
};



#endif