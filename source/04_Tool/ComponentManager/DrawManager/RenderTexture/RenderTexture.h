//================================================================================
//!	@file	 RenderTexture.h
//!	@brief	 レンダラーテクスチャClass
//! @details 
//!	@author  Kai Araki									@date 2018/05/08
//================================================================================
#ifndef	_RENDER_TEXTURE_H_
#define _RENDER_TEXTURE_H_



//****************************************
// インクルード文
//****************************************
#include <string>

#include <Component/Draw/DrawNull/DrawNull.h>
#include <Vector3D.h>



//****************************************
// クラス宣言
//****************************************
class PlanePolygon;
class Transform;



//************************************************************														   
//! @brief   レンダラーテクスチャClass
//!
//! @details レンダラーテクスチャのClass
//************************************************************
class RenderTexture : public DrawNull
{
//====================
// 変数
//====================
private:
	PlanePolygon* plane_polygon_ = nullptr;			//!< 板ポリゴン
	Transform* transform_ = nullptr;				//!< 状態


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 行列取得関数
	//! @details
	//! @param object_index オブジェクトインデックス
	//! @retval MATRIX* 行列
	//----------------------------------------
	MATRIX* getpMatrix(unsigned object_index) override;

	//----------------------------------------
	//! @brief マテリアル取得関数
	//! @details
	//! @param object_index オブジェクトインデックス
	//! @param mesh_index   メッシュインデックス
	//! @retval D3DMATERIAL9* マテリアル
	//----------------------------------------
	D3DMATERIAL9* getpMaterial(unsigned object_index, unsigned mesh_index) override;


//==============================
// 非静的メンバ関数
//==============================
public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Init();

	//----------------------------------------
	//! @brief 終了関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Uninit() override;

	//----------------------------------------
	//! @brief 更新関数
	//! @details
	//! @param x     X座標
	//! @param y     Y座標
	//! @param color 色
	//! @retval void なし
	//----------------------------------------
	void Update(float x, float y, XColor4 color);
	

	//----------------------------------------
	//! @brief 描画関数
	//! @details
	//! @param object_index オブジェクトインデックス
	//! @param mesh_index   メッシュインデックス
	//! @retval void なし
	//----------------------------------------
	void Draw(unsigned object_index, unsigned mesh_index) override;
};



#endif