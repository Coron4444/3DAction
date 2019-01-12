//================================================================================
//!	@file	 CoinDraw.h
//!	@brief	 コイン描画Class
//! @details 
//!	@author  Kai Araki									@date 2018/07/24
//================================================================================
#ifndef	_COIN_DRAW_H_
#define _COIN_DRAW_H_



//****************************************
// インクルード文
//****************************************
#include <string>

#include "../Coin.h"
#include <Component/Draw/DrawNull/DrawNull.h>



//****************************************
// クラス宣言
//****************************************
class TextureObject;



//************************************************************														   
//! @brief   コインロゴ描画Class
//!
//! @details コインロゴの描画Class
//************************************************************
class CoinDraw : public DrawNull
{
//====================
// 定数
//====================
private:
	static const std::string diffuse_TEXTURE;	//!< ディヒューズテクスチャ名
	

//====================
// 変数
//====================
private:
	Coin* coin_;						//!< コイン
	TextureObject* diffuse_texture_;		//!< ディヒューズテクスチャ


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Init() override;

	//----------------------------------------
	//! @brief 終了関数
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Uninit() override;

	//----------------------------------------
	//! @brief 更新関数
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Update() override;

	//----------------------------------------
	//! @brief 描画関数
	//! @param[in] object_index オブジェクトインデックス
	//! @param[in] mesh_index   メッシュインデックス
	//! @retval void なし
	//----------------------------------------
	void Draw(unsigned object_index, unsigned mesh_index) override;

	//----------------------------------------
	//! @brief 描画前設定関数
	//! @param[in] camera       カメラ
	//! @param[in] object_index オブジェクトインデックス
	//! @retval void なし
	//----------------------------------------
	void SettingBeforeDrawing(Camera* camera, unsigned object_index) override;


	// プロパティ
	unsigned getMeshNum(unsigned object_index) override;
	MATRIX* getpMatrix(unsigned object_index) override;
	D3DMATERIAL9* getpMaterial(unsigned object_index, unsigned mesh_index) override;
	LPDIRECT3DTEXTURE9 getpDiffuseTexture(unsigned object_index, unsigned mesh_index) override;
};



#endif